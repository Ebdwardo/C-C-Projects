//************************************************************************
// Author: Eduardo Teodosio Campuzano
// Description: Red black tree implementation. See RedBlackTree.h
//              for the tree definition. You need to add your own
//              code at //---- position
//************************************************************************

#include "RedBlackTree.h"

using namespace std;

//*******************************************************************
//constructor
RedBlackTree::RedBlackTree()
{
    root = NULL;
}

//*******************************************************************
//destructor
RedBlackTree::~RedBlackTree()
{
    int nodeSize = deleteNode(root);
    cout << "The number of nodes deleted: " << nodeSize << endl;
}

//**************************************************************
//This function return the root of the red-black tree
Node* RedBlackTree::getRoot()
{
    return this->root;
}

//*******************************************************************
//delete the sub-tree rooted at 'node' and return number of nodes deleted
//This can be defined as a recursive function
int RedBlackTree::deleteNode(Node *node)
{
    if(node == NULL)
        return 0;
    else
    {
        //add your codes here
        //----
        if (node->leftChild == nullptr){
            transplant(node, node->rightChild);
        }
        else if (node->rightChild == nullptr){
            transplant(node, node->leftChild);
        }
        else{
            Node* y  = findMinimumNode(node->rightChild);
            if (y->parent != node){
                transplant(y,y->rightChild);
                y->rightChild = node->rightChild;
                y->rightChild->parent = y;
            }
            else{
                transplant(node, y);
                y->leftChild = node->leftChild;
                y->leftChild->parent = y;
            }
        }
    }
}

//****************************************************************
//This is the general BST insertion operation.
//It does not care about the color of the newly added node.
void RedBlackTree::insertNode(Node *node){
    Node* y = new Node();
    Node* x = root;

    while ( x != nullptr){
        y=x;
        if (compareNodes(node, getKey(x)) < 0){
            x = x->leftChild;
        } else{
            x = x->rightChild;
        }
    }

    node->parent = y;
    if(this->root == NULL) // if the tree is empty
    {
        //add your codes here
        //----
        root = node;
    }
    else if(compareNodes(node,getKey(y)) < 0)
    {
        //add your codes here
        //----
        y->leftChild = node;
    }
    else{
        y->rightChild = node;
    }

    //At the end, need to call fixup() in case the newly
    //added node's parent is also RED
    fixUp(node);
}

//*******************************************************************
//At beginning, each newly added node will always be RED,
//this may violate the red-black tree property #4. fixUp()
//function will restore the property.
void RedBlackTree::fixUp(Node *z)
{
    if(z == root)
    {
        z->color = "BLACK";
        return;
    }

    //if z's color is 'RED' and its parent's color is also 'RED'
    while(z->color.compare("RED") == 0 &&
          z->parent != NULL &&
          z->parent->color.compare("RED") == 0)
    {
        //add your codes here
        //----
        //----

    }//end while

    //make sure the root is always 'BLACK'
    this->root->color = "BLACK";
}

//*****************************************************
//This function print the pre-order traversal of the
//subtree rooted at 'node'.It's a recursive function
void RedBlackTree::preOrderTraversal(Node *node)
{
    if(node == NULL)
    {
        return;
    }
    else
    {
        cout << node->name << endl;
        preOrderTraversal(node->leftChild);
        preOrderTraversal(node->rightChild);
    }
}

//**************************************************
//This function print the in-order traversal of the
//subtree rooted at 'node'.It's a recursive function
void RedBlackTree::inorderTraversal(Node *node)
{
    if(node == NULL)
    {
        return;
    }
    else
    {
        inorderTraversal(node->leftChild);
        cout << node->name << endl;
        inorderTraversal(node->rightChild);
    }
}

//**************************************************
//This function print the post-order traversal of the
//subtree rooted at 'node'.It's a recursive function
void RedBlackTree::postOrderTraversal(Node *node)
{
    if(node == NULL)
    {
        return;
    }
    else
    {
        postOrderTraversal(node->leftChild);
        postOrderTraversal(node->rightChild);
        cout << node->name << endl;
    }
}

//**************************************************************
//This function returns a pointer points to the minimum node from
//the current sub-tree rooted at 'node'. It's a recursive function
Node* RedBlackTree::findMinimumNode(Node *node)
{
    if (node == NULL)
    {
        cout << "Tree is empty, no MINIMUM." << endl;
        return node;
    }
    else
    {
        Node* temp = node;
        while (temp->leftChild != nullptr){
            temp = temp->leftChild;
        }
        return temp;
    }
}

//**************************************************************
//This function returns a pointer points to the maximum node from
//the current sub-tree rooted at 'node'. It's a recursive function
Node* RedBlackTree::findMaximumNode(Node *node)
{
    if (node == NULL)
    {
        cout << "Tree is empty, no MAXIMUM." << endl;
        return node;
    }
    else
    {
        Node* temp = node;
        while (temp->rightChild != nullptr){
            temp = temp->rightChild;
        }
        return temp;
    }
}

//**************************************************************
//This function search the tree for a given key of a Food
//Note: key is the combination of foodID, name, supplierID
//It returns a pointer points to the node if founded, otherwise return NULL
Node* RedBlackTree::treeSearch(Node* root,string foodID, string name, string supplierID) {
    string key2 = foodID + name + supplierID;

    if (root == nullptr || getKey(root) == key2) {
        if (getKey(root) == key2) {
            cout << left;
            cout << setw(5) << foodID
                 << setw(35) << name
                 << setw(15) << supplierID
                 << " is FOUND." << endl;
            return root;
        }
        else {

            cout << left;
            cout << setw(5) << foodID
                 << setw(35) << name
                 << setw(15) << supplierID
                 << " is NOT FOUND." << endl;
            return NULL;
        }
    }
    if (compareNodes(root, key2) > 0) {
        return treeSearch(root->leftChild, foodID, name, supplierID);
    } else {
        return treeSearch(root->rightChild, foodID, name, supplierID);
    }

}


//****************************************************
//This function left-rotate the BST at 'node'
    void RedBlackTree::leftRotate(Node *node)
    {
        if(node == NULL)
            return;

        //add your codes here
        //----
        //----
    }

//***************************************************
//This function right-rotate the BST at 'node'
void RedBlackTree::rightRotate(Node *node){
    if(node == NULL)
        return;

    //add your codes here
    //----
    //----
}



//**************************************************************
//This function finds the predecessor of the given 'node'
//it prints the relevant predecessor info. on screen.
    Node* RedBlackTree::findPredecessorNode(Node *node)
    {
        Node* predn = new Node();
        if(node->leftChild != nullptr){
            predn = findMaximumNode(predn->leftChild);
            cout << left;
            cout << "Its Successor is: " << endl;
            print(predn);
            return predn;
        }
        else if(node->leftChild == nullptr){
            Node* y = node->parent;
            while ( y != nullptr && node == y->leftChild){
                node = y;
                y = y->parent;
            }
            cout << left;
            cout << "Its Successor is: " << endl;
            print(y);
            return y;
        }
        else  //not found
        {
            cout << left;
            cout << "Its Successor does NOT EXIST"	<< endl;
            return predn;
        }
    }

//**************************************************************
//This function finds the successor of the given 'node'
//it prints the relevant successor info. on screen.
    Node* RedBlackTree::findSuccessorNode(Node *node)
    {
        Node* sn = new Node();
        if(node->rightChild != nullptr){
            sn = findMinimumNode(sn->rightChild);
            cout << left;
            cout << "Its Successor is: " << endl;
            print(sn);
            return sn;
        }
        else if(node->rightChild == nullptr){
            Node* y = node->parent;
            while ( y != nullptr && node == y->rightChild){
                node = y;
                y = y->parent;
            }
            cout << left;
            cout << "Its Successor is: " << endl;
            print(y);
            return y;
        }
        else  //not found
        {
            cout << left;
            cout << "Its Successor does NOT EXIST"	<< endl;
            return sn;
        }
    }

//**************************************************************
//This function find the minimum node of the entire red-black tree
//It print out the minimum node info. on screen if tree is not empty
//or print 'Tree is empty' message on screen.
    void RedBlackTree::treeMinimum()
    {
        if (root == NULL)
        {
            cout << "Tree is empty. No Minimum." << endl;
            return;
        }
        findMinimumNode(getRoot());
    }

//**************************************************************
//This function find the maximum node of the entire red-black tree
//It print out the maximum node info. on screen if tree is not empty
//or print 'Tree is empty' message on screen.
    void RedBlackTree::treeMaximum()
    {
        if (root == NULL)
        {
            cout << "Tree is empty. No Maximum." << endl;
            return;
        }

        findMaximumNode(getRoot());
    }

//******************************************************************
//This function print out the pre-order traversal of the entire tree
    void RedBlackTree::treePreorder()
    {
        Node* temp = root;
        preOrderTraversal(temp);
    }

//******************************************************************
//This function print out the in-order traversal of the entire tree
    void RedBlackTree::treeInorder()
    {
        Node* temp = root;
        inorderTraversal(temp);
    }

//******************************************************************
//This function print out the post-order traversal of the entire tree
    void RedBlackTree::treePostorder()
    {
        Node* temp = root;
        postOrderTraversal(temp);
    }

//******************************************************************
//Given a Food's key, this function first check whether the
//food is inside the tree or not, if it is inside, it will print
//its predecessor info. on screen, if not, it print an error message
    void RedBlackTree::treePredecessor(string foodID, string name, string supplierID)
    {
        if (root == NULL)
            cout << "Tree is empty. No Predecessor." << endl;
        else
        {
            Node* newNode = new Node;
            newNode->foodID = foodID;
            newNode->name = name;
            newNode->supplierID = supplierID;
            findPredecessorNode(newNode);
        }
    }

//******************************************************************
//Given a food's key, this function first check whether the
//food is inside the tree or not, if it is inside, it will print
//its successor info. on screen, if not, it print an error message
    void RedBlackTree::treeSuccessor(string foodID, string name, string supplierID)
    {
        if (root == NULL)
            cout << "Tree is empty. No Successor." << endl;
        else
        {
            Node* newNode;
            newNode->foodID = foodID;
            newNode->name = name;
            newNode->supplierID = supplierID;
            findSuccessorNode(newNode);
        }
    }

//**************************************************************
//This function create a node from the given info., then insert
//the node inside the red-black tree. Note: at beginning, the newly
//added node should always be 'RED'
    void RedBlackTree::treeInsert(string foodID, string name, string supplierID, double price)
    {
        Node* newNode = new Node;
        newNode->foodID = foodID;
        newNode->name = name;
        newNode->supplierID = supplierID;
        newNode->price = price;
        newNode->color = "RED";
        insertNode(newNode);
    }

//******************************************************************
//Given a 'node', this function prints all its information on screen
    void RedBlackTree::print(Node *node)
    {
        cout << left;
        cout << setw(5) << node->foodID
             << setw(35) << node->name
             << setw(15) << node->supplierID
             << setw(7) << fixed << setprecision(2) << node->price
             << setw(7) << node->color << endl;
    }

//**************************************************************
//Given a Node 'node1', this function compares it with another
//node's key.
//key is a string combination of foodID + name + supplierID
//It returns a negative number if in alphabetical order, key2 is
//in front of 'node1'; otherwise it returns a positive number
    int RedBlackTree::compareNodes(Node *node1, string key2)
    {
        string key1 = node1->name + node1->foodID+ node1->supplierID;
        return key1.compare(key2);
    }

    string RedBlackTree::getKey(Node *node) {
        return node->foodID+node->name+node->supplierID;
    }

void RedBlackTree::transplant(Node *node1, Node *node2) {
    if (node1->parent == nullptr){
        root = node2;
    }
    else if( node1 = node1->parent->leftChild){
        node1->parent->leftChild = node2;
    }
    else{
        node1->parent->rightChild = node2;
    }

    if (node2 != nullptr){
        node2->parent = node1->parent;
    }
}
