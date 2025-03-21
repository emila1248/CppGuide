// Prior to compilation, each code .cpp file goes through a preprocessing phase.
// In this phase, the preprocessor makes various changes to the text of the code file.
/* The preprocessor does not actually modify the original code files in any way. All changes made by
   the preprocessor happen either temporarily in-memory or using temporary files.*/
// One thing the preprocessor does is strips out comments and makes each code file end in a newline.
// When the preprocessor has finished processing a code file, the result is called a translation unit.
/* An important thing the preprocessor does is process directives, which are preceded by a '#' and end
   with a newline (not a semicolon). */

/*************
    MACROS
*************/

// The #define directive can be used to create a macro.
// In C++, a macro is a rule that defines how input text is converted into replacement output text.
// By convention, macro names are typically all uppercase, separated by underscores.
// There are two basic types of macros: object-like macros and function-like macros.

// Function-like macros act like functions, and serve a similar purpose.
/* Their use is generally considered unsafe, and almost anything they can do can be done by a normal
   function. */

// Object-like macros can be defined in one of two ways:

#define IDENTIFIER substitution_text
#define IDENTIFIER


// With substitution text
// ------------------------
/* A marco with substitution text tells the preprocessor to replace all further occurrences of the
   identifier with the substitution text. */
// For example:

#define SUPERCAL "Supercalafragilisticexpialadocious"
std::cout << (SUPERCAL);

/* Object-like macros with substitution text are now mostly seen in legacy code, and it is recommended
   to avoid them whenever possible. (Idk why honestly) */


// Without substitution text
// ---------------------------
// Macros without substitution text replace all further occurrences of the identifier with nothing.
// Macros of this form are generally considered acceptable to use.
// These macros are very useful when used with a conditional compilation directive.

// NOTE: The preprocessor doesn’t understand C++ concepts like functions.
/* So if you place a directive inside of a function, it will apply to the entire translation unit.
   instead of only within that function's scope. */

/******************************
    CONDITIONAL COMPILATION
******************************/

// This type of directive allows you to specify under what conditions something will or won’t compile.
// The most used ones are #ifdef, #ifndef, #elif, and #endif.
// #ifdef means "if defined", #ifndef means "if not defined", and #elif means "else if".
// Here is an example of all four being used:

#define PRINT_HELLO

#ifdef PRINT_HELLO
    std::cout << "Hello\n"; // will be compiled since PRINT_HELLO is defined
#elif PRINT_BYE
    std::cout << "Bye\n"; // will be excluded since PRINT_BYE is not defined
#endif
#ifndef BE_POLITE
    std::cout << "Fuck you\n"; // will be compiled since BE_POLITE is not defined
#endif

// You can also use the "#if 0" directive to quickly "disable" preprocessor directives, like this:

#if 0
    /*
    Multiple lines of code
    */
#endif

// You can use "#if 1" to reverse it.

/**************
    INCLUDE
**************/

// #include directives are where header files come into play.
/* When you #include a header file, (.h) the preprocessor replaces the #include directive with the
   the of that file. */
// Basically just a copy-and-paste.
// This is useful for forward declarations, which is what a header file is used for 99% of the time.
/* Header files are often paired with source (.cpp) files, with the header file providing forward
   declarations for things (like functions) defined in the corresponding source file. */
// Corresponding header and source files should have the same base name.
// Also, header files should be #included in their respective source file.
// Do NOT #include .cpp files.

// To use certain things from the C++ Standard Library, you have to include the correct header file.
// For example, to print messages to the console using "std::cout", you need this header file:

#include <iostream>

/* When including header files that are part of the C++ language, surround them in angled brackets
   < > like what's done above. */
/* When including header files that you've written yourself, surround them in quotes and add the
   ".h" extension, like so: */

#include "myHeaderFile.h"

/* If the header file is in a different directory (folder) than the file you're including it in, you'll
   have to tell the preprocessor where to find it by including it's relative path, like this: */
// NOTE: A file's relative path refers to its location relative to the current directory.

#include "pathToFile/file.h"
// Looks for the folder "pathToFile" in the current directory, then goes into it to find "file.h".

#include "../path/file.h"
// The ".." means "escape the current directory", AKA "look one folder up from this one".

/* The downside of this approach is that if you ever update your directory structure, your code won’t
   work anymore.*/
/* A better method is to tell your compiler/IDE that you have a bunch of header files in some other
   location, so that it will look there when it can’t find them in the current directory. */
// This can usually be done by setting an "include path" or "search directory" in your project settings.
// For instructions, just search "how to set include path for (insert IDE)".

// Header files can also include other header files.
// In that case, you’ll get any header files that are included by the one you're explicitly including.
// Those additional header files are sometimes called transitive includes.
// It's best not to rely on transitive includes and explicitly include each header file you're using.
/* This may result in the same header file being included more than once, which is what header guards
   are for. */

// This is a common way you'll see a header guard written:

#ifndef FILE_H
#define FILE_H

// Code goes here

#endif

/* You can use any unique identifier for a header guard, but the best convention is to use the full file
   name in all caps, with underscores for spaces/punctuation. (like "_H" used for ".h") */

// Modern compilers support a simpler alternative using "#pragma once" as a header guard, like this:

#pragma once
// Code here

/* Because #pragma once is not defined by the C++ standard, it is possible that some compilers may not
   implement it. */
// For this reason, some development houses (such as Google) recommend using traditional header guards.
/* However, support for #pragma once is fairly ubiquitous at this point, and if you wish to use #pragma
   once instead, that is generally accepted in modern C++. */