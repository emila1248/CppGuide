#include <iostream>  // Must include to write to the console
// "iostream" stands for "input/output stream".

/**************************
    PRINTING TO CONSOLE
**************************/

std::cout << "Hi" << std::endl;  // Prints "Hi" to console followed by a newline.

// std::cout is buffered, which works a lot like this:
/* Consider a rollercoaster at an amusement park. Passengers show up at some variable rate and get in
   line. Periodically, a train arrives and boards passengers up to maximum capacity. When the train is
   full, or when enough time has passed, the train departs with a batch of passengers. Any passengers
   unable to board the current train wait for the next one.*/
// This analogy is similar to how a buffer works in C++.
// Periodically the buffer is "flushed", which is synonymous with the train leaving.
/* This means that if your program crashes, aborts, or is paused before the buffer is flushed, any output
   still waiting in the buffer will not be displayed. */
   
// std::endl is often inefficient, as it flushes the buffer after outputting a newline.
// To print a newline without flushing the buffer, use the "\n" character instead, like this:

std::cout << "Newline\n";

// Prefer \n to std::endl when outputting to the console.

/*************************
    GETTING USER INPUT
*************************/

const char* input;
std::cin >> input;  // Sets the value of "input" to the characters the user typed

// For the >> operator, leading whitespace is excluded from the input.
/* It then takes as many consecutive characters as it can until it encounters either a whitespace
   character or a character that is not valid for the variable being extracted to. */
/* IMPORTANT: The remaining characters will be left in the buffer and will be extracted if std::cin is
   called again. */

// std::cin.eof() returns true if the entire input stream was extracted.
// std::cin.peek() returns the next character in the input stream without extracting it.

#include "fakeheader.h"