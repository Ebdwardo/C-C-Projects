/*
Author: Eduardo Teodosio Campuzano
Date: 6/27/2020
Description: This code generates a random "land" defined by user input and a 2d array.
It uses a random number generator to simulate the probability for the neighbors and starting land
It then prints it out and then frees up the dynamically allocated space
*/

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <stdint.h>
#include "termcolor.hpp"
using namespace std;

int main(int argc, char *argv[]) {
    //forward declare the method we wil be using
    char** generateLand(int, int);
    void printLand(char**, int, int);

    //initialize variables to pass as parameters
    int rowCount = 0, columnCount = 0;
    //set a seed for our random number function
    srand((int)time(0));

    //prints out a simple menu telling the user what to input
    cout << "Lets Generate a Fantasy Land!" << endl;
    cout << "Enter the dimensions of the land you want to create" << endl;

    //gather the user inputs and loop if they dont enter a number between 20-50
    cout << "Vertical length: " << endl;
    cin >> rowCount;
    while (rowCount < 20 || rowCount > 50){
        cout << "Please enter a number between 20-50" << endl;
        cin >> rowCount;
    }
    cout << "Horizontal length: " << endl;
    cin >> columnCount;
    while (columnCount < 20 || columnCount > 50){
        cout << "Please enter a number between 20-50" << endl;
        cin >> columnCount;
    }

    //generate and fill the 2d array with "terrain"
    char** land = generateLand(columnCount, rowCount);

    //print out that terrain
    printLand(land , columnCount, rowCount);

    return 0;
}

//this is a random number generator that gives between a range to simulate our probability
int randomNumber(int range){
    return (rand() % range ) + 1;
}

//these next few functions just return a character representing a type of terrain
char newFromRuralLand(){
    return 'R';
}

char newFromForest(){
    return 'F';
}

char newFromTown(){
    return 'T';
}

char newFromWater(){
    return 'W';
}

char newFromCity(){
    return 'C';
}

char newFromMountain(){
    return 'M';
}

//this picks the top left corner and the array is built off this result
char PickLandType (){
    int probability = randomNumber( 120);
    if (probability <= 20)
        return newFromRuralLand();
    else if (probability > 20 && probability <= 40)
        return newFromForest();
    else if (probability > 40 && probability <= 60)
        return newFromTown();
    else if (probability > 60 && probability <= 80)
        return newFromCity();
    else if (probability > 80 && probability <= 100)
        return newFromMountain();
    else
        return newFromWater();
}

//this function returns a character according to the specified probability for each terrain
char generateNeighbor(char item){
    int prob = randomNumber(100);
    switch (item) {
        case 'R':
            if (prob <= 40)
                return newFromRuralLand();
            else if (prob > 40 && prob <= 65)
                return newFromForest();
            else if (prob > 65 && prob <= 80)
                return newFromTown();
            else if (prob > 80 && prob <=90)
                return newFromWater();
            else
                return newFromMountain();
        case 'F':
            if (prob <= 20)
                return newFromRuralLand();
            else if (prob > 20 && prob <= 60)
                return newFromForest();
            else if (prob > 60 && prob <= 65)
                return newFromTown();
            else if (prob > 65 && prob <= 85)
                return newFromWater();
            else
                return newFromMountain();
        case 'T':
            if (prob <= 20)
                return newFromRuralLand();
            else if (prob > 20 && prob <= 25)
                return newFromForest();
            else if (prob > 25 && prob <= 65)
                return newFromTown();
            else if (prob > 65 && prob <=75)
                return newFromWater();
            else if (prob > 75 && prob <= 95)
                return newFromCity();
            else
                return newFromMountain();
        case 'C':
            if (prob <= 15)
                return newFromForest();
            else if (prob > 15 && prob <= 40)
                return newFromTown();
            else if (prob > 40 && prob <=50)
                return newFromWater();
            else if (prob > 50 && prob <= 90)
                return newFromMountain();
            else
                return newFromRuralLand();
        case 'M':
            if (prob <= 5)
                return newFromRuralLand();
            else if (prob > 5 && prob <= 20)
                return newFromForest();
            else if (prob > 20 && prob <= 25)
                return newFromTown();
            else if (prob > 25 && prob <=40)
                return newFromWater();
            else if (prob > 40 && prob <= 50 )
                return newFromCity();
            else
                return newFromMountain();
        case 'W':
            if (prob <= 15)
                return newFromRuralLand();
            else if (prob > 15 && prob <= 35)
                return newFromForest();
            else if (prob > 35 && prob <= 40)
                return newFromTown();
            else if (prob > 40 && prob <=80)
                return newFromWater();
            else if (prob > 80 && prob <= 90)
                return newFromCity();
            else
                return newFromMountain();
    }

}

// this function builds the 2d array and fills it based of what to the left or on top except for the first row and column
char** generateLand(int width, int height){
    // create
    char** landArray = new char*[height];
    for (int i = 0; i < height ; i++) {
        landArray[i] = new char[width];
    }

    //fill
    landArray[0][0] = PickLandType();
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width ; j++) {
            int coin = randomNumber(2);
            if (i == 0 && j >= 1)
                landArray[i][j] = generateNeighbor(landArray[i][j-1]);
            else if (i >= 1 && j == 0)
                landArray[i][j] = generateNeighbor( landArray[i-1][j]);
            else{
                //gets value to the left
                if (coin == 1){
                    if (i>=1 && j >= 1)
                        landArray[i][j] = generateNeighbor(landArray[i][j-1]);
                }
                // gets value above it
                if (coin == 2){
                    if (i>=1 && j >= 1)
                        landArray[i][j] = generateNeighbor(landArray[i-1][j]);
                }
            }
        }
    }
    return landArray;
}

void printLand(char** land, int width, int height){
    //displays the 2d array and we use the termcolor library to color coordinate each character
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width ; j++) {
            char currentLand = land[i][j];
            switch (currentLand) {
                case 'R':
                    cout << termcolor::on_green << termcolor::white << currentLand << " ";
                    break;
                case 'F':
                    cout << termcolor::on_green << termcolor::grey << currentLand << " ";
                    break;
                case 'T':
                    cout << termcolor::on_yellow << termcolor::white << currentLand << " ";
                    break;
                case 'C':
                    cout << termcolor::on_magenta << termcolor::yellow << currentLand << " ";
                    break;
                case 'M':
                    cout << termcolor::on_grey << termcolor::white << currentLand << " ";
                    break;
                case 'W':
                    cout << termcolor::on_blue << termcolor::white << currentLand << " ";
                    break;

            }
        }
        cout << termcolor::reset;
        cout << endl;
    }

    //free the space
    for (int j = 0; j < height; ++j) {
        delete[] land[j];
    }
    delete land;
}