// C++ supports three basic types of memory allocation, of which you’ve already seen two.
/* Static memory allocation: Static and global variables. Memory for these types is allocated once when
   your program is run and persists throughout the life of your program. */
/* Automatic memory allocation: Function parameters and local variables. Memory for these types is
   allocated when the relevant block is entered, and freed when the block is exited. */
// Dynamic memory allocation: Discussed below:

/********************************
    DYNAMIC MEMORY ALLOCATION
********************************/

// Both static and automatic allocation have two things in common:
// 1. The size of the variable/array must be known at compile time.
// 2. Memory allocation/deallocation happens automatically when the variable is instantiated/destroyed.

/* You will come across situations where one or both of these constraints cause problems, usually when
   dealing with external (user or file) input. */
/* For example, we may want to use a string to store someone’s name, but we do not know how long it is
   until they enter it. */
// The best we can do (for now) is try to guess the maximum size of the variable we’ll need.
// Most normal variables (including fixed arrays) are allocated in a portion of memory called the STACK.
/* The amount of stack memory for a program is generally quite small. (Visual Studio defaults the stack
   size to 1MB) */
/* If you exceed this number, stack overflow will result and the operating system will probably close down
   the program.*/
// Fortunately, these problems are easily addressed via dynamic memory allocation, which is essentially:
// A way for running programs to request memory from the operating system when needed.
/* This memory is allocated from a much larger pool of memory called the HEAP. */
// On modern machines, the heap can be gigabytes in size.

// To allocate a single variable dynamically, we can use the "new" keyword, like so:

new int;

// In the above case, we’re requesting an integer’s worth of memory from the operating system.
/* The "new" operator creates the object using that memory, then returns a pointer containing the address
   of the memory. */
// Most often, we’ll assign the return value to our own pointer so we can access the allocated memory.

int* ptr = new int{4};

// Note that accessing heap-allocated objects is generally slower than accessing stack-allocated objects.

// How does dynamic memory allocation work?
// -----------------------------------------
// Your computer has memory (probably lots of it) that is available for applications to use.
// When you run an application, your operating system loads the application into some of that memory.
// The memory used by your application is divided into different areas, each serving a different purpose.
// One area contains your code, another area is used for normal operations, etc.
// Much of the memory available just sits there, waiting to be handed out to programs that request it.
/* When you dynamically allocate memory, you’re asking the operating system to reserve some of that memory
   for your program’s use. */
// If it can fulfill this request, it will return the address of that memory to your application.
// From that point forward, your application can use this memory as it pleases.
// When your application is done with the memory, it can return the memory back to the operating system.
/* Unlike static or automatic memory, the program itself (AKA you) is responsible for requesting and
   disposing of dynamically allocated memory. */

/* When we are done with a dynamically allocated variable, we need to explicitly tell C++ to free the memory
   for reuse. */
// For single variables, this is done via the "delete" operator:

delete ptr;

// The delete operator does not ACTUALLY delete anything.
// It simply returns the memory back to the operating system, which is then free to reassign it.
// Although the syntax makes it look like we’re deleting a variable, this is not the case.
// The pointer variable still has the same scope as before, and can be assigned a new value, like this:

ptr = nullptr;

/* In summary, the old memory was returned to the operating system, and we repurposed our ptr variable to
   point to a new value (in this case, a null pointer). */
/* C++ does not make any guarantees about what will happen to the contents of deallocated memory, or to the
   value of the pointer being deleted if you do not set it yourself. */
/* In most cases, the memory returned to the operating system will contain the same values it had before it
   was returned, and the pointer will be left pointing to the now deallocated memory. */
// A pointer that is pointing to deallocated memory is called a dangling pointer.
// Dereferencing or deleting a dangling pointer will lead to undefined behavior.
// Here is a short function demonstrating this:

#include <iostream>
void function() {
    int* ptr{new int}; // Dynamically allocate an integer
    *ptr = 7; // Put a value in that memory location

    delete ptr; // Return the memory to the operating system (ptr is now a dangling pointer)

    std::cout << *ptr; // Dereferencing a dangling pointer will cause undefined behavior
    delete ptr; // Trying to deallocate the memory again will also lead to undefined behavior
}

// Here are some best practices that can keep your code clean:
/* 1: Avoid having multiple pointers point at the same piece of dynamic memory. If this isn't possible, be
      clear about which pointer “owns” the memory and is responsible for deleting it. */
/* 2: When you delete a pointer, if that pointer is not going out of scope immediately afterward, set the
      pointer to nullptr. */

// In rare circumstances, the operating system may not have any memory to grant a request with.
// By default, if "new" fails, a "bad_alloc" exception is thrown.
// If this exception isn’t handled, the program will simply terminate with an unhandled exception error.
/* Thankfully, there’s an alternate form of "new" that can be used instead to tell new to return a null
   pointer if memory can’t be allocated. */
// This is done by adding the constant std::nothrow, like this:

int* ptr2 = new (std::nothrow)int;

// Note that if you attempt to dereference this pointer, undefined behavior will result.
// The best practice is to check all memory requests to ensure they actually succeeded before using them.
// Because asking new for memory only fails rarely, it’s common to forget to do this check.

/* In the context of dynamic memory allocation, a null pointer basically says “no memory has been allocated
   to this pointer”. */
// This allows us to do things like conditionally allocate memory:

if (!ptr) { ptr = new int; } // Basically: if ptr isn't already allocated, allocate it

// Deleting a nullptr has no effect, so there's no need to check if a pointer is null before deleting it.
// If the pointer is non-null, the memory will be returned. If not, nothing will happen.

/*******************
    MEMORY LEAKS
*******************/

// Dynamically allocated memory stays allocated until it is explicitly deallocated or the program ends.
/* However, the pointers used to hold dynamically allocated memory addresses follow the normal scoping rules
   for local variables. */
// This mismatch can create interesting problems. Here is an example:

void doSomething() { int* ptr = new int; }

// This function allocates an integer dynamically, but never frees it using delete.
// When the function ends, ptr will go out of scope.
/* Because ptr is the only variable holding the address of the dynamically allocated int, when ptr is
   destroyed, there are no more references to the allocated memory. */
// As a result, this dynamically allocated integer cannot be deleted. This is called a "memory leak".
// When this happens, your program can’t delete the memory because it no longer knows where it is.
// The operating system can’t use it because the memory is still considered to be in use by the program.
/* Programs with severe memory leaks can eat all the available memory, causing the entire machine to run
   slowly or even crash. */
// Only after your program terminates is the operating system able to reclaim the leaked memory.
// There are other ways to cause a memory leak besides a pointer going out of scope.
// For example, a memory leak can occur if a pointer is assigned a new value without deleting it first.

/*************
    ARRAYS
*************/

/* Unlike a fixed array, dynamically allocating an array allows us to choose its length at runtime
   (typically via user input). */
/* Note: We’ll be dynamically allocating C-style arrays here, which is the most common type of dynamically
   allocated array. */
/* While you can dynamically allocate a std::array, you’re usually better off using a non-dynamically
   allocated std::vector */

// To allocate an array dynamically, we can use the array form of new and delete:

int* array = new int[5]; // The length of dynamically allocated arrays has type std::size_t
delete[] array; // Memory returned to OS

// You can also initialize your dynamically allocated arrays like this:

int* array2 = new int[3]{ 1, 2, 3 };

// Because dynamic allocation occurs on the heap, the size of the array can be quite large.
// Because of this, programs that need to allocate a lot of memory in C++ typically do so dynamically.
// Also, when deleting an array, don't forget to use "delete[]" and not "delete".
// The brackets tell the CPU it needs to clean up multiple variables instead of just one.

// C++ does not provide a built-in way to resize an array that has already been allocated.
/* It's possible to work around this by dynamically allocating a new array, copying the elements over, and
   deleting the old array. */
// However, this is error prone, especially when the element type is a class.
// You're probably better off using a std::vector instead.

/* NOTE: When a dynamically allocated object is explicitly deleted using the delete keyword, the class
   destructor is automatically called (if it exists) to do any necessary clean up. */
// For simple classes, a destructor is not needed because C++ will automatically clean up the memory.
/* However, if your class object is holding any resources (ex. dynamic memory) you need to ensure the memory
   is freed upon object destruction. */
// You can delete any dynamically allocated data members in the class's destructor.

#include "fakeheader.h"