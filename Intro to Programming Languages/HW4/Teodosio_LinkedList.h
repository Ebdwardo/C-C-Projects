//
// Created by Eduardo Teodosio on 7/5/2020.
//
// This is the Zombie linkedList class, it is made up of nodes that store Zombies;

#ifndef ASSIGNMENT4_TEODOSIO_LINKEDLIST_H
#define ASSIGNMENT4_TEODOSIO_LINKEDLIST_H
#include "Zombie.h"

class Node{
public:
    Node();

    Zombie data;
    Node* next;
};

class linkedList{
private:
    Node* head;
public:
    linkedList();
    linkedList(Node*);
    ~linkedList();

    void AddToFront(Zombie data);
    void AddToEnd(Zombie data);
    bool AddAtIndex(int index, Zombie data);

    char RemoveFromFront();
    char RemoveFromEnd();
    void RemoveTheFirst(Zombie data);
    void RemoveAllOf(Zombie data);

    bool ElementsExists(Zombie data);
    Node* Find(Zombie data);
    int IndexOf(Zombie data);

    char RetrieveFront();
    char RetrieveEnd();
    char Retrieve(int index);

    void PrintList();
    void Empty();
    int Length();
};

#endif //ASSIGNMENT4_TEODOSIO_LINKEDLIST_H
