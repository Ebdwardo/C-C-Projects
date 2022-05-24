//********************************************************************************
// Name: Eduardo Teodosio Campuzano
// Description: This program displays a menu of choices to a user
//              and performs the chosen task. It will keep asking a user to
//              enter the next choice until the choice of 'Q' (Quit) is entered.
//             	//---- is where you should add your own code
//********************************************************************************

#include <iostream>
#include <string>

//include the header file here
#include "Heap.h"

using namespace std;

void printMenu();

int main()
{
    char input1 = 'Z';
    string foodName;
    int key, newKey;
    int capacity, index = -1;   //1D array capacity and index
    double price;
    bool success = false;

    Food oneFood;

    //a variable used to represent a Heap object
    Heap* heap1 = nullptr;
    printMenu();

    do {
        cout << "\nWhat action would you like to perform?" << endl;
        cin.get(input1);
        input1 = toupper(input1);
        cin.ignore(20, '\n');	//flush the buffer

        // matches one of the cases
        switch (input1)
        {
            case 'C':	//create empty Heap with the relevant capacity
                cout << "\nPlease enter the heap capacity: ";
                cin >> capacity;
                heap1 = new Heap(capacity);
                cin.ignore(20, '\n');	//flush the buffer
                break;

                //delete the heap, call the destructor explicitly. Re-initialize heap1
                //with capacity 5
            case 'D':
                cout << "\nDelete the heap" << endl;
                heap1->~Heap();
                heap1 = new Heap(5);
                break;

            case 'E':	//Extract the maximum node
                if (heap1 == nullptr){
                    cout << "Empty heap, can NOT extract max" << endl;
                }
                else{
                    cout << "Before extract heap max operation:" << endl;
                    heap1->printHeap();
                    cout  << "After extract heap max operation:" << endl;
                    heap1->extractHeapMax();
                    heap1->printHeap();
                }
                break;

            case 'F':	//Find a food
                cout << "\nEnter the food key you want to search: ";
                cin >> key;
                cout << endl;
                cin.ignore(20, '\n');	//flush the buffer

                if (heap1->isFound(key) != -1){
                    cout << "Food with key: " << key << " is found" << endl;
                }
                else{
                    cout << "Food with key: " << key << " is NOT found" << endl;
                }

                break;

            case 'I':	//Insert a Food
                cout << "\nEnter the food name: ";
                getline(cin, foodName);
                cout << endl;
                cout << "Enter food key: ";
                cin >> key;
                cout << endl;
                cout << "Enter the food price: ";
                cin >> price;
                cout << endl;
                cin.ignore(20, '\n');	//flush the buffer

                if (heap1->isFound(key) == -1){
                    success = heap1->insert(key, foodName, price);
                    if (success == true){
                        cout << "The food \"" << foodName << "\" is added" << endl;
                    }
                    break;
                }
                else{
                    cout << "Duplicated food item. Not added" << endl;
                    cout << "\nThe food \"" << foodName << "\" is NOT added" << endl;
                    break;
                }


            case 'K':	//increase the key
                cout << "\nEnter the old food key you want to increase: ";
                cin >> key;
                cout << endl;
                cout << "\nEnter the new key value: ";
                cin >> newKey;
                cout << endl;
                cin.ignore(20, '\n');	//flush the buffer

                if (heap1->isFound(key) != -1){
                    index = heap1->isFound(key);
                    oneFood.key = newKey;

                    if (newKey < heap1->getFoodArr()[index].key){
                        cout << "Increase key error: new key is smaller than current key" << endl;
                        break;
                    }
                    if (heap1->isFound(newKey) != -1){
                        cout << "The new key you entered already exist, increase key operation failed" << endl;
                        break;
                    }
                    cout << "Before increase key operation:" << endl;
                    heap1->printHeap();
                    cout << "Food with old key: " << key << " is increased to new key: " << newKey << endl;
                    heap1->increaseKey(index, oneFood);
                    cout << "After increase key operation:"<< endl;
                    heap1->printHeap();

                    break;
                }
                else{
                    cout << "The old key you try to increase does not exist" << endl;
                    break;
                }


            case 'M':	//get the maximum node
                oneFood = heap1->getHeapMax();
                if(heap1->getSize() == 0){
                    cout << "Empty heap, cannot get max node" << endl;
                    break;
                }
                else{
                    cout << "The maximum heap node is:" << endl;
                    cout << setw(5) << oneFood.key
                         << setw(8) << oneFood.foodName
                         << setw(8) << fixed << setprecision(2) << oneFood.price << endl;

                    break;
                }

            case 'P':	//Print heap contents
                heap1->printHeap();
                break;

            case 'Q':	//Quit
                delete heap1;
                break;

            case '?':	//Display Menu
                printMenu();
                break;

            default:
                cout << "Unknown action\n";
                break;
        }
    } while (input1 != 'Q');
    return 0;
}

/**The function displays the menu to a user**/
void printMenu()
{
    cout << "Choice\t\tAction\n";
    cout << "------\t\t------\n";
    cout << "C\t\tCreate a heap\n";
    cout << "D\t\tDelete the heap\n";
    cout << "E\t\tExtract max node\n";
    cout << "F\t\tFind a food by key\n";
    cout << "I\t\tInsert a food\n";
    cout << "K\t\tIncrease the key\n";
    cout << "M\t\tGet the max node\n";
    cout << "P\t\tPrint the heap\n";
    cout << "Q\t\tQuit\n";
    cout << "?\t\tDisplay Help\n\n";
}