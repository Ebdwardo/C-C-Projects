#ifndef __PARSER_H__
#define __PARSER_H__

#include <string>
#include "lexer.h"
#include <map>

using namespace std;

struct polynomial{
    string name;
    vector<string> parameters;
    int lineNumber;
};


class Parser {
  public:
    void input();
    void program();
    void poly_decl_section();
    void poly_decl();
    Token polynomial_header();
    Token id_list();
    Token polynomial_name();
    void polynomial_body();
    void term_list();
    void term();
    void monomial_list();
    Token monomial();
    void exponent();
    void add_operator();
    void coefficient();
    void start();
    void inputs();
    void statement_list();
    void statement();
    void poly_evaluation_statement();
    void input_statement();
    void polynomial_evaluation();
    void argument_list();
    void argument();
    void errorOne();
    void errorTwo();
    void errorThree();

  private:
    LexicalAnalyzer lexer;
    void syntax_error();
    Token expect(TokenType expected_type);

};

#endif

