// Name of Author: Eduardo Teodosio Campuzano
// Description: this is the main program that reads input from keyboard,
// it then call hash functions to execute hash commands given in the input.

/**************************************************************************
//(1)Describe here what is your hash function?
// my hash function is a variation on hashing by multiplication. I convert the key to an ascii value
 representing the sum of characters the do the floor of (k A mod 1) * m
***************************************************************************/

#include "Hash.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

//This function extracts tokens from oneLine and get all info. of a Food
void getFoodInfo(string oneLine, string& FoodID, string& name, string& supplierID, double& price);

//This function extracts tokens from oneLine and get a Food key which is
//the combination of FoodID, name and supplierID
void readSearchAndDeleteInfo(string oneLine,string& command ,string& FoodID, string& name, string& supplierID);

int main()
{
    //a variable represents the number of hash table slots
    int size;

    //a variable represents the number of commands
    int numOfCommand;

    //a variable represents the actual command name
    string command;

    string FoodID, name, supplierID;
    double price;
    string delimiter = ",";

    //declare any other necessary variables here
    //----
    string oneLine;

    cout << "Enter the size of the hash table: ";
    cin >> size;
    cin.ignore(20, '\n');

    Hash* hashtable = new Hash(size);

    do {
        cout << "\nEnter food info.(enter InsertionEnd to terminate): " << endl;
        getline(cin, oneLine);
        if(oneLine.compare("InsertionEnd") == 0)
            break;

        //if command is not InsertionEnd
        //Get one line, call getFoodInfo(), then
        //insert the new Food inside the hash table
        //----

        getFoodInfo(oneLine, FoodID, name, supplierID, price);
        hashtable->hashInsert(FoodID, name, supplierID, price);
        cout << "slot index = " << hashtable->hashFunction(hashtable->getKey(FoodID, name, supplierID)) << endl;


    } while(true);

    cout<< "\nEnter number of Commands: ";
    cin >> numOfCommand;
    cin.ignore(20, '\n');

    for(int i= 0; i < numOfCommand; i++)
    {
        //get one line from the input file and extract the first token,
        //if the token is hashDisplay, call the relevant function in Hash.h
        //-----
        cout << "\nEnter command: " << endl;

        getline(cin, oneLine);
        readSearchAndDeleteInfo(oneLine, command, FoodID,name, supplierID);
        if (oneLine.compare("hashDisplay") == 0){
            cout << endl;
            hashtable->hashDisplay();
        }

        //if the token is hashSearch, call the relevant function in Hash.h
        //----
        else if (command.compare("hashSearch") == 0){
            hashtable->hashSearch(FoodID, name, supplierID);
        }


        //if the token is hashDelete, call the relevant function in Hash.h
        //----
        else if (command.compare("hashDelete") == 0){
            hashtable->hashDelete(FoodID, name, supplierID);
        }

        //for all other cases, show the following message
        //cout << "Invalid command" << endl;
        else{
            cout << "Invalid command" << endl;
        }

    } //end for loop

    return 0;
} //end main

//*******************************************************************
//This function extract the tokens from one line and
//get all Food info.
//*******************************************************************
void getFoodInfo(string oneLine, string& FoodID, string& name, string& supplierID, double& price)
{
    string delimiter = ",";
    int pos=oneLine.find(delimiter);
    string token = oneLine.substr(0,pos);
    FoodID = token;
    oneLine.erase(0, pos+delimiter.length());

    pos=oneLine.find(delimiter);
    token = oneLine.substr(0,pos);
    name = token;
    oneLine.erase(0, pos+delimiter.length());

    pos=oneLine.find(delimiter);
    token = oneLine.substr(0,pos);
    supplierID = token;
    oneLine.erase(0, pos+delimiter.length());

    pos=oneLine.find(delimiter);
    token = oneLine.substr(0,pos);
    price = stod(token);
    oneLine.erase(0, pos+delimiter.length());

    //Note: you can use stod to convert a string into double
    //but you will need c++11 compiler to achieve this
    //for example: price = stod(token);
}

//********************************************************************
//This function extracts the FoodID, name, supplierID from a given line
//These info. forms the key of a Food.
//This function is given to you. Study it.
//********************************************************************
void readSearchAndDeleteInfo(string oneLine, string& command, string& FoodID, string& name, string& supplierID)
{
    string delimiter = ",";
    int pos=oneLine.find(delimiter);
    string token = oneLine.substr(0,pos);
    command = token;
    oneLine.erase(0, pos+delimiter.length());

    pos=oneLine.find(delimiter);
    token = oneLine.substr(0,pos);
    FoodID = token;
    oneLine.erase(0, pos+delimiter.length());

    pos=oneLine.find(delimiter);
    token = oneLine.substr(0,pos);
    name = token;
    oneLine.erase(0, pos+delimiter.length());

    pos=oneLine.find(delimiter);
    token = oneLine.substr(0,pos);
    supplierID = token;
    oneLine.erase(0, pos+delimiter.length());
}