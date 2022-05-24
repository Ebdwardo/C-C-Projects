//
// Created by Eduardo Teodosio on 5/27/2020.
//
#include <stdio.h>
int main() {
    int c;
    char ch;
    int f, a = 10, b = 20;
    float d = 0;

// a for loop that asks the user for 5 inputs
    for (c = 0; c <= 4; c++) {

// get user input and replace ch with whatever they input
        scanf("%c", &ch);

//switch statements that run depending on the character the user inputs
        switch (ch) {
            case '+':
                f = a + b;
                printf("f = %d\n", f);
                break;
            case '-':
                f = a - b;
                printf("f = %d\n", f);
                break;
            case '*':
                f = a * b;
                printf("f = %d\n", f);
                break;
            case '/':
                d = (float)a / b;
                printf("f = %.2f\n", d);
                break;
            default:
                printf("invalid operator\n");
                break;
        }
// extra scanf to read the \n only to be overwritten once the loop runs again
        scanf( "%c", &ch);
    }
    return 0;
}