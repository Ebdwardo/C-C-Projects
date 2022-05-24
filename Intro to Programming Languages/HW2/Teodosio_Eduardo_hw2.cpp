/*
Author: Eduardo Teodosio Campuzano
Date: 6/7/2020
Description: This code has the user choose between playing 4 random minigames against the computer in a best of series
OR see the difference between functions and macro;
*/

#include <iostream>
#include <stdio.h>
#include <ctime>
#include <cstdlib>
#define sub_macro(a,b) a-b
#define cube_macro(a) a*a*a
#define min_macro(a,b) ((a<=b) ? a: b)
#define odd_macro(a) ((a%2 == 0) ? 0: 1)
using namespace std;

int main (int argc, char *argv[]) {
    // Here is where I declare the forward declarations and the local variables to be used in the code and passed to the functions
    srand((int)time(0));
    int gameChoice = 0;
    int validChoice = -1;
    char name[10];
    int numberOfRounds = 0;
    int numberOfWins = 0;
    int numberOfBotWins = 0;
    int miniGameChosen = 0;

    int RandomInRange(int, int);
    bool evenOrOdd(char[]);
    int rockPaperScissors(char[]);
    bool numberBetween();
    int diceRoll(char[]);
    void macroVFunctions();
    int victory (int, int, int);

    // Here is the main menu that prompts the user for a choice and store a valid choice
    cout << "Welcome to the CSE240 Assignment 2!\nMenu:\n1 - CSE240 Mini-Game Collection\n2 - Macros vs Functions Throw-down\n0 - Exit\nChoose an option: " ;
    cin >> gameChoice;
    if (gameChoice == 0 || gameChoice == 1 ||gameChoice == 2){
        validChoice = 0;
    }
    while(validChoice != 0){
        cout << "Please choose a number corresponding to an option listed above\n" << endl;
        cin >> gameChoice;
        if (gameChoice == 0 ||gameChoice == 1 ||gameChoice == 2){
            validChoice = 0;
        }
    }

    // Here is where we do the file reading for the file stored where the executable is
    FILE * infile;
    infile = fopen("random_names.txt","r");

    int i = 0;
    for(i = 0; i < RandomInRange(0, 100); i++)
    {
        fscanf(infile, "%s", name);
    }
    fclose(infile);

    // This is where we run all the mini games based on the user choice
    if (gameChoice ==1){
        cout << "Welcome to the CSE240 Mini-Game Collection!" << endl;
        cout << "I am your opponent " << name << endl;
        cout << "How many rounds should we play? (Choose an odd number)\n>" << endl;
        cin >> numberOfRounds;

        // Here is where we make sure the user enters an odd number of rounds
        while ( numberOfRounds%2 == 0){
            cout << "Enter and ODD number" << endl;
            cin >> numberOfRounds;
        }

        // Here is the loop that runs and calls all the games until the player wins, loses,  or the numbers of rounds is reached
        for (int i = 1; i <= numberOfRounds; i++){
            cout << "The score is:\nPlayer: " << numberOfWins << endl;
            cout << name << ":  " << numberOfBotWins << "\n" << endl;
            cout << "Game #" << i << endl;

            // This is where the code random chooses one of the four mini games
            miniGameChosen = RandomInRange(1,4);

            // These if statements run the games and based on whether the user won or lost it will update respective scores
            if (miniGameChosen == 1){
                if (evenOrOdd(name)){
                    numberOfWins++;
                }
                else {
                    numberOfBotWins++;
                }
            }
            if (miniGameChosen == 2){
                // Created this variable so the game only runs once and we can update scores based on who won
                // Created this variable and if statement so the game keeps running in the case of a tie until someone wins
                int rpsResult = rockPaperScissors(name);
                if (rpsResult == -1){
                    while (rpsResult == -1){
                        rpsResult = rockPaperScissors(name);
                    }
                }

                if (rpsResult == 1){
                    numberOfWins++;
                }
                else if ( rpsResult == 0 ){
                    numberOfBotWins++;
                }
            }
            if (miniGameChosen == 3){
                if (numberBetween()){
                    numberOfWins++;
                }
                else {
                    numberOfBotWins++;
                }
            }
            if (miniGameChosen == 4){
                // Same here, this varaible was created so games only runs once and we can so stuff according to the output
                int diceResult = diceRoll(name);
                if (diceResult == -1){
                    while (diceResult == -1){
                        diceResult = diceRoll(name);
                    }
                }
                if (diceResult == 1){
                    numberOfWins++;
                }
                else if (diceResult == 0){
                    numberOfBotWins++;
                }
            }

            if (victory(numberOfRounds, numberOfWins, numberOfBotWins) == 1){
                cout << "Winner! you have won " << numberOfWins << " out of " << numberOfRounds << " games" << endl;
                break;
            } else if (victory(numberOfRounds, numberOfWins, numberOfBotWins) == 0) {
                cout << "Defeat! " << name << " won " << numberOfBotWins << " out of " << numberOfRounds << " games" << endl;
                break;
            }

        }
    }

    // If the player chooses two it will show the difference between functions and macros
    if (gameChoice ==2){
        macroVFunctions();
    }

    // Will stop the program if the user chose zero
    if ( gameChoice == 0)
        cout << "Goodbye!" << endl;

    return 0;
}


int RandomInRange(int min,int max){
    // Have a random seed in the main. We get a value in the range by using the % to divide rand() to get a number
    // between the ranges and then we offset that value by the minimum so it falls between the range of numbers
    int r = (rand() % (max - min +1)) + min  ;
    return r;
}

// Checks is a number is even
bool IsEven(int number){
    return (number)%2 == 0;
}

bool evenOrOdd(char name[10]) {
    // Declare local variables to be used and generate a random number
    int choice;
    bool incorrectChoice = true;
    int numBetween100;
    int computerChoice = RandomInRange(0, 100);

    // Prompt the user for input until it is valid
    cout << "Even/Odd game!\nGuess even or odd! (0 for even 1 for odd): " ;
    cin >> choice;
    while (incorrectChoice){
        if (choice != 1){
            if (choice != 0){
                cout << "Please pick 0 or 1 for even or odd respectively: ";
                cin >> choice;
                if (choice == 1 || choice ==0){
                    incorrectChoice = false;
                }
            }
            else{incorrectChoice = false;}
        }
        else {incorrectChoice = false;}
    }

    // Ask the user for more input to see if they are correct
    cout << "Enter a number (between 0 and 100): ";
    cin >> numBetween100;
    printf("%s", name);
    cout << " picked " << computerChoice<< endl;

    // Check to see if the sum of the players and bots number is even
    bool isEven = IsEven(numBetween100+ computerChoice);

    // Check to see if we chose the number to be even
    bool bChoice = choice == 0;

    // Print out the expression and result
    cout << numBetween100 << " + " << computerChoice << " = " << (numBetween100 + computerChoice);

    // Append whether it is even or odd;
    if(isEven) cout << " - EVEN!";
    else cout << " - ODD!";
    cout << endl;

    // If our choices truth value matches that of the total number we win, if not we lose;
    if(bChoice == isEven){
        cout << "You win! \n" << endl;
        return true;
    }
    else {
        cout << name << " wins! \n";
        cout << endl;
        return false;
    }



}

int rockPaperScissors(char name[10]){
    // Created these local char variables so we can easily compare inputs to choices
    char choice[16];
    char computerChoice[16];

    // Have the bot choose a number 1-3 to simulate their choice
    int randomValue = RandomInRange(1 ,3);

    // Display menu
    cout << "Rock, Paper, Scissors game!\n" << "Choose a throw!\n" << "1. Rock\n2. Paper\n3. Scissors\n>>" << endl;

    // Makes sure the user puts in correct input
    while (true){
        cin >> choice;
        if(choice[0] != '1' && choice[0] != '2' && choice[0] != '3')
            cout << "Invalid input; try again." << endl;
        else break;
    }

    // Show what the computer chose
    if (randomValue == 1 ){
        computerChoice[0] = '1';
        cout << name <<  " chose rock" << endl;
    }
    else if( randomValue == 2){
        computerChoice[0] = '2';
        cout << name <<  " chose paper" << endl;
    }
    else if (randomValue == 3) {
        computerChoice[0] = '3';
        cout << name <<  " chose scissors" << endl;
    }

    // These if statements determine and prints out who wins
    if ( choice[0] == '1'){
        if ( computerChoice[0] == '1'){
            cout << "Tie!\n" << endl;
            return -1;
        }
        else if ( computerChoice[0] == '2') {
            cout << "You lose!\n" << endl;
            return 0;
        }
        else {
            cout << "You win!\n" << endl;
            return 1;
        }
    }
    if ( choice[0] == '2'){
        if ( computerChoice[0] == '2'){
            cout << "Tie!\n" << endl;
            return -1;
        }
        else if ( computerChoice[0] == '3') {
            cout << "You lose!\n" << endl;
            return 0;
        }
        else {
            cout << "You win!\n" << endl;
            return 1;
        }
    }
    if ( choice[0] == '3'){
        if ( computerChoice[0] == '3'){
            cout << "Tie!\n" << endl;
            return -1;
        }
        else if ( computerChoice[0] == '1') {
            cout << "You lose!\n" << endl;
            return 0;
        }
        else {
            cout << "You win!\n" << endl;
            return 1;
        }
    }
}

bool numberBetween(){
    // Establish the random int between 1000 and the boundaries as well as other needed variables
    int computerChoice = RandomInRange(0 ,1000 );
    int lowerBoundary = RandomInRange(computerChoice - 50, computerChoice -15);
    int upperBoundary = RandomInRange( computerChoice +15, computerChoice + 50);
    int playerGuess = 0;
    int numberOfGuesses;

    // Telling the user what to do
    cout << "Number Guessing game!" << endl;
    cout << "Player I'm thinking of a number between " << ((lowerBoundary)/10)*10 << " and " << (((upperBoundary)/10)*10) << endl;
    cout << "You have 5 guesses!"<< endl;

    // Loop to get user input and tell them whether they are close to the value or not
    for ( numberOfGuesses = 1; numberOfGuesses <= 5; numberOfGuesses++) {
        cout << "What's guess #" << numberOfGuesses << "? ";
        // Loop to make sure user put in correct data type
        while (true) {
            cin >> playerGuess;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(1024, '\n');
                printf("Invalid input; try again.\n");
            } else break;
        }

        // This if chains tells the user information about their guess
        if (playerGuess == computerChoice){
            cout << "Correct!" << endl;
            return true;
        }
        else if (playerGuess > computerChoice){
            cout << "My number is lower!" << endl;
        }
        else {
            cout << "My number is higher" << endl;
        }

    }
    // If the user didnt figure out the number the code will tell them what the number was
    cout << "My choice was: " << computerChoice << "\n" << endl;
    return false;

}
// Function to simulate rolling a dice
int RollDie(int sides){
    return RandomInRange(1, sides);
}

int diceRoll(char name[10]){
    //Create variables we need to keep track of the dice and number of wins etc..
    int dice = 0;
    int sides = 0;
    int playerResult = 0;
    int botResult = 0;
    int rolledNumber = 0;
    int botRolledNumber = 0;

    // Tell the user info and ask for input
    cout << "Dice Roll Showdown!" << endl;
    cout << "How many sides do the dice have (input a positive number): ";
    cin >> sides;
    cout << "How many dice will each player roll? ";
    cin >> dice;

    // A for loop to "roll" according to the number of dice and add the total
    cout << "Player 1 rolled:" << endl;
    int i;
    for(i = 0; i<dice; i++){
        rolledNumber = RollDie(sides);
        playerResult += rolledNumber;
        cout << rolledNumber << endl;
    }
    // Show what the user rolled
    cout << "Total: " << playerResult << endl;

    cout << name <<  " rolled:" << endl;
    // Same as the player
    int j;
    for(j = 0; j<dice; j++){
        botRolledNumber = RollDie(sides);
        botResult += botRolledNumber;
        cout << botRolledNumber << endl;
    }
    // Show what the computer rolled
    cout << "Total: " << botResult << endl;

    // This if chain determines who wins and returns a value accordingly
    if (playerResult > botResult){
        cout << "Player Wins! \n" << endl;
        return 1;
    }
    else if ( playerResult == botResult){
        cout << "Tie! \n" << endl;
        return -1;
    }
    else {
        cout << name <<  " Wins! \n" << endl;
        return 0;
    }
}

// This function is used to determine who wins the best of however many rounds the user decides to play and returns a corresponding value
int victory(int rounds, int playerWins, int botWins){
    int win = (rounds +1) / 2;
    if (playerWins == win){
        return 1;
    }
    else if (botWins == win){
        return 0;
    }
    else {
        return -1;
    }
}

//------------------------------------------------------------------------------------------------//
// Part 2

// These are the functions required to implement
int subf(int a, int b) {
    return a-b;
}
int cubef(int a){
    return a*a*a;
}
int minf(int a, int b){
    if (a <= b){
        return a;
    }
    else {
        return b;
    }
}
int oddf(int a){
    if( a % 2 ==0){
        return 0;
    }
    else {
        return 1;
    }
}

// This function shows the difference between passing parameters to functions as opposed to macro's
void macroVFunctions(){
    int num1 = 10, num2 = 17;
    cout << "The subtraction function returns: " << subf(num1, num2) << endl;
    cout << "The subtraction macro returns: " << sub_macro(num1, num2) << endl;
    cout << endl;

    num1 = 10, num2 = 17;
    cout << "The subtraction function returns: " << subf(num1++, num2--) << endl;
    cout << "The subtraction macro returns: " << sub_macro(num1++, num2--) << endl;
    cout << endl;

    num1 = 10, num2 = 17;
    cout << "The cube function returns: " <<  cubef(num1) << endl;
    cout << "The cube macro returns: " << cube_macro(num1) << endl;
    cout << endl;

    num1 = 10, num2 = 17;
    cout << "The cube function returns: " << cubef(--num1) << endl;
    cout << "The cube macro returns: " << cube_macro(--num1) << endl;
    cout << endl;

    num1 = 10, num2 = 17;
    cout << "The minimum function returns: " << minf(num1, num2) << endl;
    cout << "The minimum macro returns: " << min_macro(num1, num2) << endl;
    cout << endl;

    num1 = 10, num2 = 17;
    cout << "The minimum function returns: " << minf(--num1, --num2) << endl;
    cout << "The minimum macro returns: " << min_macro(--num1, --num2) << endl;
    cout << endl;

    num1 = 10, num2 = 17;
    cout << "The odd function returns: " << oddf(num1) << endl;
    cout << "The odd macro returns: " << odd_macro(num1) << endl;
    cout << endl;

    num1 = 10, num2 = 17;
    cout << "The odd function returns: " << oddf(num1++) << endl;
    cout << "The odd macro returns: " << odd_macro(num1++) << endl;
    cout << endl;
}