//
// Created by Eduardo Teodosio on 7/5/2020.
//

#include <iostream>
#include "Zombie.h"
#include "Teodosio_LinkedList.h"

using namespace std;

//Constructor or my node class
Node::Node() {
    data = NULL;
    next = NULL;
}

//Constructor for my linkedList Class
linkedList::linkedList() {
    head = NULL;
}

//Alternate Constructor
linkedList::linkedList(Node* head) {
    this->head = head;
}

//Destructor
linkedList::~linkedList() {
    delete head;
}


void linkedList::AddToFront(Zombie data) {
    //If the list is empty we create a new node and add it to the list
    if (head == NULL){
        Node* newHead = new Node;
        newHead->data = data;
        newHead->next = NULL;
        head = newHead;
    }
    else {
        //If the list exists we make it the new head but reassigning head to the new node
        Node* newHead = new Node;
        newHead->data = data;
        newHead->next = head;
        head = newHead;
    }
}


void linkedList::AddToEnd(Zombie data) {
    //If the list is empty we create a new node and add it
    if (head == NULL){
        Node* newHead = new Node;
        newHead->data = data;
        newHead->next = NULL;
        head = newHead;
    }
    else {
        //if it already exists we move our pointer to the end and assign it to be the tail
        Node* temp = head;
        while (temp->next != NULL){
            temp = temp->next;
        }
        Node* newNode = new Node();
        newNode->data = data;
        temp->next = newNode;
    }
}

bool linkedList::AddAtIndex(int index, Zombie data){
    int position = 0;
    Node* current = head;
    Node* previous;
    Node* nodeToInsert = new Node;

    //We use the position and index to walk our nodes to where we want them to be
    while (position < index){
        // Previous will always be behind current and current will be on the index we need to add
        previous = current;
        current = current->next;
        position++;
    }

    // So we put the new node in between by making the previous look at current and the node we inserted look at current
    nodeToInsert->data = data;
    nodeToInsert->next = current;
    previous->next = nodeToInsert;

    return true;
}

char linkedList::RemoveFromFront() {
    //If the list is empty dont do anything
    if (head == NULL){
        return NULL;
    }
    else {
        // Have 2 pointers looking at the head so we can delete one and reassign the other to the next value;
        Node* deleteNode = head;
        Node* newHead = head;

        head = newHead->next;
        deleteNode ->next = NULL;


        delete deleteNode;
        return newHead->data.getType();
    }
}


char linkedList::RemoveFromEnd() {
    char data;
    Node* temp = head;

    // If list is empty dont do anything
    if (head == NULL){
        return NULL;
    }

    // If there's only one item delete and return it
    if (head->next == NULL) {
        data = head->data.getType();
        delete head;
        return data;
    }
    else {
        //Walk the pointer to the second to last position
        while (temp->next->next != NULL){
            temp = temp->next;
        }
        // Get the data from the last node
        // Since we are on the 2nd to last we can delete the one if front of us freely
        data = temp->next->data.getType();
        temp->next = NULL;
        delete temp->next;

        return data;

    }
}


void linkedList::RemoveTheFirst(Zombie data) {
    Node* current = head;
    Node* previous = new Node;

    //Make sure we have correct characters
    if (data.getType() == 'R' || data.getType() == 'Y'||data.getType() == 'G'||data.getType() == 'B' || data.getType() == 'M' || data.getType() == 'B'){
        // Walk the pointer to where we need it to be
        while (current->data.getType() != data.getType()){
            //Previous will always be behind the current
            previous = current;
            current = current->next;
        }
        //Since we want to delete current we make previous look ahead of current
        //and then we are free to delete current
        previous-> next = current->next;
        current->next = NULL;
        delete current;
    }
    else {
        return;
    }

}

//
void linkedList::RemoveAllOf(Zombie data) {
    Node* current = head;
    Node* previous = new Node;
    while (current->next != NULL){
        if (current->data == data){
            previous-> next = current->next;
            current->next = NULL;
            delete current;
            current = head;
        }
        previous = current;
        current = current->next;
    }
}

bool linkedList::ElementsExists(Zombie data) {
    //Walk through the list and see if the thing we asked exists
    Node* temp = head;
    while (temp != NULL){
        if (temp->data == data)
            return true;
        else
            temp = temp -> next;
    }
    return false;
}


Node* linkedList::Find(Zombie data) {
    // Walk through the list and return a node to the item we want to find
    Node* temp = head;
    while (temp->data.getType() != data.getType()){
        if (temp->next == NULL){
            cout << "zombie not found" << endl;
            return NULL;
        }
        temp = temp ->next;
    }
    cout << "Node found" << endl;
    return temp;
}

int linkedList::IndexOf(Zombie data) {
    // Walk through the list and increase our counter until we get to the index of what we want to find
    Node* temp = head;
    int index = 0;
    while (temp->data.getType() != data.getType()){
        temp = temp -> next;
        index++;
    }
    return index;
}

char linkedList::RetrieveFront() {
    //Return the information in the first node;
    Node* temp = head;
    if (temp == NULL){
        return NULL;
    } else{
        return temp->data.getType();
    }
}

char linkedList::RetrieveEnd() {
    //Return the information in the last node;
    Node* temp = head;
    while (temp->next != NULL){
        temp = temp->next;
    }
    return temp->data.getType();
}

char linkedList::Retrieve(int index) {
    // Return the info at a user specified node;
    int count = 0;
    Node* temp = head;
    while (temp->next != NULL){
        count++;
        temp = temp->next;
    }
    if (count < index){
        return NULL;
    } else{
        Node* tracker = head;
        for (int i = 0; i < index; i++) {
            tracker = tracker->next;
        }
        return tracker->data.getType();
    }
}

void linkedList::PrintList() {
    //If the list is empty tell the user
    Node* temp = head;
    if (temp == NULL){
        cout << "list empty"<< endl;
    }
    else{
        //Walk through the list and print the character stored in each node
        while (temp != NULL){
            cout << temp->data.getType() << " ";
            temp = temp -> next;
        }
        cout << endl;
    }
}


void linkedList::Empty() {
    //Walk through the list and delete every node one by one
    Node* temp  = head;
    while (temp != NULL){
        temp = temp->next;
        delete head;
        head = temp;
    }
}

int linkedList::Length() {
    //Walk through the list and increase our counter by the amount of items in the list
    Node* temp = head;
    int length = 0;
    while (temp != NULL){
        temp = temp->next;
        length++;
    }
    return length;
}
