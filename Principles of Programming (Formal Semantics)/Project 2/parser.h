//************************************************************************
// Name: Eduardo Teodosio Campuzano
// Description: This code creates regex structures based on a specific input and rules
// and using those structures we determine if some input provided is accepted by the reg structures
// or if it causes an error or if it allows epsilon to be a token
//Rules:

//input -> tokens section INPUT TEXT
//tokens section -> token list HASH
//token list -> token
//token list -> token COMMA token list
//token -> ID expr
//expr -> CHAR
//expr -> LPAREN expr RPAREN DOT LPAREN expr RPAREN
//expr -> LPAREN expr RPAREN OR LPAREN expr RPAREN
//expr -> LPAREN expr RPAREN STAR
//expr -> UNDERSCORE
//**************************************************************************
#ifndef __PARSER_H__
#define __PARSER_H__

#include <string>
#include "lexer.h"
#include <map>
#include <sstream>
using namespace std;

struct REG_node{
    struct REG_node* first_neighbor;
    char first_label;
    struct REG_node* second_neighbor;
    char second_label;
};

struct REG {
    REG_node * start;
    REG_node * accept;
};

class My_LexicalAnalyzer {
public:
    string input;
    string longestSubStr;
    map<string, REG*> listOfRegs;
    vector<REG_node*> regNodes;
    int placeInString = 0;
    vector<string> strings;
    bool error = false;

    void my_GetToken();
    bool match(REG*, string);
    bool matchOneChar(char c);
    bool epsilonIsNotAToken();
    bool epsilonCanReachAccept(REG *);
    bool isAccepted(string string1, REG*);
    My_LexicalAnalyzer(map<string, REG*> regList, string string1, int i){
        listOfRegs = regList;
        input = string1;
        placeInString = i;
    }

};

class Parser {
  public:
    map<string, REG *> Regs;
    string inputString;
    vector<string> individualInputs;
    string daInput;

    void input();
    void tokens_section();
    void token_list();
    void token();
    REG* expr();
    void storeInputs();


    REG* base_case(Token);
    REG* Concatenation(REG *, REG *);
    REG* Union(REG *, REG *);
    REG* kleeneStar(REG *);

private:
    LexicalAnalyzer lexer;
    void syntax_error();
    Token expect(TokenType expected_type);
};

#endif

