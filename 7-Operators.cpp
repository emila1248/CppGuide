// An OPERATION is a mathematical process involving zero or more input values that produces a new value.
/* The specific operation to be performed is denoted by a construct (typically a symbol or pair of symbols)
   called an operator. */
/* All operators are assigned a level of precedence. Operators with a higher precedence level are grouped
   with operands first. */
/* If two operators with the same precedence are adjacent to each other, the operator's ASSOCIATIVITY tells
   the compiler to evaluate the operators (NOT the operands) from left to right or from right to left. */
// For basic arithmetic, C++ follows PEMDAS. (Except for "E" since exponents don't have their own operator)
/* A good rule of thumb to ensure everything gets evaluated in the order you want them to is to parenthesize
   everything except addition (+), subtraction (-), multiplication (*), and division (/). */

// There is also the modulus operator (%) which returns the remainder when dividing two numbers.
/* When dividing one positive and one negative number, the modulus operator will still work. The result
   will have the same sign as the first operand (unlike in regular mathematics). */

// Note: If you want to use an exponent, use the "pow()" function in the cmath library:

#include <cmath>
int eight = pow(2, 3);


// Dividing Integers and Floats:
// ------------------------------
// If one or both of the operands is a float type, dividing them will also result in a float type.
/* If the operands are both integers, the result will also be an integer, meaning that everything after
   the decimal point is DROPPED, not rounded. */
// If you don't want the fractional part dropped, simply cast one of the operands as a float or double.


// A lot of the time you'll want to operate on a variable, then assign that value to the variable itself.
// This can be done like so:

int x;
int y;

x = x + y;

// A shortcut for this is to use the +=, -=, *=, /=, or %= operator, like this;

x += y;


// Increment/Decrement operators
// ------------------------------
// Adding and subtracting 1 from a variable is so common that it has it's own operators.

// ++num = Increment num first, then return it
// --num = Decrement num first, then return it
// num++ = Return num first, then increment it
// num-- = Return num first, then decrement it

// In cases where prefixing or suffixing the operator will both work, prefer prefixing.


// Conditional/Ternary Operator
// -----------------------------
/* The conditional operator determines if a condition is true or false, then returns one of two values;
   the 1st value if the condition is true, and the 2nd value if the condition is false. */
// Here is the syntax:

condition ? value1 : value2;

// For example, let's say we have the ages of two people, and want to store the age of the older person.
// We can do it like this:

int age1 = 20;
int age2 = 30;

int oldestAge = age1 > age2 ? age1 : age2;
// English translation: Is age1 greater than age2? If so, return age1. If not, return age2.

// It's best to only use the ternary operator for simple conditions, not complex ones.


// Relational Operators
// ---------------------
// Relational operators determine how two values relate to each other. Here are your options:

// x > y	Is x greater than y?
// x < y	Is x less than y?
// x >= y	Is x greater than or equal to y?
// x <= y	Is x less than or equal to y?
// x == y	Is x equal to y?
// x != y	Is x not equal to y?

// Each expression returns a boolean value of 1 (true) or 0 (false).

// Be careful when using one of these operators to compare two floating point values.
// This is because representing base 10 decimals as base 2 decimals results in tiny rounding errors.
// So your value of 0.1 might actually be 0.100000000000001.
// This is really only a problem with the == and != operators.
// Instead, compare the DIFFERENCE between two floating point values.


// Logical Operators
// ------------------
// The three logical operator are AND (&&), OR (||), and NOT (!).
// They work like this:

bool condition1 = true;
bool condition2 = false;

if (condition1 && condition2)	// If condition1 AND condition2 are true...
if (condition1 || condition2)	// If condition1 OR condition2 OR both are true...
if (!condition1)				// If condition1 is NOT true...

/* For the AND operator, if the first condition is false, the second condition will not be evaluated.
   This can be useful for optimization purposes. */

// What if you want to know if only ONE of the conditions is true? This is called the XOR operator.
// Some languages have this operator, but C++ does not.
// A way to get around this is to use the != operator instead. For example:

if (condition1 != condition2) // This means that one has to be false, and the other has to be true.

/* If you need to use the XOR operator on values that aren't booleans, you can just cast them as booleans
   before using != */

// You can also use the "and", "or", and "not" keywords instead of their respective symbols, like this:

if (condition1 and condition2)
if (condition1 or condition2)
if (not condition1)

#include "fakeheader.h"