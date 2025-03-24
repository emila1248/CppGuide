// Before we begin...
// Any line of code that starts with "//" is a comment. Comments are ignored by the compiler.
// To comment or un-comment a section of code, highlight it and press "Ctrl + /".

/* Also, this
   is a
   multi-line
   comment. */

/***-**-***-**-***-**-***-**
	You can style them ;)
***-**-***-**-***-**-***-**/

// A VARIABLE is a name you ascribe to a piece of data.
// A variable must be declared with a variable TYPE. Here is a list of the built-in types for C++:


// 1. INTEGERS
// -------------
// Integer variables hold whole numbers, inluding 0 and negative numbers.
/* The only difference between all these integer types is that they each take up a different amount of
   space in memory, thus having different minimum and maximum values. */

			 short integer1;	// 2 bytes: -32768 to 32767
	unsigned short integer2;	// 2 bytes: 0 to 65535
			   int integer3;	// 4 bytes: -2147483648 to 2147483647
	  unsigned int integer4;	// 4 bytes: 0 to 4294967295
			  long integer5;	// 4 bytes: -2147483648 to 2147483647
	 unsigned long integer6;	// 4 bytes: 0 to 4294967295
		 long long integer7;	// 8 bytes: -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807
unsigned long long integer8;	// 8 bytes: 0 to 18,446,744,073,709,551,615

/* The reason why ints and longs hold the same number of bytes is because some machines only use 2 bytes
   to hold an int, thus making a long the larger variable type. */
/* When dividing two integers where the result happens to be a fraction, the decimal part of the value
   gets dropped, NOT rounded. (This is also called flooring a number) */
// Fun fact: You can write numbers in octal (base 8) or hexadecimal (base 16) form like this:

int octal = 012;	// Add a "0" in front for octal.
int hex = 0x1f;		// Add a "0x" in front for hexadecimal.
// In C++14 and above, you can represent binary numbers by putting "0b" at the front.

// If you want to make an integer of a specific size, you can use fixed-width integers, like this:

#include <cstdint> // Must include
std::int8_t fixedInt1;     // 8 bits (1 byte)
std::uint8_t fixedInt2;    // 8 bits, unsigned
std::int16_t fixedInt1;    // 16 bits (2 bytes)
std::uint16_t fixedInt2;   // 16 bits, unsigned

// The same pattern continues for bigger integers.
// NOTE: std::int8_t and std::uint8_t typically behave like chars (discussed in next section).


// 2. CHARS
// ----------
// Char (short for character) variables holds single characters of text.
/* Each character is associated with a number value via the ASCII code. Look up "ASCII table" to see all
   the character-value associations. */
// You can initialize a char with either a character or a number. Here are examples of both:

char char1 = 'A';	// 1 byte: -128 to 127
char char2 = 65;	// 1 byte: -128 to 127

// Both chars hold the same value, since 65 is the ASCII code for 'A'.
// You can also use chars to store integers by putting "signed" or "unsigned" before "char".
// Chars hold 1 byte of data, so use them as integers if you need to save space.


// 3. BOOLEANS
// -------------
// A bool (short for "boolean") can only hold "true" or "false", represented as 1 or 0.

bool trueBool = true;	// 1 byte: Equal to 1
bool falseBool = false;	// 1 byte: Equal to 0

// Initializing a boolean to any other number besides zero will set it as "true".


// 4. FLOATS & DOUBLES
// ---------------------
// A float or double is a variable type that can hold a number with a fractional value.
// It is called a float because the decimal point can "float" between the number of digits.
// Float-type variables are always signed.

	  float floatVar = 1.5f;		// 4 bytes
	 double doubleVar = -1.5;		// 8 bytes
long double ldoubleVar = 3.14159;	// 8, 12, or 16 depending on the platform. Not recommended.

/* For some damn reason, defining a float without the "f" at the end causes the variable to default
   to a double. So make sure to do that. */
/* Also, if your float / double doesn't have a decimal component, it's best to add a .0 at the end so
   the compiler doesn't get confused. */
// You can also define floats/doubles using scientific notation, like this:

float scientificNotation = 3.8e-14f;	// 3.8 x 10^-14

/* The PRECISION of a floating point number refers to the amount of significant digits it can hold
   without information loss. */
// A float has 6-9 digits of precision depending on the value.
// A double has 15-18 digits of precision depending on the value.
/* Due to floats being written in base 10 but being stored in base 2, most of your float values will be
   slightly inaccurate due to rounding. */
// The inaccuracy gets more significant the more mathmatical operations you perform on the number.
// Keep this in mind when comparing two floating point values.


// There are more variable types in C++, but these are the ones you can use without relying on a library.
// The ones above are called the basic, built-in, fundamental, or primitive data types.
// There are other data types called compound data types that are composed of primitive data types.
// An example of this is a string, which is composed of multiple char values.

/*************************
	CREATING VARIABLES
*************************/

// There are 5 basic ways you can initialize a variable. They are as follows:

int way1 = 1;   // initializer after equals sign (copy initialization)
int way2 (2);   // initializer in parentheses (direct initialization)
int way3 {3};   // initializer in braces (direct list initialization)
int way4 = {4}; // initializer in braces after equals sign (copy list initialization)
int way5 {};    // initializer is empty braces (value initialization)

// You can also create an uninitialized variable, like so:
int way6;  // no initializer (default initialization)

/* You can research the differences between these because I don't feel like explaining it, and it's also
   very confusing. */
// way1 is the most common/readable, but learncpp.com recommends way3. Honestly, just use whatever.
// Except way2, because it looks too similar to a function (discussed later).

// You can also initialize multiple variables at once, like this:

int a, b;
int c = 1, d = 2;

/* If you want the compiler to pick a compatible type for your variable, use the "auto" keyword,
   like this: */

auto e = 3.5;	// Hover over the value to see what type the compiler assigned it to

// A constant variable is a variable that cannot be changed once defined, like this:

const float PI = 3.14159f;	// Don't use const anymore. Use constexpr

// You cannot declare a constant without giving it a value.
// Constants are usually written in all caps to distinguish them from regular variables.
// UPDATE: Instead of "const", use "constexpr". It's a better version of "const".

/***********
	TIPS
***********/

// 1. Anything with a "_t" suffix is usually a type.

// 2. Use the "sizeof" operator to know how many bytes a variable takes up. For example:

char var = 'v';
int sizeOfVar = sizeof(var);	// "sizeOfVar" is equal to 1, since a char is 1 byte.

// This operator return a value of type "size_t".
// size_t is an unsigned integral-type variable, except the compiler will decide how big it is.

/* 3. You might assume that types that use less memory would be faster than types that use more memory.
   This is not always true. CPUs are often optimized to process data of a certain size (e.g. 32 bits),
   and types that match that size may be processed quicker. */