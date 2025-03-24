// A string is a collection of sequential characters.
// Most programming languages have strings as a fundamental data type since they are so common.
// For historical reasons, that is not the case with C++.

/****************
    C STRINGS
****************/

// C++ uses strings called "C strings" or "C-style strings", as they are inherited from the C language.
// There are two non-obvious things about C strings:
/* 1. All strings have a null terminator that signifies the end of a string. For example, the string
      "Hello" has 6 characters: 'H', 'e', 'l', 'l', 'o', and '\0'. */
/* 2. C strings are const objects that are created at the start of the program and are guaranteed to
      exist for the entirety of the program. */

/* Note: ALL string literals (anything between double quotes) are C strings. In fact, you can hover
   your mouse over a string literal, and you will see that they are all of the type "const char[]" */
// You can define a C string like this:

const char* cString = "C String";   // const because C strings are IMMUTABLE

/* Since C strings can be tough to work with, the prefered way to define strings is with std::string
   or std::string_view. */
/* The std:: at the beginning just means that they are from the std library. Only fundamental data types
   are without a prefix. */
/* In order to use these new data types, you MUST include them at the beginning of your program, like
   this: */

#include <string>
#include <string_view>  // Only exists in C++17 and onward

/**************
    STRINGS
**************/

// Unlike a C string, a std::string can hold strings of different lengths, like this:

std::string name = "Belle"; // Initialized with 5 characters
name = "Annabelle";         // Changed to 9 characters
name = "Anna";              // Changed to 4 characters

// You can get the length of a string like this:

size_t nameLength = name.length();

/* The length() function returns a value of type size_t. However, since size_t is still an integral type
   value, we can cast it to another integral type, like this: */

int intNameLength = name.length();

/* There is also a type of string called a wstring (wide string) that holds characters that take more than
   1 byte to represent, such as those from international character sets. */
// To define a wstring, you have to include the "L" identifier at the front, like this:

std::wstring wstring = L"wstring";

// Each character has the type "wchar_t".

// Things to remember:
// 1. Strings are NOT primitive data types, they are OBJECTS.
// 2. Copying a std::string is expensive, so avoid this as much as possible.
// 3. Avoid passing std::string by value, as this makes a copy.
// 4. If possible, avoid creating short-lived std::string objects.

/******************
    STRING VIEW
******************/

// Whenever a string is passed by value into a function, an expensive copy of the string is made.
/* Using string_view as a parameter instead allows the function to read (or view) the value of a string
   WITHOUT copying it, thus making your code more optimized. */
// In summary, use string_view when you need a read-only string.
/* Another perk of string_view is that it can be initialized with a C string, a regular string, or another
   string_view. */

// Here is a good analogy to better understand string vs. string_view:

/* Say you've decided that you're going to paint a picture of a bicycle. But you don't have a bicycle!
   What are you to do? Well, you could go to the local cycle shop and buy one. You would own that bike.
   This has some benefits: you now have a bike that you can ride. You can guarantee the bike will always
   be available when you want it. You can decorate it, or move it. There are also some downsides to this
   choice. Bicycles are expensive. And if you buy one, you are now responsible for it. You have to
   periodically maintain it. And when you eventually decide you don't want it any more, you have to
   properly dispose of it. Ownership can be expensive. As an owner, it is your responsibility to acquire,
   manage, and properly dispose of the objects you own.
   
   On your way out of the house, you glance out your window front. You notice that your neighbor has
   parked their bike across from your window. You could just paint a picture of your neighbor's bike
   (as seen from your window) instead. There are lots of benefits to this choice. You save the expense
   of having to go acquire your own bike. You don't have to maintain it. Nor are you responsible for
   disposing of it. When you are done viewing, you can just shut your curtains and move on with your life.
   This ends your view of the object, but the object itself is not affected by this. There are also some
   potential downsides to this choice. You can't paint or customize your neighbors bike. And while you
   are viewing the bike, your neighbor may decide to change the way the bike looks, or move it out of
   your view altogether. You may end up with a view of something unexpected instead. Viewing is
   inexpensive. As a viewer, you have no responsibility for the objects you are viewing, but you also
   have no control over those objects. */

// std::string is an owner. std::string_view is a viewer.

/* You can tell your string_view to only view part of a string by using "remove_prefix()" or 
   "remove_suffix()", like this: */

std::string_view sv = "stringview";
sv.remove_prefix(6);    // Now sv = "view"

sv = "stringview";      // Reset the value of sv
sv.remove_suffix(4);    // Now sv = "string"

// Things to remember:
// 1. string_view is typically used for passing string function parameters and returning string literals.
// 2. When a string is destroyed, all views to that string are invalidated.
/* 3. Using an invalidated view(other than using assignment to revalidate the view) will cause undefined
      behavior. */
// 4. A string_view may or may not be null-terminated.

/******************************
    COMMON STRING FUNCTIONS
******************************/

std::string str = "Hello world";
std::string str2 = "Goodbye!";

// Use + or += to append to a string

void stringFunctions() {  // (Listed alphabetically)
    // Hover over a function to see what each parameter means

    stoi(str);          // Turn string into int
    stod(str);          // Turn string into float
    stof(str);          // Turn string into double
    std::to_string(1);  // Turn a different variable type into a string

    str[0];             // Return the character at specified index
    str.at(0);          // Same ^
    str.append("!");    // Add characters to back of string
    str.back();         // Return the last character
    str.c_str();        // Turn a std::string into a C-string
    str.capacity();     // Returns the number of characters that can be held without reallocation
    str.clear();        // Erase all characters
    str.empty();        // Returns "true" if string is empty
    str.erase(5, 6);    // Erase specific characters
    str.find("w");      // Returns the index (size_t) where the 1st occurance of the desired string is found
                        // Returns string::npos if unable to find string
    str.front();        // Returns the first character
    str.insert(6, "cruel ");    // Inserts text into a specified spot in the string
    str.length();       // Returns the number of characters in the string excluding the null terminator
    str.pop_back();     // Removes the last character
    str.push_back('!'); // Adds a character to the back of the string
    str.replace(0, 5, "Goodbye");   // Replaces a portion of the string with another string
    str.reserve(20);    // Sets a specified capacity for a string
    str.rfind("l");     // R stands for reverse. Finds the LAST occurance of the desired string.
    str.substr(0, 5);   // Returns a new string that is a specified portion of the last string
    str.swap(str2);     // Swaps the value of two strings
    swap(str, str2);    // Another way to swap strings

    // Note: There are more find() functions available that may be better suited for your needs.
}

#include "fakeheader.h"