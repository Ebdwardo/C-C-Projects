// Name of Author: Eduardo Teodosio Campuzano
// Description: A simple linked list that implements a list of Food objects. A user can
//              perform searching, insertion or deletion on the linked list.

#ifndef ASSIGNMENT5_LINKEDLIST_H
#define ASSIGNMENT5_LINKEDLIST_H

#endif //ASSIGNMENT5_LINKEDLIST_H


#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

struct Food
{
    string foodName, foodID, supplierID ;
    double price;
    struct Food* next;
};

class LinkedList
{
private:
    struct Food* head;
    int size;
public:
    LinkedList();
    ~LinkedList();
    Food* getHead();
    int getSize();
    bool insertFood(string foodID, string foodName, string supplierID, double price);
    bool deleteFood(string foodID);
    bool searchFood(string foodID);
    void displayList();
};

//Constructor
LinkedList::LinkedList()
{
    head = NULL;
    size = 0;
}

//Destructor
LinkedList::~LinkedList()
{
    Food* temp = head;
    while(head != nullptr){
        temp = head->next;
        head->next = nullptr;
        delete head;
        head = temp;
    }
}

//Accessor for the head
Food* LinkedList::getHead()
{
    return head;
}

//Return number of foods inside the Linked list
int LinkedList::getSize()
{
    return size;
}

//Insert the parameter food at the head of the linked list.
//return true if it is inserted successfully and false otherwise
//Inserts at the head of the linked list
bool LinkedList::insertFood(string foodID, string foodName, string supplierID, double price)
{
    Food* newNode = new Food;
    newNode->foodName = foodName;
    newNode->foodID = foodID;
    newNode->price = price;
    newNode->supplierID = supplierID;
    newNode->next = nullptr;

    // check to see is list is empty
    if (head == nullptr){
        head = newNode;
        size++;
        return true;
    }
    else{
        // Insert at the head
        newNode->next = head->next;
        head->next = newNode;
        size++;
    }

    return true;
}

//Delete the food with the given foodID from the linked list.
//Return true if it is deleted successfully and false otherwise
bool LinkedList::deleteFood(string foodID)
{
    Food* current = head;
    Food* previous = nullptr;

    while (current != nullptr){
        if (current->foodID == foodID){
            if (previous != nullptr){
                previous-> next = current->next;
                current->next = nullptr;
                delete current;
                size--;
            }
            else {
                head = current->next;
                delete current;
                size--;
            }
            return true;
        }
        previous = current;
        current = current->next;
    }
    return false;
}

//This function searches the food list with the given foodID
//returns true if it is found, otherwise return false.
bool LinkedList::searchFood(string foodID)
{
    Food* temp = head;
    while (temp != nullptr){
        if (temp->foodID == foodID){
            return true;
        }
        temp = temp->next;
    }
    return false;
}

//This function displays the content of the linked list.
void LinkedList::displayList()
{
    struct Food *temp = head;
    if(head == NULL)
    {
        return;
    }
    while(temp != NULL)
    {
        cout << left;
        cout << setw(4) << temp->foodID
             << setw(30) << temp->foodName
             << setw(12) << temp->supplierID
             << setw(8) << temp->price << endl;

        temp = temp->next;
    }
}