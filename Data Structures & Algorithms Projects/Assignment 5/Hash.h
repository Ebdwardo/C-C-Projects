// Name of Author: Eduardo Teodosio Campuzano
// Description: this is where you need to design functions on Hash hashTable,
// such as hashInsert, hashDelete, hashSearch and hashDisplay

#ifndef ASSIGNMENT5_HASH_H
#define ASSIGNMENT5_HASH_H

#endif //ASSIGNMENT5_HASH_H

#include "LinkedList.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <math.h>

using namespace std;

class Hash
{
private:
    LinkedList* hashTable;     //hashTable is a one-dimensional array of LinkedList
    int m;                     //slots number of the hash table
public:
    Hash(int size);
    ~Hash();
    bool hashInsert(string foodID, string name, string supplierID, double price);
    bool hashDelete(string foodID, string name, string supplierID);
    bool hashSearch(string foodID, string name, string supplierID);
    void hashDisplay();
    int hashFunction(string key);

    //add any other auxiliary functions here
    //----

    // creates a string from all three parameters (forms the key) to use in the hash function
    string getKey(string foodID, string name, string supplierID);
};

//constructor
Hash::Hash(int size)
{
    hashTable = new LinkedList[size];
    m = size;
}

//Destructor
Hash::~Hash()
{
    for (int i = 0; i < m; ++i) {
        if (hashTable[i].getHead() != nullptr){
            hashTable[i].~LinkedList();
        }
    }
    delete[] hashTable;
}

//hashInsert inserts a Food with the relevant info. into the hashTable.
//it returns true if the data is inserted successfully and false otherwise
bool Hash::hashInsert(string foodID, string name, string supplierID, double price)
{
    // slot value is the position the food is going to be inserted and we get that by passing the key to the hash function
    int slotValue = hashFunction(getKey(foodID, name, supplierID));
    hashTable[slotValue].insertFood(foodID, name, supplierID, price);

    return true;
}

//hashDelete deletes a Food with the relevant key from the hashTable.
//it returns true if it is deleted successfully and false otherwise
//Note: key is the combination of foodID, name and supplierID
bool Hash::hashDelete(string foodID, string name, string supplierID)
{
    string key = getKey(foodID, name, supplierID);
    int slot = hashFunction(key);
    if (hashSearch(foodID, name, supplierID)){
        hashTable[slot].deleteFood(foodID);
        cout << "\n";
        cout	<< setw(4) << foodID
                << setw(30) << name
                << setw(12) << supplierID
                << " is deleted from hash table." << endl;
        cout << endl;

        return true;
    }
    else{
        cout << "\n";
        cout	<< setw(4) << foodID
                << setw(30) << name
                << setw(12) << supplierID
                << " is NOT deleted from hash table." << endl;
        cout << endl;
        return false;
    }

}

//This function searches for a key inside the hash table and
//return true if it is found and false otherwise
//Note: key is the combination of foodID, name and supplierID
bool Hash::hashSearch(string foodID, string name, string supplierID)
{
    bool found = true;
    //find the slot in which the food should've been inserted and search the linked list that is there
    string key = getKey(foodID, name, supplierID);
    int slot = hashFunction(key);
    if (hashTable[slot].searchFood(foodID))
        found = true;
    else
        found = false;

    if (found){
        cout   << "\n" << left
               << setw(4) << foodID
               << setw(30) << name
               << setw(12) << supplierID
               << " is found inside the hash table." << endl;
        return true;
    }

    if(!found){
        cout	<< "\n" << left
                << setw(4) << foodID
                << setw(30) << name
                << setw(12) << supplierID
                << " is NOT found inside the hash table." << endl;
        return false;
    }
}

//This function prints all the elements from the hash hashTable.
void Hash::hashDisplay()
{
    for (int i = 0; i < m ; i++) {
        if (hashTable[i].getSize() != 0){
            cout << "HashTable[" << i << "], size = " << hashTable[i].getSize() << endl;
            hashTable[i].displayList();
        }
        else {
            cout << "HashTable[" << i << "] is empty, size = " << hashTable[i].getSize() << endl;
        }
        cout<< endl;
    }
}

//This is the hash function you will need to design, test and refine
//Given a Food key, the function should return the slot index where it
//will be hashed to

// My hash function works by using hash by multiplication
// I create a int representing the ascii value of all the characters summed up
// from there I hash by using the hash by multiplication given in the text
int Hash::hashFunction(string key)
{
    int asciiValueOfString = 0;
    int keyValue;
    double fibNum = (sqrt(5) - 1)/2;


    int i = 0;
    while(key[i] != '\0'){
        asciiValueOfString += key[i];
        i++;
    }

    double modOfKeyTimesFibNum = fmod(asciiValueOfString * fibNum, 1);

    keyValue = floor(m * modOfKeyTimesFibNum);
    return keyValue;

}

// gives me the key that I need to pass to the hash function
string Hash::getKey(string foodID, string name, string supplierID){
    return foodID + " " + name +  " " + supplierID;
}
