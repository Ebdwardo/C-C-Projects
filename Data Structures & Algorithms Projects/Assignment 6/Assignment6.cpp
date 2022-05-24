//************************************************************************
// Author: Eduardo Teodosio Campuzano
// Description: this is the main program that reads input from keyboard,
// it then execute various red-black tree operations which is given in the input.
//**************************************************************************

#include "RedBlackTree.h"

using namespace std;

//This function used to get the key of a Food
void getFoodKey(string oneLine, string& foodID, string& name, string& supplierID);

//This function used to get all info. of a Food
void getFoodInfo(string oneLine, string& foodID, string& name, string& supplierID, double& price);

int main()
{
   string foodID, name, supplierID;
   double price;
   string command, oneLine, token;
   string delimiter = ",";

   int pos = 0;

   RedBlackTree *rbTree = new RedBlackTree();
   do
   {
      getline(cin, oneLine);
      pos = oneLine.find(delimiter);
      token = oneLine.substr(0, pos);
      command = token;
      oneLine.erase(0, pos + delimiter.length());

      if(command.compare("quit")==0)
      {
         cout << "\nCommand: quit" << endl;

         //call destructor
         //----
         rbTree->~RedBlackTree();
         break;
      }
      else if(command.compare("tree_preorder")==0)
      {
         cout << "\nCommand: tree_preorder" << endl;

         rbTree->treePreorder();
      }
      else if(command.compare("tree_inorder")==0)
      {
         cout << "\nCommand: tree_inorder" << endl;

         //call the relevant function
         //----
         rbTree->treeInorder();
      }
      else if(command.compare("tree_postorder")==0)
      {
         cout << "\nCommand: tree_postorder" << endl;

         //call the relevant function
         //----
         rbTree->treePostorder();
      }
      else if(command.compare("tree_minimum")==0)
      {
         cout << "\nCommand: tree_minimum" << endl;

         //call the relevant function
         //----
         rbTree->treeMinimum();
      }
      else if(command.compare("tree_maximum")==0)
      {
         cout << "\nCommand: tree_maximum" << endl;

         //call the relevant function
         //----
         rbTree->treeMaximum();
      }
      else if(command.compare("tree_predecessor")==0)
      {
         getFoodKey(oneLine, foodID, name, supplierID);
         cout << "\nCommand: tree_predecessor" << endl;

         //call the relevant function
         //----
         rbTree->treePredecessor(foodID, name, supplierID);
      }
      else if(command.compare("tree_successor")==0)
      {
         getFoodKey(oneLine, foodID, name, supplierID);
         cout << "\nCommand: tree_successor" << endl;

         //call the relevant function
         //----
         rbTree->treeSuccessor(foodID, name, supplierID);
      }
      else if(command.compare("tree_search")==0)
      {
         getFoodKey(oneLine, foodID, name, supplierID);
         cout << "\nCommand: tree_search" << endl;

         //call the relevant function
         //----
         rbTree->treeSearch(rbTree->getRoot() ,foodID, name, supplierID);
      }
      else if(command.compare("tree_insert")==0)
      {
         getFoodInfo(oneLine, foodID, name, supplierID, price);
         cout << "\nCommand: tree_insert" << endl;
         cout << left;
         cout << setw(5) << foodID
              << setw(35) << name
              << setw(15) << supplierID
              << setw(5) << fixed << setprecision(2) << price << endl;

         //call the relevant function
         //----
         rbTree->treeInsert(foodID, name, supplierID, price);
      }
   } while(true);  //continue until 'quit'
   return 0;
}

//********************************************************************
//This function from one line, extracts the foodID, name, supplierID
//information of a Food
void getFoodKey(string oneLine, string& foodID, string& name, string& supplierID)
{
    string delimiter = ",";
    int pos=oneLine.find(delimiter);
    string token = oneLine.substr(0,pos);
    foodID = token;
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

//**************************************************************
//This function from one line, get all Food's info.
void getFoodInfo(string oneLine, string& foodID, string& name, string& supplierID, double& price)
{
    string delimiter = ",";
    int pos=oneLine.find(delimiter);
    string token = oneLine.substr(0,pos);
    foodID = token;
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
}