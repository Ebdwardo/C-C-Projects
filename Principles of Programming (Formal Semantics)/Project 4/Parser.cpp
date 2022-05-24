// Created by Eduardo Teodosio on 4/12/2021.
#include "Parser.h"
#include <iostream>
#include <cstdlib>

void Parser::syntax_error()
{
    cout << "SYNTAX ERROR\n";
    exit(1);
}

Token Parser::expect(TokenType expected_type)
{
    Token t = lexer.GetToken();
    if (t.token_type != expected_type)
        syntax_error();
    return t;
}

int Parser::constLocation(Token a) {
    mem[next_available] = stoi(a.lexeme);
    next_available++;
    return next_available-1;
}

int Parser::location(string a) {
    mem[next_available] = 0;
    association.insert({a,next_available});
    next_available++;
    return next_available-1;
}

InstructionNode* Parser::program() {
    InstructionNode* inst1 = new InstructionNode;
    var_section();
    inst1 = body();
    input();
    expect(END_OF_FILE);

    return inst1;
}

void Parser::var_section() {
    id_list();
    expect(SEMICOLON);
}

void Parser::id_list() {
    Token g = lexer.peek(1);
    location(g.lexeme);     // add the variable name to the location table and associate location in mem[1000]
    expect(ID);

    Token t = lexer.peek(1);
    if (t.token_type == COMMA){
        expect(COMMA);
        id_list();
    }
}

InstructionNode* Parser::body() {
    InstructionNode* inst1 = new InstructionNode;

    expect(LBRACE);
    inst1 = stmt_list();
    expect(RBRACE);

    return inst1;
}

InstructionNode* Parser::stmt_list() {
    InstructionNode* inst1 = new InstructionNode;
    InstructionNode* inst2 = new InstructionNode;

    inst1 = stmt();

    Token t = lexer.peek(1);
    if ( t.token_type == ID || t.token_type == WHILE || t.token_type == IF || t.token_type == SWITCH || t.token_type == FOR || t.token_type == OUTPUT || t.token_type == INPUT ){
        inst2 = stmt_list();

        //merge inst1 and inst2
        if (inst1->next != NULL){
            InstructionNode* temp = inst1;
            while (temp->next != NULL){
                temp = temp->next;
            }
            temp->next = inst2;
        }
        else{
            inst1->next = inst2;
        }
        return inst1;
    }
    else{
        return inst1;
    }
}

InstructionNode* Parser::stmt() {
    InstructionNode* inst  = new InstructionNode;
    inst->next = NULL;

    Token t = lexer.peek(1);
    if (t.token_type == ID){
        inst = assign_stmt();
    }
    else if (t.token_type == WHILE){
        inst = while_stmt();
    }
    else if (t.token_type == IF){
        inst = if_stmt();
    }
    else if (t.token_type == SWITCH){
        inst = switch_stmt();
    }
    else if (t.token_type == FOR){
        inst = for_stmt();
    }
    else if (t.token_type == OUTPUT) {
        inst = output_stmt();
    }
    else if (t.token_type == INPUT){
        inst = input_stmt();
    }
    return inst;
}

InstructionNode* Parser::assign_stmt() {
    InstructionNode* inst = new InstructionNode;
    inst->next = NULL;
    inst->type = ASSIGN;

    Token g = lexer.peek(1);
    expect(ID);
    inst->assign_inst.left_hand_side_index = association.at(g.lexeme);

    expect(EQUAL);

    Token t = lexer.peek(2);
    if (t.token_type == PLUS || t.token_type == MINUS || t.token_type == MULT || t.token_type == DIV){
        InstructionNode* temp = new InstructionNode;
        temp = expr();
        inst->assign_inst.operand1_index = temp->assign_inst.operand1_index;
        inst->assign_inst.operand2_index = temp->assign_inst.operand2_index;
        inst->assign_inst.op = temp->assign_inst.op;
    }
    else{
        Token p = primary();
        inst->assign_inst.op = OPERATOR_NONE;

        if (p.token_type == NUM){
            bool alreadyIn = false;
            int location = 0;
            for (int i = 0; i < next_available; i++) {
                if (mem[i] == stoi(p.lexeme) && p.lexeme != "0"){ // added here
                    alreadyIn = true;
                    location = i;
                }
            }
            if (!alreadyIn){
                location = constLocation(p);
            }
            inst->assign_inst.operand1_index = location;
        }
        else{
            inst->assign_inst.operand1_index = association.at(p.lexeme);
        }
    }
    expect(SEMICOLON);
    return inst;
}

InstructionNode* Parser::expr() {
    InstructionNode* inst = new InstructionNode;
    inst->next = NULL;
    inst->type = ASSIGN;
    Token a = primary();
    if (a.token_type == NUM){
        bool alreadyIn = false;
        int location = 0;
        for (int i = 0; i < next_available; i++) {
            if (mem[i] == stoi(a.lexeme) && a.lexeme != "0"){ // added here
                alreadyIn = true;
                location = i;
            }
        }
        if (!alreadyIn){
            location = constLocation(a);
        }
        inst->assign_inst.operand1_index = location;
    }
    else{
        inst->assign_inst.operand1_index = association.at(a.lexeme);
    }

    Token b = op();
    if (b.token_type == PLUS)
        inst->assign_inst.op = OPERATOR_PLUS;
    else if (b.token_type == MINUS)
            inst->assign_inst.op = OPERATOR_MINUS;
    else if (b.token_type == MULT)
        inst->assign_inst.op = OPERATOR_MULT;
    else if (b.token_type == DIV)
        inst->assign_inst.op = OPERATOR_DIV;


    Token c = primary();
    if (c.token_type == NUM){
        bool alreadyIn = false;
        int location = 0;
        for (int i = 0; i < next_available; i++) {
            if (mem[i] == stoi(c.lexeme) && c.lexeme != "0"){ // added here
                alreadyIn = true;
                location = i;
            }
        }
        if (!alreadyIn){
            location = constLocation(c);
        }
        inst->assign_inst.operand2_index = location;
    }
    else{
        inst->assign_inst.operand2_index = association.at(c.lexeme);
    }
    return inst;
}

Token Parser::primary() {
    Token t = lexer.peek(1);
    if (t.token_type == ID){
        expect(ID);
        return t;
    }
    else if (t.token_type == NUM){

        expect(NUM);
        return t;
    }
}

Token Parser::op() {
    Token t = lexer.peek(1);
    if (t.token_type == PLUS)
        expect(PLUS);
    else if (t.token_type == MINUS)
        expect(MINUS);
    else if (t.token_type == MULT)
        expect(MULT);
    else if (t.token_type == DIV)
        expect(DIV);
    return t;
}

InstructionNode* Parser::output_stmt() {
    InstructionNode* inst = new InstructionNode;
    inst->next = NULL;
    inst->type = OUT;
    expect(OUTPUT);

    Token o = lexer.peek(1);
    inst->output_inst.var_index = association.at(o.lexeme);
    expect(ID);

    expect(SEMICOLON);

    return inst;
}

InstructionNode* Parser::input_stmt() {
    InstructionNode* inst = new InstructionNode;
    inst->next = NULL;
    inst->type = IN;
    expect(INPUT);

    Token o = lexer.peek(1);
    inst->input_inst.var_index = association.at(o.lexeme);
    expect(ID);

    expect(SEMICOLON);

    return inst;
}

InstructionNode* Parser::while_stmt() {
    InstructionNode* inst = new InstructionNode;
    InstructionNode* noop = new InstructionNode;
    InstructionNode* jump = new InstructionNode;
    jump->next = NULL;
    noop->next = NULL;
    inst->next = NULL;
    inst->type = CJMP;
    noop->type = NOOP;
    jump->type = JMP;

    expect(WHILE);
    InstructionNode* temp = condition();
    inst->cjmp_inst.operand1_index = temp->cjmp_inst.operand1_index;
    inst->cjmp_inst.operand2_index = temp->cjmp_inst.operand2_index;
    inst->cjmp_inst.condition_op = temp->cjmp_inst.condition_op;

    InstructionNode* temp2 = body();
    jump->jmp_inst.target = inst;

    if (temp2->next != NULL){
        InstructionNode* temp = temp2;
        while (temp->next != NULL){
            temp = temp->next;
        }
        temp->next = jump;
        temp->next->next = noop;
    }
    else{
        temp2->next = jump;
        //temp->next->next = noop;
        temp2->next->next = noop;
    }

    inst->next = temp2;
    inst->cjmp_inst.target = noop;

    return inst;
}

InstructionNode* Parser::if_stmt() {
    InstructionNode* inst = new InstructionNode;
    InstructionNode* noop = new InstructionNode;
    noop->next = NULL;
    inst->next = NULL;
    inst->type = CJMP;
    noop->type = NOOP;

    expect(IF);
    InstructionNode* temp = condition();
    inst->cjmp_inst.operand1_index = temp->cjmp_inst.operand1_index;
    inst->cjmp_inst.operand2_index = temp->cjmp_inst.operand2_index;
    inst->cjmp_inst.condition_op = temp->cjmp_inst.condition_op;

    InstructionNode* temp2 = body();

    if (temp2->next != NULL){
        InstructionNode* temp = temp2;
        while (temp->next != NULL){
            temp = temp->next;
        }
        temp->next = noop;
    }
    else{
        temp2->next = noop;
    }
    inst->next = temp2;
    inst->cjmp_inst.target = noop;

    return inst;
}

InstructionNode* Parser::condition() {
    InstructionNode* inst = new InstructionNode;
    inst->next = NULL;

    Token a = primary();
    if (a.token_type == NUM){
        bool alreadyIn = false;
        int location = 0;
        for (int i = 0; i < next_available; i++) {
            if (mem[i] == stoi(a.lexeme) && a.lexeme != "0"){ // added here
                alreadyIn = true;
                location = i;
            }
        }
        if (!alreadyIn){
            location = constLocation(a);
        }
        inst->cjmp_inst.operand1_index = location;
    }
    else{
        inst->cjmp_inst.operand1_index = association.at(a.lexeme);
    }

    Token b = relop();
    if(b.token_type == GREATER)
        inst->cjmp_inst.condition_op = CONDITION_GREATER;
    else if(b.token_type == LESS)
        inst->cjmp_inst.condition_op = CONDITION_LESS;
    else if(b.token_type == NOTEQUAL)
        inst->cjmp_inst.condition_op = CONDITION_NOTEQUAL;

    Token c = primary();
    if (c.token_type == NUM){
        bool alreadyIn = false;
        int location = 0;
        for (int i = 0; i < next_available; i++) {
            if (mem[i] == stoi(c.lexeme) && c.lexeme != "0"){
                alreadyIn = true;
                location = i;
            }
        }
        if (!alreadyIn){
            location = constLocation(c);
        }
        inst->cjmp_inst.operand2_index = location;
    }
    else{
        inst->cjmp_inst.operand2_index = association.at(c.lexeme);
    }
    return inst;
}

Token Parser::relop() {
    Token t = lexer.peek(1);
    if (t.token_type == GREATER)
        expect(GREATER);
    else if (t.token_type == LESS)
        expect(LESS);
    else if (t.token_type == NOTEQUAL)
        expect(NOTEQUAL);
    return t;
}

InstructionNode* Parser::for_stmt() {
    InstructionNode* inst = new InstructionNode;
    InstructionNode* noop = new InstructionNode;
    InstructionNode* jump = new InstructionNode;
    jump->next = NULL;
    noop->next = NULL;
    inst->next = NULL;
    inst->type = ASSIGN;
    noop->type = NOOP;
    jump->type = JMP;

    expect(FOR);
    expect(LPAREN);

    inst = assign_stmt();

    InstructionNode* b = condition();
    b->type = CJMP;
    b->cjmp_inst.target = noop;
    inst->next = b;

    expect(SEMICOLON);
    InstructionNode* c = assign_stmt();
    expect(RPAREN);

    InstructionNode* d = body();
    if (d->next != NULL){
        InstructionNode* temp = d;
        while (temp->next != NULL){
            temp = temp->next;
        }
        temp->next = c;
        temp->next->next = jump;
        temp->next->next->next = noop;
    }
    else{
        d->next = c;
        d->next->next = jump;
        d->next->next->next = noop;
    }
    b->next = d;
    jump->jmp_inst.target = b;
    return inst;
}

InstructionNode* Parser::switch_stmt() {
    InstructionNode* inst = new InstructionNode;
    InstructionNode* noop = new InstructionNode;
    inst->next = NULL;
    noop->next = NULL;
    noop->type = NOOP;

    expect(SWITCH);
    Token g = lexer.peek(1);
    expect(ID);
    expect(LBRACE);
    inst = case_list();

    if (inst->next != NULL){
        InstructionNode* temp = inst;
        while (temp->next != NULL ){
            if (temp->type == CJMP){
                if(temp->cjmp_inst.operand1_index == NULL){
                    temp->cjmp_inst.operand1_index = association.at(g.lexeme);
                }
                temp->cjmp_inst.condition_op = CONDITION_NOTEQUAL;
            }
            if (temp->type == JMP && temp->jmp_inst.target == NULL){
                temp->jmp_inst.target = noop;
            }
            temp = temp->next;
        }
    }
    else{
        inst->cjmp_inst.operand1_index = association.at(g.lexeme);
        inst->cjmp_inst.condition_op = CONDITION_NOTEQUAL;
    }

    Token t = lexer.peek(1);
    if (t.token_type == RBRACE){
        expect(RBRACE);
        InstructionNode* temp2 = inst;
        while (temp2->next != NULL){
            temp2 = temp2->next;
        }
        temp2->next = noop;
    }
    else {
        InstructionNode* temp2 = inst;
        while (temp2->next != NULL){
            temp2 = temp2->next;
        }
        temp2->next = default_case();
        while (temp2->next != NULL){
            temp2 = temp2->next;
        }
        temp2->next = noop;
        expect(RBRACE);
    }

    return inst;
}

InstructionNode* Parser::case_list() {
    InstructionNode* inst = new InstructionNode;
    InstructionNode* inst2 = new InstructionNode;
    inst->next = NULL;
    inst->type = CJMP;
    inst2->next = NULL;
    inst2->type = CJMP;

    inst =  CCase();
    Token t = lexer.peek(1);
    if (t.token_type == CASE){
        inst2 = case_list();

        InstructionNode* temp = inst;
        while (temp->next != NULL){
            temp = temp->next;
        }
        temp->next = inst2;
    }

    return inst;
}

InstructionNode* Parser::CCase() {
    InstructionNode* inst = new InstructionNode;
    InstructionNode* jump = new InstructionNode;
    InstructionNode* jumpToIfNOOP = new InstructionNode;
    InstructionNode* noop = new InstructionNode;
    inst->next = NULL;
    inst->type = CJMP;
    jump->next = NULL;
    jump->type = JMP;
    jump->jmp_inst.target = NULL;
    jumpToIfNOOP->next = NULL;
    jumpToIfNOOP->type = JMP;
    noop->next = NULL;
    noop->type = NOOP;

    jumpToIfNOOP->jmp_inst.target = noop;

    expect(CASE);

    Token t = lexer.peek(1);
    expect(NUM);
    if (t.token_type == NUM){
        bool alreadyIn = false;
        int location = 0;
        for (int i = 0; i < next_available; i++) {
            if (mem[i] == stoi(t.lexeme) && t.lexeme != "0" ){
                alreadyIn = true;
                location = i;
            }
        }
        if (!alreadyIn){
            location = constLocation(t);
        }
        inst->cjmp_inst.operand1_index = NULL;
        inst->cjmp_inst.operand2_index = location;
    }
    expect(COLON);

    InstructionNode* temp = body();
    if (temp->next != NULL){
        InstructionNode* tem = temp;
        while (tem->next != NULL){
            tem = tem->next;
        }
        tem->next = jump;
        tem->next->next = noop;
    }
    else{
        temp->next = jump;
        temp->next->next = noop;
    }
    inst->next = jumpToIfNOOP;
    inst->next->next = temp;
    inst->cjmp_inst.target = temp;
    return inst;
}

InstructionNode* Parser::default_case() {
    expect(DEFAULT);
    expect(COLON);
    return body();
}

void Parser::input() {
   num_list();
}

void Parser::num_list() {
    Token g = lexer.peek(1);
    inputs.push_back(stoi(g.lexeme));
    expect(NUM);
    Token t = lexer.peek(1);
    if (t.token_type == NUM)
        num_list();
}

struct InstructionNode * parse_generate_intermediate_representation() {
    InstructionNode* inst = new InstructionNode;
    Parser parser;
    inst = parser.program();
    return inst;
}