/* In general programming, a container is a data type that provides storage for a collection of unnamed
   objects, called elements. */
// For example, a std::string container provides storage for a collection of characters.
// In programming, the number of elements in a container is often called it’s length (sometimes size).
// Keep in mind that the term “size” can also refer to the number of bytes of memory used by an object.
// Containers typically implement a significant subset of the following operations:
// Create a container, access elements, insert/remove elements, and get the number of elements.
// Containers may also provide other operations that assist in managing the collection of elements.
/* Every container has a set of strengths and limitations. Picking the right container for the task you're
   trying to solve can have a huge impact on code maintainability and overall performance. */
// In C++, containers are homogenous, meaning the elements of a container must be of the same type.

/* The Containers library is a part of the C++ standard library that contains various class types that
   implement some common types of containers. */
// In C++, the definition of “container” is narrower than the general programming definition.
/* The following types are containers under the general programming definition, but are not considered to
   be containers by the C++ standard: */
// C-style arrays, std::strings, and std::vector<>s

// An array is a container data type that stores a sequence of values contiguously.
// This means that each element is placed in an adjacent memory location with no gaps.
// Arrays allow fast, direct access to any element. They are conceptually simple and easy to use.
// C++ contains three primary array types: C-style arrays, std::vector<>, and std::array.
// C-style arrays were inherited from the C language and kept in C++ for backwards compatibility.
// By modern standards, C-style arrays behave strangely and are dangerous.
/* std::vector is the most flexible of the array types, and has a bunch of capabilities that the other
   array types don’t. */
/* One nice thing is that all of the container classes have similar interfaces; once you learn how to use
   one, learning the others becomes a lot easier. */

/**************
    VECTORS
**************/

/* std::vector is defined in the <vector> header as a class template, with a template type parameter that
   defines the type of the elements. */

#include <vector>
std::vector<int> vec;
std::vector<char> vowels {'a', 'e', 'i', 'o', 'u'};

/* Containers typically have a special constructor called a list constructor that allows us to construct an
   instance of the container using an initializer list (curly brackets). */
// The list constructor does three things:
// 1. Ensures the container has enough storage to hold all the initialization values
// 2. Sets the length of the container to the number of elements in the initializer list
// 3. Initializes the elements to the values in the initializer list in sequential order

/* The most common way to access array elements is by using the name of the array along with the subscript
   operator [] like this: */

char a = vowels[0]; // Access element at position 0

// When indexing an array, the index provided must select a valid element of the array.
// That is, for an array of length n, the index must be a value between 0 and n-1.
// The subscript operator does not do any bounds checking, so providing a valid index is up to you.
// An alternative method that does bounds checking at runtime is using the .at(n) member function.
// Instead of resulting in undefined behavior, at(n) generates an error that terminates the program.
// Although at(n) is safer (but slower), the subscript operator is used more often.

/* One of the defining characteristics of arrays is that the elements are always allocated adjacently in
   memory. */
/* Arrays are one of the few containers that allow for random access, meaning any element in the container
   can be accessed directly as opposed to sequentially. */
// Random access to elements is efficient and makes arrays very easy to use.

// To create an empty vector of a pre-defined size, use this syntax:

std::vector<int> empty(16);

// If the vector is part of a class-type, this syntax will not work. Instead, use this:

struct MyStruct {
    std::vector<int> empty{ std::vector<int>(8) };
};

// To return the length of a vector, just use the .size() member function.
// Something to note is that the return value of that function is an unsigned int, not a "regular" int.
/* This means that storing the length of a vector using a "regular" int will involve an unsigned-to-signed
   type conversion. */

/* The easiest and best way to loop through each member of an array-type is called a "range-based for loop"
   and works as such: */

for (char vowel : vowels) {  // Translation: "for each vowel" : "in the "vowels" vector," {do this...}
    std::cout << vowel << "\n";
};

// Note: Avoid using vector<bool>. It behaves differently than vectors of any other type.
// This is called "class template specialization" and will be discussed in a different section.

/**********************
    VECTOR RESIZING
**********************/

// Once thing about a vector is that it has the ability to resize itself after it has been instantiated.
// And array with the ability to resize is called a dynamic array.
// One way to resize a vector is to use the resize function, like this:

vec.resize(6);

// The maximum amount of elements a vector can hold is called its capacity.
// To get the capacity of a vector, use the .capacity() member function.

/* Reallocation is when a vector changes the amount of storage it is managing. The process is (essentially)
   as follows: */
// 1. The vector acquires new memory with capacity for the desired number of elements.
// 2. The elements in the old memory are copied (or moved, if possible) into the new memory.
// 3. The capacity and length of the std::vector are set to the new values.
// Reallocation is expensive, so do your best to avoid it.
// Note: The process of acquiring new memory at runtime is called dynamic memory allocation.

// Making a vector smaller will only decrease its length, not it's capacity.
// To change that, call the shrink_to_fit() method after the resize(n) method.

// You can add elements to a vector like this:

vec.push_back(1);   // Adds element to the back of a vector.
vec.pop_back();     // Removes the element at the back of a vector.
vec.emplace_back(2) // Same as push_back(), but can be more efficient (see line 135).

/* Note that when creating a vector with an initialized capacity, (as in line 69) you set the capacity AND
   length of the vector. (each element is zero-initialized) */
// This means that using push/pop will add an element AFTER all the zero-initialized values.
// To circumvent this, we can use the reserve() function, like so:

std::vector<int> vec2;
vec2.reserve(4);  // Changes the capacity, but not the length.

/* When you add an element that exceeds the vector's capacity, the compiler will automatically reallocate
   memory for it. */
// How much memory depends on the compiler.
// GCC and Clang doubles the current capacity, and Visual Studio 2022 multiplies it by 1.5.

// push_back() vs. emplace_back()
// -------------------------------
// Both push_back() and emplace_back() push an element onto the stack.
/* If the object to be pushed already exists, push_back() and emplace_back() are equivalent but push_back()
   should be preferred.*/
// In cases where we create a temporary object to be pushed onto the vector, prefer emplace_back().

// std::reference_wrapper
// -----------------------
/* Fixed arrays and the various standard library lists (like std::vector) can’t hold references because list
   elements must be assignable, and references can’t be reassigned. */
// Instead of references we could use pointers, but that opens the possibility to store/pass null pointers.
// To solve this problem, we can use std::reference_wrapper.
/* Essentially, std::reference_wrapper is a class that acts like a reference, but also allows assignment and
   copying, so it’s compatible with lists.*/
// All you really need to know are three things:
// 1. std::reference_wrapper lives in the <functional> header.
// 2. When you create your wrapped object, the object can’t be an anonymous object.
// 3. To get your object back out of std::reference_wrapper, you can use the get() member function.

/****************************
    COPY & MOVE SEMANTICS
****************************/

// The term copy semantics refers to the rules that determine how copies of objects are made.
/* When we say a type supports copy semantics, we mean that objects of that type are copyable because the
   rules for making such a copy have been defined. */
// For class types, copy semantics are implemented via the copy constructor (and copy assignment operator).

// When ownership of data is transferred from one object to another, we say that data has been moved.
// Move semantics refers to the rules that determine how the data from one object is moved to another.
// The cost of a move is typically trivial, usually just involving two or three pointer assignments.
/* When move semantics is invoked on a class type, any data member that can be moved is moved, and any data
   member that can’t be moved is copied. */
// Not that many types support move semantics, however std::vector and std::string do.

/* Since std::vector supports move semantics, vectors that are returned by value can be moved instead of
   copied into the destination object; so returning them by value is fine. */
// To summarize, for move-capable types, we prefer to pass by reference and return by value.

/******************************
    USEFUL VECTOR FUNCTIONS
******************************/

void vectorFunctions() {  // (Listed alphabetically)
    std::vector<int> v { 1, 2, 3, 4, 5, 6 };

    int idx = v[0];             // Access element at specified index
    int back = v.back();        // Gets element at the back of vector
    std::size_t cap = v.capacity();  // Returns the capacity of the vector
    v.clear();                  // Clears the contents of the vector, but leaves the same capacity
    int n = v.data()[0];        // Returns a pointer to the underlying C-style array
    v.emplace_back(0);          // Adds element to the end of vector
    bool empty = v.empty();     // Checks if the vector is empty (if size = 0)
    int front = v.front();      // Gets element at the front of vector
    v.pop_back();               // Removes the last element
    v.push_back(0);             // Adds element to the end of vector
    v.reserve(2);               // Changes the capacity of the vector
    v.resize(3);                // Changes the capacity and size of the vector
    v.shrink_to_fit();          // Makes the capacity = the length of the vector
    std::size_t size = v.size();     // Returns the number of elements
}

#include "fakeheader.h"