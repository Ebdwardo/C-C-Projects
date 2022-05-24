// Name: Eduardo Teodosio Campuzano
// Description: This program displays a menu of choices to a user
//              and performs the chosen task. It will keep asking a user to
//              enter the next choice until the choice of 'Q' (Quit) is entered.
//              //---- is where you should add your own code

#include <iostream>
#include <string>
#include "LinkedList.h"

using namespace std;

void printMenu();

int main()
{
    // local variables, can be accessed anywhere from the main method
    char input1 = 'Z';
    string inputInfo;
    string foodName, oldName, newName;
    int id;
    double price;
    string line;
    bool success = false;

    // instantiate a Linked List object
    LinkedList* list1 = new LinkedList();

    printMenu();

    do  // will ask for user input
    {
        cout << "\nWhat action would you like to perform?\n";
        cin.get(input1);
        input1 = toupper(input1);
        cin.ignore(20, '\n'); //flush the buffer
        // matches one of the case statement
        switch (input1)
        {
            case 'A':   //Add the food
                cout << "Please enter the food information:\n";
                cout << "Enter the food name:\n";
                getline(cin, foodName);
                cout << "Enter food id:\n";
                cin >> id;
                cout << "Enter the food price:\n";
                cin >> price;
                cin.ignore(20, '\n');    //flush the buffer

                success = list1->add(foodName, id, price);

                if (success == true)
                    cout << "The food \"" << foodName << "\" is added\n";
                else
                    cout << "The food \"" << foodName << "\" is NOT added\n";
                break;

            case 'C':  //Change food name
                cout << "Please enter the food ID which you want to change the name:\n";
                cin >> id;
                cin.ignore(20, '\n'); //flush the buffer
                cout << "\nPlease enter the new name: ";
                cin >> foodName;

                success = list1->changeFoodName(id, foodName);

                if (success == true)
                    cout << "\nFood with ID #: " << id << " name was changed\n";
                else
                    cout << "\nFood with ID #: " << id << " does not exist\n";
                break;

            case 'D':   //Display all foods

                list1->printFoodList();
                break;

            case 'F':   //Find a food
                cout << "\nPlease enter the food id you want to search:\n";
                cin >>id;
                cin.ignore(20, '\n');   //flush the buffer

                success = list1->isFound(id);

                if (success == true)
                {
                    cout << "\nFood with ID #: " << id << " was found\n";
                }
                else
                    cout << "\nFood with ID #: " << id << " was not found\n";
                break;

            case 'P':  //Change a food price
                cout << "\nPlease enter the food id you want to change the price:\n";
                cin >> id;

                success = list1->isFound(id);

                if (success)  //food found inside
                {
                    cout << "\nPlease enter the new food price:\n";
                    cin >> price;
                    cin.ignore(20, '\n');   //flush the buffer

                    list1->changeFoodPrice(id, price);

                    cout << "Food with ID #: " << id << " price was updated\n";
                }
                else
                    cout << "Food with ID #: " << id << " does not exist\n";
                break;

            case 'R':  //Remove a food from the list by ID
                cout << "\nPlease enter the food ID to remove:\n";
                cin >> id;
                cin.ignore(20, '\n');   //flush the buffer

                success= list1->removeById(id);

                if (success == true)
                    cout << "\nFood with ID #: " << id << " was removed\n";
                else
                    cout << "\nFood with ID #: " << id << " does not exist\n";
                break;

            case 'S':  //Remove a food from the list by name
                cout << "Please enter the food name to remove:\n";
                cin >> foodName;

                success = list1->removeByName(foodName);

                if (success == true)
                    cout << "\nFood with name: " << foodName << " was removed\n";
                else
                    cout << "\nFood with name: " << foodName << " does not exist\n";
                break;

            case 'Q':   //Quit
                delete list1;
                break;

            case '?':   //Display Menu
                printMenu();
                break;

            default:
                cout << "Unknown action\n";
                break;
        }
    } while (input1 != 'Q');
    return 0;
}

/** The method printMenu displays the menu to a user**/
void printMenu()
{
    cout << "Choice\t\tAction\n";
    cout << "------\t\t------\n";
    cout << "A\t\tAdd Food\n";
    cout << "C\t\tChange A Food Name\n";
    cout << "D\t\tDisplay All Foods\n";
    cout << "F\t\tFind A Food\n";
    cout << "P\t\tChange Food Price\n";
    cout << "R\t\tRemove Food by ID\n";
    cout << "S\t\tRemove Food by Name\n";
    cout << "Q\t\tQuit\n";
    cout << "?\t\tDisplay Help\n\n";
}