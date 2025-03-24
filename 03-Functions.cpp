/************************
	WRITING FUNCTIONS
************************/

// Here is the syntax for writing a function:

void myFunction() {
	// (insert code here)
}

// The first line is called the function header, written in this format:
// returnType functionName(parameters);
// "void" just means that the function does not return a value.
// The parameters are values that you must input for the function to work.
/* For example, a function that adds two numbers would need two parameters, which would be the two
   numbers you want to add. It would look like this: */

int addNumbers(int num1, int num2) {
	return num1 + num2;
}

// You can call a function like this:

myFunction();  // This syntax only works for void functions
int result = addNumbers(1, 2);

// For functions with a return value, you must either store the result or use it in an expression.
// Functions can be called more than once, and you can call a function inside of a different function.
/* You can even call a function inside of itself, which is called a recursive function. Be careful with
   these, as they can result in endless loops. */
// You CAN'T define a funciton inside of another function. This is called a nested function.

void outerFunction() {

	void innerFunction() {

	}
}
// ^ This is supported in other languages, but not C++.

/* You can provide a function with default parameters, which just means parameters that will default
   to a value if you don't provide them in the function call. */
// The default parameters must be the right-most parameters, like this:

void defaultParams(int x, int y = 2, int z = 3) {}

/* Then when you call the function, if you don't provide enough parameters, they will be set as
   their default value. */

// Two functions cannot have the same name unless they have different parameter types.
// Otherwise, the compiler won't know which one to use.
// This is called "function overloading".

/********************
	PASS BY VALUE
********************/

// When you pass variables into a function, the value gets COPIED, and THEN used in the function.
// For example...

int x = 1;

void addOne(int num) {
	num = num + 1;
}

// If we were to pass x into that function and call it, you'd expect x to equal 2, not 1.
// However, after we call the function, x is still equal to 1. (Just trust me)
/* This is because the value of x is COPIED into the function. The function does not operate on x itself,
   it operates on the VALUE of x, which is 1 in this case. */
// To change x itself, we would need to use a pointer, which is covered in "8-Refs&Pointers.cpp".

/********************
	MAIN FUNCTION
********************/

// The main() function is called the entry point of your program.
// When you run your program, all of the statements in main() get executed in order. That's it.
/* Well, before running main(), global variables are initialized first. This process invokes a function,
   so technically that's the first function that gets called in your program. */
/* The two requirements of main are that...
    1. It must return an int value
    2. You cannot explicitly call main (kinda)
*/
// Here's what the main function looks like:

int main()
{
	return 0; // <-- Sometimes there, sometimes not.
}

// The return value of main() is called a STATUS CODE or an EXIT CODE.
// If main() returns 0 or EXIT_SUCCESS, that means your program executed successfully.
// If main() returns EXIT_FAILURE, your program did not execute successfully.
// If a return value is not specified in main(), it will implicitly return 0.

/* It's best to define all your functions BEFORE main, since the compiler compiles code files from top
   to bottom. */
// If a function is called IN main but defined AFTER main, the compiler will throw an error.
/* You can subvert this with a "forward declaration", which just means defining the function header
   without the body, like this: */

void function2();

// This lets main() know that your function exists, even though it is defined afterwards.
// Don't do this. Forward declarations are pretty much just for header files.