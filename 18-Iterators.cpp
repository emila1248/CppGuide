/* An iterator is an object designed to traverse through a container, providing access to each element
   along the way. */
// A container may provide different kinds of iterators.
/* For example, an array might provide a forwards iterator that walks through the array in forward order,
   and a reverse iterator that walks through the array in reverse. */
/* The simplest kind of iterator is a pointer, which (by using pointer arithmetic) works for data stored
   sequentially in memory. */
// We can create 2 pointer iterators like this:

#include <array>
std::array<int, 3> arr = {1, 2, 3};

int* begin = &arr[0];  // Pointer to first element
int* end = begin + std::size(arr);  // Pointer to 1 spot BEYOND the last element

/* Note that for arrays, the end marker is typically the place in memory where the last element would be
   if the container contained one more element. */
// Iterating is such a common operation that all standard library containers offer direct support for it.
/* We can simply ask the container for the begin and end points through the member functions named begin()
   and end(), like this: */

auto begin2 = arr.begin();
auto end2 = arr.end();

/* Note: For C-style arrays, the begin and end functions are in the <iterator> header. Otherwise they can
   be found in the respective container's header file. */
/* Also note: When comparing iterators, use == or != rather than < or >, as pointers are memory addresses,
   not values. */
// To access the values at each pointer, you must dereference it first.

// All containers that support begin() and end() also support range-based for loops.
// These loops actually use iterators behind the scenes, just like std::sort and other algorithms.
/* Much like pointers and references, iterators can be left “dangling” if the elements being iterated over
   change address or are destroyed. */
// When this happens, we say the iterator has been invalidated. Accessing it produces undefined behavior.

/*****************
    ALGORITHMS
*****************/

/* Searching, counting, and sorting containers are such common operations to do that the C++ standard
   library contains a bunch of functions to do those very things. */
// These functions are pre-tested, efficient, and work on a variety of different container types.
// They can be found in the <algoritm> header

// The functionality provided in the algorithms library generally falls into one of three categories:
// 1. Inspectors - Used to view (but not modify) data in a container. (Ex. searching, counting)
// 2. Mutators - Used to modify data in a container. (Ex. sorting, shuffling)
// 3. Facilitators - Used to generate a result based on values of the data members.

// Here are some of the most useful ones:

// std::find
// ----------
// std::find() searches for the first occurrence of a value in a container.
/* It takes 3 parameters: an iterator to the starting element, an iterator to the ending element, and a
   value to search for. */
// It returns an iterator pointing to the element if found, or the end of the container if not found.
// Here is an example:

#include <algorithm>
std::array<int, 10> nums = {8, 4, 6, 1, 2, 9, 3, 5, 7, 0};

auto idxOfOne = std::find(nums.begin(), nums.end(), 1);
//      ^  Pointer to element OR end of array

// There is also std::find_if(), which searches for the first element that meets a certain condition.
/* The first two parameters are the same as std::find(), but the last one needs to be a callable object,
   such as a function pointer (or a lambda, which we’ll cover later). */
/* For each element, std::find_if() will call the function and return the desired pointer if the function
   evaluates to true. */
// Here is an example:

bool isEven(int n) {
    return n % 2 == 0 ? true : false;
}
auto firstEvenNum = std::find_if(nums.begin(), nums.end(), isEven);
//                                                            ^ No parentheses for function pointer

// std::count
// -----------
/* std::count() and std::count_if() search for all occurrences of an element, or an element fulfilling a
   certain condition. */
// Returns the number of pointers found. Can be stored in an integral-type variable.

int evens = std::count_if(nums.begin(), nums.end(), isEven); // Counts all even numbers

// std::sort
// ----------
/* By default, std::sort() sorts the elements of a container in ascending order by using the < operator to
   compare each element. */
// The first two parameters are the start and end iterators of your container.
/* You can pass in a third parameter, which is a function pointer to tell std::sort how you want your
   elements sorted. */
// Here is an example of sorting an array in DESCENDING order:

template <typename T>
bool isGreater(T a, T b) {
    return (a > b);
}
std::array sortedArr = nums;
std::sort(sortedArr.begin(), sortedArr.end(), isGreater<int>);

// Notice that we made a copy of "nums", then sorted the COPY.
// This is because std::sort operates directly on the array. It has no return value.
// Sorting items in descending order is so common that the standard library provides a custom type for it:

std::sort(sortedArr.begin(), sortedArr.end(), std::greater{});
//                                                  ^ Needs curly braces bc it's not a callable function

// std::for_each
// --------------
// std::for_each() takes a list as input and applies a custom function to every element, like this:

void doubleNum(int& n) {
    n *= 2;
}
std::array doubledArr = nums;
std::for_each(doubledArr.begin(), doubledArr.end(), doubleNum);

// std::for_each() works the same as a range-based for loop.
// One of the benefits is that it can operate on a specified section of a container, unlike the for loop.
// For example, if you only wanted to affect elements 4-8, you can do that with std::for_each().



// There are plenty of other algorithms in the <algoritms> library that you can use.
// Here are a few of the most useful ones, but go to https://en.cppreference.com/w/cpp/algorithm for more.

void algorithmFunctions() {
    std::copy();            // Copies a range of elements to a new location (has _if version)
    std::equal();           // Determines if two sets of elements are the same
    std::find_if_not();     // Like std::find_if, but opposite
    std::find_last();       // Finds last occurance of element (has _if version)
    std::for_each_n();      // Applies a function to the first N elements of a sequence
    std::is_sorted();       // Checks whether a range is sorted into ascending order
    std::move();            // Moves a range of elements to a new location
    std::merge();           // Merges two sorted ranges
    std::reverse();         // Reverses the order of elements in a range
    std::shuffle();         // Randomly re-orders elements in a range
    std::swap();            // Swaps the values of two objects
}

#include "fakeheader.h"