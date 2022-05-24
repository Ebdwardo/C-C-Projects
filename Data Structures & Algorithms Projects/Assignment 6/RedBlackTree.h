//************************************************************************
// Author: Eduardo Teodosio Campuzano
// Description: Red black tree header file. It defines the node and the
// red black tree functionalities.
//************************************************************************
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <string>

using namespace std;

#ifndef REDBLACKTREE_H_
#define REDBLACKTREE_H_

//Node represents one node of the RBT which is a Food
struct Node
{
    string foodID, name, supplierID;
    double price;
    Node *parent;
    Node *leftChild;
    Node *rightChild;
    string color;
};

class RedBlackTree
{
private:
    Node *root;
public:
    RedBlackTree();
    ~RedBlackTree();
    Node* getRoot();
    int deleteNode(Node *node);
    void insertNode(Node *node);
    void fixUp(Node *node);

    void preOrderTraversal(Node *node);
    void inorderTraversal(Node *node);
    void postOrderTraversal(Node *node);

    Node* findMinimumNode(Node *node);
    Node* findMaximumNode(Node *node);
    Node* treeSearch(Node* root, string foodID, string name, string supplierID);
    void leftRotate(Node *node);
    void rightRotate(Node *node);
    Node* findPredecessorNode(Node *node);
    Node* findSuccessorNode(Node *node);

    void treeMinimum();
    void treeMaximum();
    void treePreorder();
    void treeInorder();
    void treePostorder();
    void treePredecessor(string foodID, string name, string supplierID);
    void treeSuccessor(string foodID, string name, string supplierID);
    void treeInsert(string foodID, string name, string supplierID, double price);

    void print(Node *node);
    int compareNodes(Node *node, string key);
    string getKey(Node* node);
    void transplant(Node* node1, Node* node2);

};

#endif