#include <iostream>
#include <cstdlib>
#include <map>
#include <algorithm>
#include "parser.h"

using namespace std;

map<string, vector<int> >duplicatePolynomials;

map<int, vector<string> >polyParamters;
map<int, vector<string> > bodyVariables;
bool errorOneTriggered = false;

map<string, int> declaredPolys;
map<string, int> declaredPolyevals;

void Parser::syntax_error()
{
    cout << "SYNTAX ERROR !!&%!!\n";
    exit(1);
}

// this function gets a token and checks if it is
// of the expected type. If it is, the token is
// returned, otherwise, synatx_error() is generated
// this function is particularly useful to match
// terminals in a right hand side of a rule.
// Written by Mohsen Zohrevandi
Token Parser::expect(TokenType expected_type)
{
    Token t = lexer.GetToken();
    if (t.token_type != expected_type)
        syntax_error();
    return t;
}

// Parsing
void Parser::input() {
    program();
    errorOne();
    if (errorOneTriggered == false){
        errorTwo();
    }
    errorThree();
    inputs();
    expect(END_OF_FILE);
}
void Parser::program() {
    poly_decl_section();
    start();
}
void Parser::poly_decl_section() {
    poly_decl();
    Token t = lexer.peek(1);
    if (t.token_type == POLY){
        poly_decl_section();
    }
}
void Parser::poly_decl() {
    expect(POLY);
    Token g = polynomial_header();

    vector<int> line = {g.line_no};
    if (duplicatePolynomials.find(g.lexeme) == duplicatePolynomials.end()){
        duplicatePolynomials.insert({g.lexeme, line});
    }
    else{
        duplicatePolynomials[g.lexeme].push_back(g.line_no);
    }

    declaredPolys.insert({g.lexeme, g.line_no});

    expect(EQUAL);
    polynomial_body();
    expect(SEMICOLON);
}
Token Parser::polynomial_header() {
    Token g = polynomial_name();
    Token t = lexer.peek(1);
    if (t.token_type == LPAREN){
        expect(LPAREN);
        Token h = id_list();
        expect(RPAREN);
    }
    return g;

}
Token Parser::id_list() {
    Token g = expect(ID);
    vector<string> line = {g.lexeme};
    if (polyParamters.find(g.line_no) == polyParamters.end()){
        polyParamters.insert({g.line_no,line});
    }
    else{
        polyParamters[g.line_no].push_back(g.lexeme);
    }


    Token t = lexer.peek(1);
    if (t.token_type == COMMA){
        expect(COMMA);
        id_list();
    }
    return g;
}
Token Parser::polynomial_name() {
    return expect(ID);
}
void Parser::polynomial_body() {
    term_list();
}
void Parser::term_list() {
    term();
    Token t = lexer.peek(1);
    if (t.token_type == PLUS || t.token_type == MINUS){
        add_operator();
        term_list();
    }
}
void Parser::term() {
    Token t = lexer.peek(1);
    if (t.token_type == ID){
        monomial_list();
    }else if (t.token_type == NUM){
        coefficient();
        t = lexer.peek(1);
        if (t.token_type == ID){
            monomial_list();
        }
    }
    else
        syntax_error();
}
void Parser::monomial_list() {
    Token g = monomial();
    vector<string> line = {g.lexeme};
    if (bodyVariables.find(g.line_no) == bodyVariables.end()){
        bodyVariables.insert({g.line_no,line});
    }
    else{
        bodyVariables[g.line_no].push_back(g.lexeme);
    }


    Token t = lexer.peek(1);
    if (t.token_type == ID){
        monomial_list();
    }
}
Token Parser::monomial() {
    Token g = expect(ID);
    Token t = lexer.peek(1);
    if (t.token_type == POWER){
        exponent();
    }
    return g;
}
void Parser::exponent() {
    expect(POWER);
    expect(NUM);
}
void Parser::add_operator() {
    Token t = lexer.peek(1);
    if (t.token_type == PLUS){
        expect(PLUS);
    }
    else if (t.token_type == MINUS){
        expect(MINUS);
    }
}
void Parser::coefficient() {
    expect(NUM);
}
void Parser::start() {
    expect(START);
    statement_list();
}
void Parser::inputs() {
    expect(NUM);
    Token t = lexer.peek(1);
    if (t.token_type == NUM){
        inputs();
    }
}
void Parser::statement_list() {
    statement();
    Token t  = lexer.peek(1);
    if (t.token_type == INPUT || t.token_type == ID){
        statement_list();
    }
}
void Parser::statement() {
    Token t = lexer.peek(1);
    if (t.token_type == INPUT){
        input_statement();
    }else if (t.token_type == ID){
        poly_evaluation_statement();
    }
    else
        syntax_error();
}
void Parser::poly_evaluation_statement() {
    polynomial_evaluation();
    expect(SEMICOLON);
}
void Parser::input_statement() {
    expect(INPUT);
    expect(ID);
    expect(SEMICOLON);
}
void Parser::polynomial_evaluation() {
    Token g = polynomial_name();
    declaredPolyevals.insert({g.lexeme,g.line_no});

    expect(LPAREN);
    argument_list();
    expect(RPAREN);
}
void Parser::argument_list() {
    argument();
    Token t = lexer.peek(1);
    if (t.token_type == COMMA){
        expect(COMMA);
        argument_list();
    }
//    else
//        syntax_error();
}

void Parser::argument() {
    Token t = lexer.peek(1);

    if (t.token_type == ID && lexer.peek(2).token_type == LPAREN) {
        polynomial_evaluation();
    } else if (t.token_type == ID) {
        expect(ID);
    } else if (t.token_type == NUM) {
        expect(NUM);
    } else
        syntax_error();

}
void Parser::errorOne() {
    vector<int> lineNumbers;
    map<string, vector<int> >::iterator it;

    for (it = duplicatePolynomials.begin(); it != duplicatePolynomials.end(); it++)
    {
        vector<int> tmp = it->second;
        if (tmp.size() > 1){
            lineNumbers.reserve(it->second.size());
            lineNumbers.insert(lineNumbers.end(), tmp.begin(), tmp.end());
        }
    }

    if (!lineNumbers.empty()){
        sort(lineNumbers.begin(), lineNumbers.end());
        cout << "Error Code 1: ";
        for (int i = 0; i < lineNumbers.size(); i++) {
            cout << lineNumbers.at(i) << " ";
        }
        cout << endl;
        errorOneTriggered = true;
    }


}
void Parser::errorTwo() {
    vector<int> lineNumbers;
    map<int, vector<string> >::iterator it;
    vector<string> tmp;
    vector<string> tmp2;
    int linenumber = 1;
    string lineToPrint = "Error Code 2: ";

    tmp.reserve(polyParamters.size() );
    tmp2.reserve(bodyVariables.size() );
    for (int i = 1; i <= bodyVariables.size(); i++) {
        tmp = polyParamters[i];
        tmp2 = bodyVariables[i];

        for (int j = 0; j < tmp2.size(); j++) {
            if (!tmp.empty() && tmp2.size() != 1){
                if (!(std::find(tmp.begin(), tmp.end(), tmp2[j]) != tmp.end())) {
                    lineToPrint.append(to_string(linenumber)).append(" ");
                }
            }

        }
        linenumber++;

    }
    if (lineToPrint != "Error Code 2: "){
        cout << lineToPrint;
    }

}
void Parser::errorThree() {
    map<string, int >::iterator it;
    vector<string> polys;
    polys.reserve(declaredPolyevals.size());
    map<string, int > polies = declaredPolys;
    map<string, int > inputies =  declaredPolyevals;
    string code = "Error Code 3: ";
    for (it = declaredPolyevals.begin(); it != declaredPolyevals.end(); it++)
    {
        polys.push_back(it->first);
    }
    for (int i = 0; i < polys.size(); ++i) {
        if ((declaredPolys.find(polys.at(i)) == declaredPolys.end())){
            code.append(to_string(declaredPolyevals[polys.at(i)])).append(" ");
        }

    }
    if (code != "Error Code 3: "){
        cout << code;
    }


}



int main()
{
    // note: the parser class has a lexer object instantiated in it. You should not be declaring
    // a separate lexer object. You can access the lexer object in the parser functions as shown in the
    // example method Parser::ConsumeAllInput
    // If you declare another lexer object, lexical analysis will not work correctly
    Parser parser;
    parser.input();

}