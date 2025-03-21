/************************
    FUNCTION POINTERS
************************/

// Function pointers are just pointers that point to functions.
// We've seen a couple from using some of the C++ standard library algorithms.
/* When a function is referred to by name (without parenthesis), C++ converts the function into a function
   pointer, holding the address of the function. */
// The syntax for creating a function pointer is a bit messy:

int (*ptr)();

// The above is a pointer to a function that returns and int, and has 0 parameters.
// It can be set to any function that matches its type.
/* The parentheses around *fcnPtr are necessary, as int* fcnPtr() would be interpreted as a forward
   declaration for a function named fcnPtr that returns a pointer. */
// To make a const function pointer, the const goes after the asterisk.
// Function pointers can be initialized with a function by using curly braces:

int func() { return 1; } // <-- The function
int (*fcnPtr)(){&func};

// Here is an example of a function pointer that has parameters:

int (*fcnPtr2)(int, bool); // Pointer to a function that takes 2 parameters
int func2(int a, bool b) { return 1; } // Function that has two parameters (of the correct type)
fcnPtr2 = &func2; // Setting the pointer to the address of that function

/* To call the function at the function pointer, use the normal function call syntax but replace the name of
   the function with the name of the pointer. */
// Since function pointers can be set to nullptr, it’s good to check that before calling it.
// Also note that functions called through pointers cannot use default arguments.

/*********************
    THE CALL STACK
*********************/

/* The call stack keeps track of all the active functions from the start of the program to the current point
   of execution. */
// The call stack is implemented as a stack data structure, which works like this:

/* Consider a stack of plates in a cafeteria. Because each plate is heavy and they are stacked, you can only
   do one of three things: */
// 1. Look at the surface of the top plate.
// 2. Take the top plate off the stack (exposing the one underneath, if it exists).
// 3. Put a new plate on top of the stack (hiding the one underneath, if it exists).
// A stack is last-in, first-out (LIFO): The last item pushed on will be the first item popped off.

// When the application starts, the main() function is pushed onto the call stack by the operating system.
// Then, the program begins executing.
// When a function call is encountered, the function is pushed onto the call stack.
// When the function ends, that function is popped off the stack (sometimes called "unwinding" the stack).
// The stack itself is a fixed-size chunk of memory addresses.
// The “items” we’re pushing and popping on the stack are called stack frames.
// A stack frame keeps track of all of the data associated with one function call.
/* The stack pointer (a small piece of memory in the CPU, called a register) keeps track of where the top of
   the call stack is. */

// The stack has a limited size, and consequently can only hold a limited amount of information.
// If the program tries to put too much information on the stack, stack overflow will result.
// In that case, further allocations begin overflowing into other sections of memory.
/* Stack overflow is generally the result of allocating too many variables on the stack, and/or making too
   many nested function calls. */
// On modern operating systems, stack overflow will generally cause your OS to terminate the program.

/*****************************
    COMMAND LINE ARGUMENTS
*****************************/

/* Command line arguments are optional string arguments that are passed by the operating system to the
   program when it is launched. */
// The program can then use them as input, or ignore them.
/* Much like how function parameters allow a function to provide inputs to another function, command line
   arguments provide a way for people (or programs) to provide inputs to a program. */
// Executable programs can be run on the command line by invoking them by name.
/* For example, to run an executable file called “WordCount” that is located in the current directory of a
   Windows machine, you could type:  WordCount  */
/* In order to pass command line arguments to WordCount, we simply list the command line arguments after the
   executable name, like so:  WordCount Myfile.txt  */
// Now when WordCount is executed, Myfile.txt will be provided as a command line argument.
// A program can have multiple command line arguments, separated by spaces.
// If you're running your program from an IDE, the IDE should provide a way to enter command line arguments.

// To access command line arguments from our program, we'll have to use a different form of main():

int main(int argc, char* argv[])

// This will sometimes be written as:

int main(int argc, char** argv)

// "argc" is an integer parameter containing a count of the number of arguments passed to the program.
// argc will always be at least 1, because the first argument is always the name of the program itself.
// "argv" is where the actual argument values are stored.
// argv is just a C-style array of char pointers (each of which points to a C-style string).

// Here's a short program named “MyArgs” to print the value of all the command line parameters:

#include <iostream>
int main(int argc, char* argv[])
{
    std::cout << "There are " << argc << " arguments:\n";

    for (int count = 0; count < argc; ++count){
        std::cout << argv[count] << '\n';
    }

    return 0;
}

/* Note that we cannot use a range-based for-loop to iterate through argv, since range-based for-loops don’t
   work on decayed C-style arrays. */

// Typically, arguments passed inside double quotes are considered to be part of the same argument.
// Most operating systems will allow you to include a literal double quote by doing: \"

/***************
    ELLIPSIS
***************/

// There's a way to write a function that uses an undefined number of paramaters using an "ellipsis":

void ellipsis(int param1, ...) {};

// The ellipsis (...) must always come last, and there must be at least one non-ellipsis parameter first.
// Using ellipsis are considered dangerous and should (probably) be avoided.
// One major reason is because there is no type-checking.
/* C++11 introduced parameter packs and variadic templates, which offers functionality similar to ellipses
   but with strong type checking. */
/* Fold expressions were added in C++17 which significantly improves the usability of parameter packs to the
   point where they are now a viable option. */

/**************
    LAMBDAS
**************/

// I hate lambdas and they're ugly af so here's what one looks like and how to read it:

// A lambda is just an anonymous function (a function with no identifier)
[ captureClause ] ( parameters ) -> returnType { restOfTheFunction; }

// The return type is optional, and if omitted, "auto" will be assumed.
// The capture clause gives a lambda access to variables available in the surrounding scope.
// Everything else is self explanatory.