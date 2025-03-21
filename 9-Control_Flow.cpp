// When a program is run, execution begins at the top of main() and terminates at the end of main().
// The specific sequence of statements that the CPU executes is called the EXECUTION PATH (or just PATH).
// A CONTROL FLOW STATEMENT allows the programmer to change the normal path of execution.
/* When a control flow statement causes the point of execution to change to a non-sequential statement,
   this is called BRANCHING. */
// Here are the categories of control flow statements and their keywords:

// CONDITIONAL STATEMENTS: Causes a sequence of code to execute only if some condition is met.
// -- (if, else, switch)
// JUMPS: Tells the CPU to start executing the statements at some other location.
// -- (goto, break, continue)
// FUNCTION CALLS: Jump to some other location and back.
// -- (function calls, return)
// LOOPS: Repeatedly execute some sequence of code zero or more times, until some condition is met.
// -- (while, do-while, for, ranged-for)
// HALTS: Terminate the program.
// -- (std::exit(), std::abort())
// EXCEPTIONS: A special kind of flow control structure designed for error handling.
// -- (try, throw, catch)

/**************************
	IF/ELSE STATEMENTS
**************************/

// The most basic kind of conditional statement in C++ is the "if/else" statement, written like this:

bool condition1 = true;

if (condition1) {  // If condition1 is true...
	// Execute the code here
} else {  // Otherwise...
	// Execute the code here
}

// You can stack these statements, like this:

bool condition2 = false;

if (condition1) {  // If condition1 is true...
	// Execute the code here
} else if (condition2) {  // Otherwise, if condition2 is true...
	// Execute the code here
} else {  // Otherwise...
	// Execute the code here
}

// You can also have if statements inside of another if statement.

// Note: A common mistake with if statements is using the = operator instead of the == operator.
// If you want to check if a value is equal to another value, use ==, not =.

if (x = 2) // <-- Wrong
if (x == 2)	// <-- Right

/************************
	SWITCH STATEMENTS
************************/

/* If you find yourself chaining a bunch of if / else statements together, you might want to use a SWITCH
   STATEMENT instead. */
/* Let's say you have a class of students and you want to separate them into 3 groups. Here's an example
   of a switch statement that reflects that situation: */

#include <iostream>
int groupNumber;

switch (groupNumber) {
	case 1:
		std::cout << "You're in group 1";
		break;
	case 2:
		std::cout << "You're in group 2";
		break;
	case 3:
		std::cout << "You're in group 3";
		break;
	default:
		std::cout << "You have an invalid group number";
		break;
}

/* If the expression's value is equal to the value after any of the case-labels, the statements after the
   matching case-label are executed. */
// If no matching value can be found, the statements after the default label are executed.
// If no matching value can be found and there is no default label, the switch is skipped.
// The condition in a switch must evaluate to an integral type (integers, chars, or bools).
// This is because switch statements are designed to be highly optimized.

// The "break" keyword here basically just means "escape the switch statement".
/* If you don't include them, the switch statement will jump to the matching case, then keep going and
   execute all the statements below it. */
// This is called fallthrough, and it can be useful at times.
/* To prevent the compiler from generating a warning, you can put the [[fallthrough]] attribute (Only
   available in C++17 and onward) at the end of the case, like this: */

switch (groupNumber) {
	case 1:
		std::cout << "You're in group 1";
		break;
	case 2:
		std::cout << "You're in group 2";
		[[_fallthrough]]; // No underscore required if using C++17
	case 3:
		std::cout << "You're in group 3";
		break;
	default:
		std::cout << "You have an invalid group number";
		break;
}

// If you want to execute the same code for multiple cases, you can stack them like this:

char letter = 'A';

switch (letter) {
	case 'A':
	case 'E':
	case 'I':
	case 'O':
	case 'U';
		std::cout << "This is a vowel";
		break;
	default:
		std::cout << "This is not a vowel";
		break;
}

/***********
	GOTO
***********/

// A goto statement instructs the compiler to "jump" to a different location in the code, like this:

exampleLabel:
// Code, usually an if statement
goto exampleLabel;

/* The above example uses a goto statement to jump backwards in the code, but you can also use a goto
   statement to jump forward in the code. */

/******************
	WHILE LOOPS
******************/

// A while loop repeats a section of code until a certain condition is met.
// This is the syntax:

int count = 0;

while (count < 10) {
	// Do something
	++count;
}

// If you want to guarantee that your code runs at least once, you can use a do/while loop, like this.

do {
	// Do something
	++count;
}
while (count < 10);

// Loops can be nested.
// Don't forget to include code that can create a scenario where the condition evaluates to "false".
// Otherwise you'll end up with an infinite loop.
// Sometimes an infinite loop can be useful, however you still need to include a way to end/escape it.
/* This can be done with a return statement, a break statement, an exit statement, a goto statement, an
   exception being thrown, or the user killing the program. */
// To initiate an infinite loop, use while(true).

/****************
	FOR LOOPS
****************/

for (int x = 1; x < 10; ++x) {
	// Do something
}

// Translation: x starts at 1; as long as x is less than 10; increase x by 1 each loop.
// Note: x goes out of scope once the loop ends since it gets initialized in the for loop.
/* Each part of a for loop statement can be omitted. For example, if we initialize x before the for
   loop, we can omit the first part, like this: */

int x = 1;

for (; x < 10; ++x) {
	// Do something
}

// Omitting everything results in an infinite loop.
// These loops can also be nested.
// There is another for loop called a "range-based for loop" which is discussed with vectors/arrays.

/*********************
	BREAK/CONTINUE
*********************/

// In a switch statement, the break keyword is used to signify that the case is finished.
// In a loop, the break keyword tells the program to escape the loop and continue execution.
// In a loop, the continue keyword tells the program to move on to the next iteration of the loop.

/************
	HALTS
************/

// A halt is a flow control statement that terminates the program.
// In C++, halts are implemented as functions rather than keywords.
/* std::exit() is a function that causes the program to terminate normally, which means the program has
   exited in an expected way. */
/* Normal termination does not imply anything about whether the program was successful, which is what the
   status code is for. */
/* For example, let's say you're writing a program where you expect the user to type in a filename to process.
   If the user typed an invalid filename, your program would probably return a non-zero status code to indicate
   the failure state, but it would still have a normal termination.*/
// std::exit() also performs a number of cleanup functions.
// It is called implicitly after function main() returns.
// To call it explicitly, you need to include <cstdlib> at the top of your program.
/* There is also std::atexit(func) which allows you to specify a function that will be called on program
   termination via std::exit(). */
// The parameter is the name of the function you wish to be called.

// C++ has two other halt-related functions: std::abort() and std::terminate().
// std::abort() causes your program to terminate abnormally and does not do any cleanup.
// For example, trying to divide by 0 will result in an abnormal termination.
// std::terminate() is typically used in conjunction with exceptions.
// Although it can be called explicitly, it's more often called implicitly when an exception isn't handled.
// By default, std::terminate() calls std::abort().

#include "fakeheader.h"