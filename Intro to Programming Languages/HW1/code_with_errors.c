#include <stdio.h>

// CSE 240 Code with Errors
// Before starting this assignment, please compile and run this program. 
// You will first notice that the program will not compile. Fix the errors and define the error types.
// Next, you will notice that the program is printing incorrect information. Fix the errors and define those error types.

/* !!!!!!!!!!!!!!!!!!!!!
	This code is used in concert with an online quiz! 
	Make sure you're using it correctly!
	
	You should fix the errors and compile and run the code on general.asu.edu

	Each Problem is answered online!
	!!!!!!!!!!!!!!!!!!!!
*/

/*
	Fix the errors, rename the file with your last name: <lastname>_errors.c and turn it in
*/
int main(int argc, char** argv)
{
	int problem = 1;

	// Problem 1:
	printf("Problem #%d\n", problem);
	int value = 50;
	printf("Integer value is %d\n", value);
	// ****** IDENTIFY THE ERROR TYPE: Syntax, Context or Semantic
	// Indicate your answer in the online quiz for Problem 1

	problem++;

	// Problem 2: 
	// Numbers are numbers aren't they?  correct the error(s)(2 points)
	printf("Problem #%d\n", problem);
	float fractionalNumber = 5.5;
	printf("Value: %.1f should be 5.5\n", fractionalNumber);
	// ****** IDENTIFY THE ERROR TYPE: Syntax, Context or Semantic
	// Indicate your answer in the online quiz for Problem 2

	problem++;

	// Problem 3: 
	// One third of 66 is 22, why is the program printing that a third of 66 is 0? Correct the error(s)(2 points)
	printf("Problem #%d\n", problem);
	int fullValue = 66;
	printf("One-third of %d is %.1f\n", fullValue, fullValue * (1.0 / 3));

	// ****** IDENTIFY THE ERROR TYPE: Syntax, Context or Semantic
	// Indicate your answer in the online quiz for Problem 3
	
	problem++;
	
	// Problem 4: 
	// Integer value intValue gets a value from the user or at least ... it should ... 
	printf("Problem #%d\n", problem);
	int amIWrong;
	int intValue;
	do
	{	
		printf("Give me an integer value: x =  ");
		amIWrong = scanf("%d", &intValue);	//check for bad input
		if(amIWrong == 0) while ((getchar()) != '\n'); //clean up input stream
	}
	while(amIWrong == 0);
	printf("%d\n",intValue);
	// ****** IDENTIFY THE ERROR TYPE: Syntax, Context or Semantic
	// Indicate your answer in the online quiz for Problem 4
	
	problem++;
	
	//Problem 5:
	// Having gotten a value from the user we want to see some info about it... shouldn't there be one message?
    printf("Problem #%d\n", problem);
	if (intValue == 100)
		printf("x is equal to 100.\n");
	else if (intValue > 100)
		printf("x is greater than 100.\n");
	else
		printf("x is less than 100.\n");

	// ****** IDENTIFY THE ERROR TYPE: Syntax, Context or Semantic
	// Indicate your answer in the online quiz for Problem 5
	
	problem++;
	
	// Problem 6: 
	// ** Pay attention to what you input and the output **... is it even? is it odd? 
	// This code should tell you that! Correct the error(s) (1 points).
	printf("Problem #%d\n", problem);

	if (intValue % 2 == 0)
		printf("%d is an even number.\n", intValue);
	if (intValue % 2 != 0)
		printf("%d is an odd number.\n", intValue );

	// ****** IDENTIFY THE ERROR TYPE: Syntax, Context or Semantic
	// Indicate your answer in the online quiz for Problem 6	
	problem++;
	
	// Problem 7: 
	// This bit of code is meant to print "Hello World!". Correct the error(s) (2 points).
	char message[] = "World!";
	printf("Problem #%d\n", problem);
	printf("Hello %s\n", message);

	// ****** IDENTIFY THE ERROR TYPE: Syntax, Context or Semantic
	// Indicate your answer in the online quiz for Problem 7	
	problem++;

	printf("Problem #%d\n", problem);
	printf("Did you find it?\n");
	// Problem 8: Did you notice it?
	// There is another error in here ... look at your output... find it and fix it
	// ****** IDENTIFY THE ERROR TYPE: Syntax, Context or Semantic
	// Indicate your answer in the online quiz for Problem 8	

	
	//DONE//
	#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
	system("pause"); //pause the output with a "press anything to continue" so you can see output
	#endif
}
