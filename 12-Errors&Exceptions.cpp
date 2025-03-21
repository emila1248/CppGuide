// When an error occurs, an exception is “thrown”.
/* If the current function does not “catch” the error, the caller of the function has a chance to catch
   the error. */
// If the caller does not catch the error, the caller’s caller has a chance to catch the error, etc.
// The error moves up the call stack until it's caught and handled or until main() fails to handle it.

// When testing/debugging your program, you can write to the console with std::cout or std::cerr.
/* The main difference is that std::cout is buffered, which means that it may not get executed if your
   program ends abruptly. */
// std::cerr is unbuffered, which means that anything you send to it will output immediately.
/* As a rule of thumb, use std::cout for normal user-facing error messages, and std::cerr for
   status and diagnostic information that probably isn't as interesting for normal users. */

// An assert statement looks like this:
#include <cassert> // <-- Must include
assert (x > 0);

// If the expression in the parentheses evaluates to true, the statement does nothing.
/* If it evaluates to false, an error message is displayed and std::abort is called. */
/* This error message typically contains the expression that failed as text, along with the name of the
   code file and the line number of the assertion. */

// C++ also has "static_assert", which is an assertion that's checked at compile-time.
// Unlike assert, static_assert is a keyword, so no header needs to be included in order to use it.
// You can write one like this:

static_assert(condition, diagnostic_message);

// The compiler checks if the condition is true, and if not, prints the diagnostic message.
// Because static_assert is evaluated by the compiler, the condition must be a constant expression.
// Favor static_assert over assert() whenever possible.

/****************************
    THROW, TRY, AND CATCH
****************************/

// A throw statement is used to signal that an exception or error case has occurred.
// Signaling that an exception has occurred is also commonly called raising an exception.
// You can throw any type of value, like this:

int value;

throw value;
throw -1;
throw "Error"

// Another way to handle errors is with a "try-catch" block.
// The try block acts as an observer, looking for any exceptions that are thrown within the try block.
// The catch block tells the program how to handle the exception.
// Try blocks and catch blocks work together.
/* A try block detects any exceptions that are thrown by statements within the try block, and routes
  them to a catch block with a matching type for handling. */
/* A try block must have at least one catch block immediately following it, but may have multiple catch
   blocks listed in sequence.*/
// After the matching catch block executes, execution then resumes as normal.

try {
    // Code that may cause an error
    throw -1;
}
catch (double) {
    std::cerr << "We caught an exception of type double\n";
}
catch (int x) {
    std::cerr << "We caught an int exception with value: " << x << '\n';
}

/* Catch parameters work just like function parameters, with the parameter being available within the
   subsequent catch block. */
// If the parameter is not going to be used in the catch block, the variable name can be omitted.
/* If a function call is in the try block and that function throws and error, the following catch
   block will handle it. */
// If you want to catch all exception types, use ... as a parameter, like this:

catch (...) { }

// Catch-all blocks are often left empty.
// This tells the program to disregard any exceptions and move on with the code.

// NOTE: C++ will not perform implicit conversions or promotions when matching exceptions types.
// However, casts from a derived class to one of its parent classes will be performed.

#include "fakeheader.h"