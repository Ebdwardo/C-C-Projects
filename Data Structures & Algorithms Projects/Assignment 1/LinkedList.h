//
// Created by Eduardo Teodosio on 9/2/2020.
//

#ifndef CSE310_LINKEDLIST_H
#define CSE310_LINKEDLIST_H

#endif //CSE310_LINKEDLIST_H
// Your Name: Eduardo Teodosio Campuzano
// Description: a linked list class that stores food

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//Food represents a food information
struct Food
{
    string foodName;
    int id;
    double price;
    struct Food* next;
};

//class LinkedList will contains a linked list of foods
class LinkedList
{
private:
    struct Food* head;

public:
    LinkedList();
    ~LinkedList();
    bool isFound(int foodId);
    bool add(string foodName, int foodId, double foodPrice);
    bool removeById(int foodId);
    bool removeByName(string foodName);
    bool changeFoodName(int foodId, string newFoodName);
    bool changeFoodPrice(int foodId, double newPrice);
    void printFoodList();
};

//Constructor to initialize an empty linked list
LinkedList::LinkedList()
{
    head = nullptr;
}

//Destructor
//Before termination, the destructor is called to free the associated memory occupied by the existing linked list.
//It deletes all the nodes including the head and finally prints the number of nodes deleted by it.
//Return value: Prints the number of nodes deleted by it.
LinkedList::~LinkedList()
{
    int foodCount = 0;
    Food* temp = head;
    while(head != nullptr){
        temp = head->next;
        head->next = nullptr;
        delete head;
        head = temp;
        foodCount++;
    }
    cout << "The number of deleted food items is: " << foodCount <<"\n";
}

//A function to identify whether the parameterized food is inside the LinkedList or not.
//Return true if it exists and false otherwise.
bool LinkedList::isFound(int foodId)
{
    Food* temp = head;
    while (temp != nullptr){
        if (temp->id == foodId){
            return true;
        }
        temp = temp->next;
    }
    return false;
}

//Creates a new node and inserts it into the list at the right place.
//It maintains an alphabetical ordering of foods by their names. Each
//food item has a unique id, if two food items have exactly the same name,
//then insert it into the list in the increasing order of their IDs.
//Return value: true if it is successfully inserted and false in case of failures.
bool LinkedList::add(string foodName, int foodId, double foodPrice)
{
    Food* newNode = new Food;
    newNode->foodName = foodName;
    newNode->id = foodId;
    newNode->price = foodPrice;
    newNode->next = nullptr;

    // check to see is list is empty
    if (head == nullptr){
        head = newNode;
        return true;
    }

    //else go through the list
    //I want to sort the list alphabetically and add the newest node
    // in the list where it belongs or at the end
    Food* current = head;
    Food* previous = nullptr;

    while (current != nullptr){
        //if statement will happen when we reach point where newnode has to be inserted in the list
        if (current->foodName.compare(newNode->foodName) > 0) {
            if (previous != nullptr){
                previous->next = newNode;
            }
            newNode->next = current;
            if (previous == nullptr)
                head = newNode;
            return true;
        }
        if (current->foodName.compare(newNode->foodName) == 0){
            if (current->id > newNode->id){
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

//Removes the given food by Id from the list, releases the memory and updates pointers.
//Return true if it is successfully removed, false otherwise.
bool LinkedList::removeById(int foodId)
{
    Food* current = head;
    Food* previous = nullptr;

    while (current != nullptr){
        if (current->id == foodId){
            if (previous != nullptr){
                previous-> next = current->next;
                current->next = nullptr;
                delete current;
            }
            if (previous == nullptr){
                head = current->next;
                delete current;
            }
            return true;
        }
        previous = current;
        current = current->next;
    }
    return false;

}

//Removes the given food by name from the list, releases the memory and updates pointers.
//Return true if it is successfully removed, false otherwise. Note: all foods with
//the parameterized name should be removed from the list.
bool LinkedList::removeByName(string foodName)
{
    Food* current = head;
    Food* previous = nullptr;

    //if empty there is nothing to remove
    if (current == nullptr){
        return false;
    }

    //Check the current node
    while (current != nullptr){
        if (current->foodName == foodName){
            if (previous != nullptr){
                previous-> next = current->next;
                current->next = nullptr;
                delete current;
                current = previous->next;
            }
            if (previous == nullptr){
                head = current->next;
                delete current;
                current = head;
            }
            continue;
        }
        previous = current;
        current = current->next;
    }
    return true;

}

//Modifies the name of the given Food item. Return true if it modifies successfully and
//false otherwise. Note: after changing a food name, the linked list must still be
//in alphabetical order of foods name
bool LinkedList::changeFoodName(int oldFoodId, string newFoodName)
{
    Food* temp = head;
    double price;
    while (temp != nullptr){
        if (temp->id == oldFoodId){
            price = temp->price;
            if (removeById(oldFoodId)){
                add(newFoodName, oldFoodId, price );
                return true;
            }
        }
        temp = temp->next;
    }
    return false;
}

//Modifies the price of the given food item. Return true if it modifies successfully and
//false otherwise.
bool LinkedList::changeFoodPrice(int foodId, double newPrice)
{
    bool changed = false;
    Food* temp = head;

    while (temp != nullptr){
        if (temp->id == foodId){
            temp->price = newPrice;
            changed = true;
        }
        temp = temp->next;
    }

    return changed;

}

//Prints all the elements in the linked list starting from the head node.
void LinkedList::printFoodList()
{

    Food* temp = head;
    if (temp == nullptr){
        cout<< "the list is empty\n";
    }
    while (temp != nullptr){
        cout << left << setw(7) << temp->foodName;
        cout << right << setw(5) << temp->id;
        cout << right << setw(7) << "$" << temp->price << endl;
        temp = temp->next;
    }
}
