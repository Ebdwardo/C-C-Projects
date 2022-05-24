//************************************************************************
// Name: Eduardo Teodosio Campuzano
//**************************************************************************
#include <iostream>
#include <cstdlib>
#include "parser.h"
#include <algorithm>


using namespace std;

void Parser::syntax_error()
{
    cout << "SYNTAX ERROR\n";
    exit(1);
}

// this function gets a token and checks if it is
// of the expected type. If it is, the token is
// returned, otherwise, synatx_error() is generated
// this function is particularly useful to match
// terminals in a right hand side of a rule.
// Written by Mohsen Zohrevandi

//This section parses the regex expression and creates the corresponding regex structure and stores all the ones provided in a map
Token Parser::expect(TokenType expected_type)
{
    Token t = lexer.GetToken();
    if (t.token_type != expected_type)
        syntax_error();
    return t;
}

void Parser::input() {
    tokens_section();
    Token input = expect(INPUT_TEXT);
    inputString = input.lexeme;
    expect(END_OF_FILE);
}

void Parser::tokens_section() {
    token_list();
    expect(HASH);
}

void Parser::token_list() {
    token();
    Token t = lexer.peek(1);
    if (t.token_type == COMMA){
        expect(COMMA);
        token_list();
    }
}

void Parser::token() {
    Token t = lexer.peek(1);
    expect(ID);
    REG* regs = expr();
    Regs.insert({t.lexeme, regs});
}

//Its inside this function that we construct the regex structures
REG * Parser::expr() {
    Token t = lexer.peek(1);
    if (t.token_type == CHAR){
        Token c = expect(CHAR);
        return base_case(c);
    }
    else if (t.token_type == LPAREN ){
        expect(LPAREN);
        REG* reg1 = expr();
        expect(RPAREN);

        Token v = lexer.peek(1);

        //Depending on what the input describes, we build the according structures using functions
        if (v.token_type == DOT){
            expect(DOT);
            expect(LPAREN);
            REG* reg2 = expr();
            expect(RPAREN);

            return Concatenation(reg1, reg2);
        }
        else if (v.token_type == OR){
            expect(OR);
            expect(LPAREN);
            REG* reg3 = expr();
            expect(RPAREN);

            return Union(reg1, reg3);
        }
        else if (v.token_type == STAR){
            expect(STAR);
            return kleeneStar(reg1);
        }
        else
            syntax_error();
    }
    else if(t.token_type == UNDERSCORE){
        Token epsilon = expect(UNDERSCORE);
        epsilon.lexeme = '_';
        return base_case(epsilon);
    }
    else
        syntax_error();
}

//These functions create structures according to possible regex rules we have
REG * Parser::base_case(Token c) {
    REG* letter{};
    letter = new REG();
    letter->start = new REG_node();
    letter->accept = new REG_node();

    REG_node* startNode{};
    startNode = new REG_node();
    REG_node* endNode{};
    endNode = new REG_node();

    startNode->first_neighbor = endNode;
    startNode->first_label = c.lexeme[0];
    startNode->second_neighbor = NULL;

    endNode->first_neighbor = NULL;
    endNode->second_neighbor = NULL;

    letter->start->first_neighbor = startNode;
    letter->accept->first_neighbor = endNode;

    return letter;
}

REG * Parser::Concatenation(REG * a, REG * b) {
    REG* concat;
    concat = new REG();
    concat->start = new REG_node();
    concat->accept = new REG_node();

    a->accept->first_neighbor->first_neighbor = b->start->first_neighbor;
    a->accept->first_neighbor->first_label = '_';
    a->accept->first_neighbor->second_neighbor = NULL;

    concat->start->first_neighbor = a->start->first_neighbor;
    concat->accept->first_neighbor = b->accept->first_neighbor;
    return concat;
}

REG * Parser::Union(REG* a, REG* b) {
    REG* uni;
    uni = new REG();
    uni->accept = new REG_node();
    uni->start = new REG_node();

    REG_node* startNode{};
    startNode = new REG_node();
    REG_node* endNode{};
    endNode = new REG_node();

    startNode->first_neighbor = a->start->first_neighbor;
    startNode->first_label = '_';
    startNode->second_neighbor = b->start->first_neighbor;
    startNode->second_label = '_';

    a->accept->first_neighbor->first_neighbor = endNode;
    a->accept->first_neighbor->first_label = '_';
    a->accept->first_neighbor->second_neighbor = NULL;

    b->accept->first_neighbor->first_neighbor = endNode;
    b->accept->first_neighbor->first_label = '_';
    b->accept->first_neighbor->second_neighbor = NULL;

    endNode->first_neighbor = NULL;
    endNode->second_neighbor = NULL;

    uni->accept->first_neighbor = endNode;
    uni->start->first_neighbor = startNode;

    return uni;

}

REG * Parser::kleeneStar(REG* a) {
    REG* star;
    star = new REG();
    star->start = new REG_node();
    star->accept = new REG_node();

    REG_node* startNode;
    startNode = new REG_node();
    REG_node* endNode;
    endNode = new REG_node();
    endNode->first_neighbor = nullptr;
    endNode->second_neighbor = nullptr;

    a->accept->first_neighbor->first_neighbor = endNode;
    a->accept->first_neighbor->first_label = '_';
    a->accept->first_neighbor->second_neighbor = a->start->first_neighbor;
    a->accept->first_neighbor->second_label = '_';

    startNode->first_neighbor = a->start->first_neighbor;
    startNode->first_label = '_';
    startNode->second_neighbor = endNode;
    startNode->second_label = '_';

    star->start->first_neighbor = startNode;
    star->accept->first_neighbor = endNode;

    return star;
}


//This function determines and prints out the longest possible substring(s) for each reg structure
void My_LexicalAnalyzer::my_GetToken() {
    string temp = input;
    bool didYouAccept = false;

    // while the copy of the string is not empty
    while (!temp.empty()){

        //iterate through all the reg structures
        for (auto const& x : listOfRegs) {

            //See is the input at its current state matches
            didYouAccept = match(x.second, temp) ;
            if(didYouAccept){

                //if it does match then print it out
                for (auto& it: strings) {

                    if( !it.empty()){
                        cout << x.first << " , " << "\"" << it << "\"" << endl;
                        error = false;
                        break;
                    }

                }
                strings.clear();
                break;
            }

        }

        //if the input does not match for any of the regs then chop off the last character;
        if (didYouAccept == false)
            temp.pop_back();
        else
            temp = input;

    }

    //if none of the regs can consume the string then error out;
    if (!input.empty()){
        cout << "ERROR" << endl;
    }

}

//This function checks if the string we provided is accepted by the regex structure and if so it consumes it form the input
bool My_LexicalAnalyzer::match(REG* a, string s) {
    string input = s;
    bool Error = true;
    REG_node* first = a->start->first_neighbor;
    regNodes.clear();
    regNodes.push_back(first);

    if (isAccepted(input, a)){

        strings.push_back(input);
        longestSubStr = input;
        this->input = this->input.substr(input.size());

        while (this->input[0] == ' ')
            this->input.erase(0, 1);

        return true;
    }

    else
        return false;
}

//This function is used to check if the nodes in the regnodes list have first or second neighbors that can be reached by the character that is passed in
//If they do, depending on whether char c is '_' (epsilon) or an acutal character we either add nodes to the regnodes list
//or we change the regnodes list to nodes reachable by consuming a specific character from the current nodes
bool My_LexicalAnalyzer::matchOneChar(char c) {
    vector<REG_node*> temp;
    bool flag = false;
    vector<REG_node*> regNodesCopy = regNodes;

    //For every regnode in the list
    for (auto& it : regNodesCopy) {

        //If it can transition using the char c take the node it can go to and add it to temp and if its not already in the lsit add it
        if (it->first_label == c){

            temp.push_back(it->first_neighbor);

            if (find(regNodes.begin(), regNodes.end(), it->first_neighbor) == regNodes.end()){
                regNodes.push_back(it->first_neighbor);
                flag = true;
            }

        }

        //If it can transition using the char c take the node it can go to and add it to temp and if its not already in the list add it
        if (it->second_label == c){

            temp.push_back(it->second_neighbor);

            if (find(regNodes.begin(), regNodes.end(), it->second_neighbor) == regNodes.end()){
                regNodes.push_back(it->second_neighbor);
                flag = true;
            }

        }

    }

    //If char was an actual character then we only care what nodes we can reach after consuming that character so we update the list accordingly
    if (!temp.empty() && c != '_') {
        regNodes = temp;
        flag = true;
    }

    return flag;
}

//Checks to see if a string passed is accepted by the reg struct that is passed by calling matchOneChar for every character in the input
bool My_LexicalAnalyzer::isAccepted(string string1, REG* a) {
    string copy = string1;

    while (!copy.empty()){
        bool epsilon = true;

        while (epsilon){
            epsilon = matchOneChar('_');
        }

        bool accepted = matchOneChar(copy.at(0));

        epsilon = true;
        while (epsilon){
            epsilon = matchOneChar('_');
        }

        if (accepted == false)
            break;

        copy = copy.substr(1);
    }

    //We know that if the string is empty and the accepting node is in the list after consuming the string that it is accepted
    if (copy.empty() && (find(regNodes.begin(), regNodes.end(), a->accept->first_neighbor) != regNodes.end()))
        return true;
    else
        return false;
}

//Checks to see if the reg can take epsilon as a token which is not allowed
bool My_LexicalAnalyzer::epsilonIsNotAToken() {
    //We have to string to compare if epsilon is a token
    string e = "EPSILON IS NOOOOOT A TOKEN !!!";
    string d = "EPSILON IS NOOOOOT A TOKEN !!!";

    //For each reg check to see if it takes epsilon as a token
    for (auto const& x : listOfRegs)
    {
        //If epsilon is a token then add it to the string that tells us which regs do
        if (epsilonCanReachAccept(x.second)){
            e.append(" ").append(x.first);
        }

    }

    //If the string changed that we know we need to print out that epsilon is a token for some reg structures
    if (e != d){
        cout << e;
        return true;
    }
    else
        return false;
}

//This keeps calling match for epsilon until we reach the accepting state or we cannot go forward with strictly epsilon transitions and returns whether we can or cannot
bool My_LexicalAnalyzer::epsilonCanReachAccept(REG * a) {
    REG_node* first = a->start->first_neighbor;
    regNodes.clear();
    regNodes.push_back(first);

    while ( true ){

        vector<REG_node* > temp = regNodes;
        matchOneChar('_');

        if (temp == regNodes || (find(regNodes.begin(), regNodes.end(), a->accept->first_neighbor) != regNodes.end()))
            break;
    }

    if (find(regNodes.begin(), regNodes.end(), a->accept->first_neighbor) != regNodes.end()){
        return true;
    }
    else
        return false;

}

int main()
{
	// note: the parser class has a lexer object instantiated in it. You should not be declaring
    // a separate lexer object. You can access the lexer object in the parser functions as shown in the
    // example method Parser::ConsumeAllInput
    // If you declare another lexer object, lexical analysis will not work correctly
    Parser parser;
    parser.input();
    parser.storeInputs();

    My_LexicalAnalyzer* regAnalyzer = new My_LexicalAnalyzer(parser.Regs, parser.daInput, 0);

    bool epsil = regAnalyzer->epsilonIsNotAToken();
    if (!epsil)
        regAnalyzer->my_GetToken();

}

//This function takes the input string and parses it in such a way that we are left no quotes or spaces that there should not be
void Parser::storeInputs() {
    string word;

    // making a string stream
    stringstream iss(inputString);

    // Read each word.
    while (iss >> word)

        if (word != "\"" || word != "\""){

            if (word[word.length()-1] == '\"'){
                word.erase(word.length()-1);
            }

            if (word[0] == '\"'){
                word = word.substr(1);
            }

            individualInputs.push_back(word);
            daInput.append(word).append(" ");

        }

}