/*
Author: Eduardo Teodosio Campuzano
Date: 6/27/2020
Description: This code uses the Zombie linkedList class I created and adds, removes, and prints the nodes
in a conga line. The conga line is created by generating zombie objects and placing them in the linked list.
through actions defined in the main.
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Zombie.h"
#include "Teodosio_LinkedList.h"
#include <ctime>

using namespace std;

int main(int argc, char *argv[]) {
    //Forward Declare all our stuff
    srand((int)time(0));
    int randomNumber(int, int );
    Zombie generateZombie();
    void Engine(linkedList*, Zombie);
    void Caboose(linkedList*, Zombie);
    void JumpInLine(linkedList*, Zombie);
    void EveryoneOut(linkedList*, Zombie);
    void YouAreDone(linkedList*, Zombie);
    void Brains(linkedList*, Zombie);
    void RainbowBrains(linkedList*, Zombie);
    int rounds = 0;
    int counter = 1;

    //Create a zombie linked list and run a rainbow brains and random amount of brains actions;
    linkedList* zombieList = new linkedList;
    RainbowBrains(zombieList, generateZombie());
    for (int i = 1; i < randomNumber(2,5) ; i++) {
        Brains(zombieList, generateZombie());
    }

    // See how many rounds are going to be run;
    cout << "How many rounds would you like to run?: " << endl;
    cin >> rounds;

    // Run a random action for each round the user wants
    for (int j = 0; j < rounds; ++j) {
        cout << "Round: "<< counter << endl;
        cout << "The party continues!" << endl;
        cout << "Size: " << zombieList->Length() << ":: ";
        zombieList->PrintList();
        Zombie substitute = generateZombie();
        char zombieInUse = substitute.getType();
        switch (randomNumber(1,7)) {
            case 1:
                cout << zombieInUse << " Jumps in front of the line! (Engine!)" << endl;
                Engine(zombieList, substitute);
                zombieList->PrintList();
                break;
            case 2:
                cout << zombieInUse << " Makes his way to the back! (Caboose!)" << endl;
                Caboose(zombieList, substitute);
                zombieList->PrintList();
                break;
            case 3:
                cout << zombieInUse << " Zombies join the line! (JumpInLine!)" << endl;
                JumpInLine(zombieList, substitute);
                zombieList->PrintList();
                break;
            case 4:
                cout << zombieInUse << " type zombies all have to go! (Everyone Out!)" << endl;
                EveryoneOut(zombieList, substitute);
                zombieList->PrintList();
                break;
            case 5:
                cout << zombieInUse << " needs to get out of here! (You're Done!)" << endl;
                YouAreDone(zombieList, substitute);
                zombieList->PrintList();
                break;
            case 6:
                cout << zombieInUse << " brought friends with them! (Brains!)" << endl;
                Brains(zombieList, substitute);
                zombieList->PrintList();
                break;
            case 7:
                cout << zombieInUse << " brings the party with them! (Rainbow Brains!)" << endl;
                RainbowBrains(zombieList, substitute);
                zombieList->PrintList();
                break;

        }
        cout << "************************************************************************************" << endl;
        counter++;
    }
    return 0;
}

//Random number generator to help us do stuff
int randomNumber(int min,int max){
    // Have a random seed in the main. We get a value in the range by using the % to divide rand() to get a number
    // between the ranges and then we offset that value by the minimum so it falls between the range of numbers
    int r = (rand() % (max - min +1)) + min  ;
    return r;
}

// We use a random number to generate a a zombie with a character
Zombie generateZombie(){
    int randomNum = randomNumber(1, 6);
    switch (randomNum) {
        case 1:
            return Zombie('R');
        case 2:
            return Zombie('Y');
        case 3:
            return Zombie('G');
        case 4:
            return Zombie('B');
        case 5:
            return Zombie('M');
        case 6:
            return Zombie('C');
    }
}

// Here we implement our actions using the functions of our linkedList class
void Engine(linkedList* list, Zombie zom){
    list->AddToFront(zom);
}

void Caboose(linkedList* list, Zombie zom){
    list->AddToEnd(zom);
}

void JumpInLine(linkedList* list, Zombie zom){
    int position = randomNumber(1, list->Length());
    list->AddAtIndex(position, zom);
}

void EveryoneOut(linkedList* list, Zombie zom){
    list->RemoveAllOf(zom);
}

void YouAreDone(linkedList* list, Zombie zom){
    list->RemoveTheFirst(zom);
}

void Brains(linkedList* list, Zombie zom){
    list->AddToFront(zom);
    list->AddToEnd(zom);
    list->AddAtIndex(((list->Length())/2)+1, zom);
}

void RainbowBrains(linkedList* list, Zombie zom){
    list->AddToFront(zom);
    list->AddToEnd(Zombie('R'));
    list->AddToEnd(Zombie('Y'));
    list->AddToEnd(Zombie('G'));
    list->AddToEnd(Zombie('B'));
    list->AddToEnd(Zombie('M'));
    list->AddToEnd(Zombie('C'));
}