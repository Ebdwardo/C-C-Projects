//********************************************************************
// Name of Author: Eduardo Teodosio Campuzano
// Description: linked list that represents the arrival cities

#ifndef CSE310ASSIGNMENT07_LINKEDLIST_H
#define CSE310ASSIGNMENT07_LINKEDLIST_H

#endif //CSE310ASSIGNMENT07_LINKEDLIST_H

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//struct ArrCity represents an arrival city information with
//price info. from the departure city
struct ArrCity
{
    string arrCityName;
    int price;
    struct ArrCity* next;
};

//class LinkedList will contains a linked list of ArrCity
class LinkedList
{
private:
    struct ArrCity* head;

public:
    LinkedList();
    ~LinkedList();
    ArrCity* getHead();
    ArrCity* findArrCity(string aCity);
    bool addArrCity(string aCity, int price);
    void printArrCityList();
    int getName(int pos, string name);
    int getSize();
};

LinkedList::LinkedList()
{
    head = nullptr;
}

LinkedList::~LinkedList()
{
    ArrCity* temp = getHead();
    while(head != nullptr){
        temp = head->next;
        head->next = nullptr;
        delete head;
        head = temp;
    }
}

ArrCity * LinkedList::getHead() {
    return head;
}

ArrCity * LinkedList::findArrCity(string aCity) {
    ArrCity* temp = head;
    while (temp != nullptr){
        if (temp->arrCityName == aCity){
            return temp;
        }
        temp = temp->next;
    }
    return temp;
}

bool LinkedList::addArrCity(string aCity, int price) {
    ArrCity* newNode = new ArrCity;
    newNode->arrCityName = aCity;
    newNode->price = price;
    newNode->next = nullptr;

    // check to see is list is empty
    if (head == nullptr){
        head = newNode;
        return true;
    }

    //else go through the list
    //I want to sort the list alphabetically and add the newest node
    // in the list where it belongs or at the end
    ArrCity* current = head;
    ArrCity* previous = nullptr;

    while (current != nullptr){
        //if statement will happen when we reach point where newnode has to be inserted in the list
        if (current->arrCityName.compare(newNode->arrCityName) > 0) {
            if (previous != nullptr){
                previous->next = newNode;
            }
            newNode->next = current;
            if (previous == nullptr)
                head = newNode;
            return true;
        }
        if (current->arrCityName.compare(newNode->arrCityName) == 0){
            if (current->price > newNode->price){
                if (previous != nullptr){
                    previous->next = newNode;
                }
                newNode->next = current;
                if (previous == nullptr)
                    head = newNode;
                return true;
            }

        }

        previous = current;
        current = current->next;
    }

    previous->next = newNode;
    return true;
}


//Prints all the elements in the linked list starting from the head.
void LinkedList::printArrCityList()
{
    struct ArrCity *temp = head;

    if(head == NULL)
    {
        cout << "Arrival city list is empty\n";
        return;
    }
    while(temp!= NULL)
    {
        cout << temp->arrCityName << "(" << temp->price << "),";
        temp = temp->next;
    }
    cout <<"\n";
}

int LinkedList::getName(int cap, string name) {
    ArrCity* temp = head;
    for (int i = 0; i <= cap; i++) {
        if (temp->arrCityName == name){
            return i;
        }
        temp = temp->next;
    }
    return -1;
}

int LinkedList::getSize() {
    ArrCity* temp = head;
    int num = 0;
    while (temp != nullptr){
        num++;
        temp = temp->next;
    }
    return num;
}