//
// Created by Eduardo Teodosio on 4/12/2021.
//

#ifndef CSE340PROJECT4_PARSER_H
#define CSE340PROJECT4_PARSER_H

#include "lexer.h"
#include "compiler.h"
#include <unordered_map>
using namespace std;

class Parser {
public:
    InstructionNode* program();
    void var_section();
    void id_list();
    InstructionNode* body();
    InstructionNode* stmt_list();
    InstructionNode* stmt();
    InstructionNode* assign_stmt();
    InstructionNode* expr();
    Token primary();
    Token op();
    InstructionNode* output_stmt();
    InstructionNode* input_stmt();
    InstructionNode* while_stmt();
    InstructionNode* if_stmt();
    InstructionNode* condition();
    Token relop();
    InstructionNode* switch_stmt();
    InstructionNode* for_stmt();
    InstructionNode* case_list();
    InstructionNode* CCase();
    InstructionNode* default_case();
    void input();
    void num_list();

    int location(string);
    int constLocation(Token);

    unordered_map<string,int> association;


private:
    LexicalAnalyzer lexer;
    void syntax_error();
    Token expect(TokenType expected_type);
};


#endif //CSE340PROJECT4_PARSER_H
