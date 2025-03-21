/**************************
    LVALUES AND RVALUES
**************************/

// An LVALUE (l for left) is an expression that evaluates to an indentifiable object or function.
// "Identifiable" means that the object can be referred to by name in your program. For example:

int x = 1;

// x is an lvalue because I can reference it again, like this:

x = x + 1;

// "1" is not an lvalue because I can't refer to it again once I use it.
// I can still use the VALUE of 1, but I can't reference any specific "1" in my code.
// "1" is an example of an rvalue.

// An RVALUE (r for right) is a value that is NOT identifiable, and only exists within an expression.
/* rvalues don't have to be just a single item like "1" or 'A', they can also be expressions or functions
   that EVALUATE to an rvalue. For example... */

int y = 2;
y = y * 2;	// The expression "y * 2" is an rvalue since it evaluates to "4" (an rvalue).

// In summary...
// lvalues evaluate to an INDENTIFIABLE OBJECT that lasts beyond the expression it's in.
// rvalues evaluate to a VALUE that does not last beyond the expression it's in.

/*****************
	REFERENCES
*****************/

// A REFERENCE is just an alias for an existing object.
// The same as how a variable is an alias for a value, a reference is an alias for a variable.
// You can define a reference by putting an "&" after the variable type, like this:

int& ref = x;	// This is an lvalue reference, often just called a reference.

// If you change the value of the variable, it changes the value of the reference, and vice versa.
// You can NOT change an lvalue reference to reference a different variable once you initialize it.
// You also cannot have a reference to a reference.
// A const variable must have a const reference, but a const reference does not have to have a const variable.
/* If you have a const reference but a non-const variable, you can change the value by reassigning the
   variable, but NOT by reassigning the reference. */

/* TIP: Use a reference as a parameter to a function to prevent a potentially expensive copy from being made.
   When doing this, avoid type conversion, as this might involve a copy. */
// Fundamental data types are cheap to copy, unlike object types such as std::string.
/* TIP: When it comes to strings, use string_view as a parameter instead of a string reference. Why?
   Idk it's complicated. */

/***********************
	MEMORY ADDRESSES
***********************/

// Anytime you store a piece of data (such as a variable) it gets assigned a memory address.
// It works the same as house addresses: You have a friend name Carl, and he lives at 250 Main St.
// "Carl" = the piece of data, and 250 Main St. = the memory address.
/* Instead of a number and a street name, memory addresses are just one big number, usually written as a
   hexadecimal value. */
// To get the address of a variable, simply put a "&" in front of it.
// For example, if your variable name is "x", the address of x would be represented as "&x".

// !!! IMPORTANT !!! : The "&" symbol in this context does NOT, I repeat, does NOT mean "reference".
// If the "&" is attached to a TYPE (such as int or char) it = reference.
// If it is attached to a VARIABLE NAME (such as x) it = memory address.

/* If you have the address of a variable but want to access the VALUE that is STORED at that address,
   use the dereference operator (*) <-- */
// Simply place it before the name of the address, like this:

int value = 1;
auto addressOfValue = &value;
int valueAgain = *addressOfValue;

/***************
	POINTERS
***************/

// A pointer is an object that holds a memory address as its value.
// To initialize a pointer, use the "*" symbol, like this:

int var1 = 2;			 // The variable
int* varPointer = &var1; // The POINTER to the variable

// !!! IMPORTANT !!! : The "*" in this context is NOT a dereference operator.
// If the "*" is attached to a TYPE, it signifies a POINTER.
// If it is attached to a VARIABLE NAME, it is the DEREFERENCE OPERATOR.

// Just like a reference, you can use a pointer to reassign the value of a variable, like this:

*varPointer = 3; // (dereference it first)

// UNLIKE a reference, you can change the memory address your pointer points to, like this:

int var2 = 4;
varPointer = &var2;	// varPointer now points to var2, NOT var1

// Also unlike a reference, you can declare a pointer without giving at a value, like this:

int* pointer;

// Declaring a pointer without defining it makes it a "null pointer".
// You can also explicitly initialize a null pointer by using the "nullptr" keyword, like this:

int* nullPointer = nullptr;

// If you destroy the object that your pointer is pointing to, it does NOT automatically become null.
// It is considered a "dangling pointer". These are bad because they can lead to undefined behavior.
// It is the programmer's responsibility to set dangling pointers as "nullptr".
// Also, do NOT dereference a null pointer. This will lead to undefined behavior.

#include "fakeheader.h"