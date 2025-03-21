/*****************
    STD::ARRAY
*****************/

// An std::array is essentially a fixed-sized vector, and is slightly more performant.
// The syntax for an std::array is as such:

#include <array>
std::array<int, 4> arr;  // Parameter 1 is the array type, and parameter 2 is the length.
std::array<int, 4> arr { 1, 2, 3, 4 };

// You can use a variable for the second parameter, but it MUST be const or constexpr.
// The whole array can also be const or constexpr.

// Just like a vector, array elements can be accessed using the subscript operator [].
// The length can be accessed with the size() function.
// To pass an array into a function, you must include the type and size, like so:

void func(std::array<int, 4>& arr) {}

// To pass an array of any type or length, you can use a template, like this:

template <typename T, std::size_t N>  // The type for array length MUST be std::size_t or auto (C++ 20)
void func2(std::array<T, N>& arr) {}

// Note that std::array is not move-capable, meaning that returning it by value invokes a copy.
// The elements INSIDE of the array will be moved if they are move-capable, and copied otherwise.
// Copying an array is fine if it isn't huge and the elements are cheap to copy or move.
// A method we can use to avoid making a copy is passing the std::array as an out-parameter, like this:

void oneToFour(std::array<int, 4>& arr) {
    arr[0] = 1; arr[1] = 2; arr[2] = 3; arr[3] = 4;
}

// The function operates on a REFERENCE to an aray, therefore no copy is made.
// You should also consider returning a vector instead of an std::array since vectors are move-capable.

/*********************
    C-STYLE ARRAYS
*********************/

// C-style arrays were inherited from the C language, and are built-in to the core language of C++.
// For declaration, we use [] to tell the compiler that a declared object is a C-style array.
// Inside the square brackets, we can optionally provide the length of the array (must be >= 1).
// So declaring an array of 4 integer elements would look like this:

int four[4];

/* Just like a std::array, C-style arrays (and pointers to such arrays) can be indexed using the
   subscript operator []. */
/* NOTE: When declaring an array, the use of [] is part of the declaration syntax, NOT an invocation of
   the subscript operator. */

// Just like std::array, C-style arrays are aggregates, which means they can be initialized like this:

int evens[] { 2, 4, 6, 8 };

// Notice that the length of the array (in between the []) is missing in the above declaration.
// That is ok if you provide a list of values to initialize it with (so you don't have to count them).
// To get the length of a C-style array, you can use std::size() defined in the <iterator> header.

#include <iterator>
int length = std::size(evens);

// Note that the <array> and <vector> headers also have the <iterator> header included.

// One important thing to know about is array decay, which is basically this:
// When passing a C-style array as an argument, the array decays into a pointer.
// This means that C-style arrays are actually passed by address instead of value.
// In this decayed form, the length of the fixed array is not available
// Here's what a function using a C-style array parameter looks like:

void func3(int arr[]) {}

// Because of the non-standard passing semantics and decay, try to avoid C-style arrays.

// POINTER ARITHMETIC
// -------------------
// Pointer arithmetic allows us to apply certain operators to a pointer to get a new memory address.
/* For example, for pointer ptr, ptr + 1 returns the address of the next object in memory (based on the
   type being pointed to). */
// So if ptr is an int pointer, the next memory address will be 4 bytes away.

// C-STRINGS
// ----------
// C-style strings are just C-style arrays whose element type is char or const char.
// They have fallen out of favor in modern C++, but you may still see them in older code.
// To define a C-string, simply declare a C-style array variable of char, like this:

const char cstr[] = "string";

// If you hover over the variable, you'll see that the length of the above array is 7, not 6.
// This is because C-strings have a null terminator character at the end of each string.
// The reason for this is because C-strings decay into pointers, just like C-style arrays.
// There are helpful functions to work on C-strings in the <cstring> header.
/* A useful one is std::strlen(), which returns the length of the string even if the underlying array
   is larger in size. */

// TIP: Avoid non-const C-strings, as they are prone to overruns. Also just avoid C-strings in general.

/***************************
    2-DIMENSIONAL ARRAYS
***************************/

// An array of arrays is a 2-dimensional array.
// The syntax for one is like so:

int arr2D[3][4]; // An array with 3 "rows" and 4 "columns"

// You can index an element like this:

int firstIdx = arr2D[0][0];

// In memory, C++ uses row-major order to store each element, which means the order looks like this:
// [0][0] , [0][1] , [0][2] , [0][3] , [1][0] , [1][1] , [1][2] , [1][3]...
// When traversing an array, it's most efficient to access elements in the order they are in memory.
// It's easiest to initialize multi-dimensional arrays like this:

int threeByThree[3][3] {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};

// To loop through a 2-dimensional array, you'll need a nested for loop.
/* To access the elements as they're stored in memory, the outer loop should be for the rows and the
   inner loop should be for the columns. */