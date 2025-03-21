// On modern computer architectures, the smallest addressable unit of memory is a byte.
// Since all objects need to have unique memory addresses, this means objects must be at least one byte.
// For boolean values, this is a bit wasteful, since boolean types only have two states: true or false.
/* For the majority of cases this is fine, but it can be useful to “pack” 8 individual Boolean values into
   a single byte. */
// Modifying individual bits within an object is called bit manipulation.
// When individual bits of an object are used as Boolean values, the bits are called "bit flags".
// In computing, a flag is a value that signals when some condition exists in a program.

// To define a set of bit flags, you'd use an unsigned integer of the appropriate size, or std::bitset.
// Here is how to define a set of bit flags using std::bitset:

#include <bitset>
std::bitset<8> mybitset {0b00101100}; // "0b" prefix so compiler knows we're using binary

// Given a sequence of bits, we typically number the bits from right to left, starting with 0, like this:

// Example bitset: 0 0 1 0  1 1 0 0
//   Bit position: 7 6 5 4  3 2 1 0

// A bit holding a 0 value is said to be “false”, “off”, or “not set”.
// A bit holding a 1 value is said to be “true”, “on”, or “set”.
// When a bit is changed from 0 to 1 or 1 to 0, we say it has been “flipped” or “inverted”.

// std::bitset provides 4 key member functions that are useful for doing bit manipulation:
// test() - returns the value of the bit
// set() - turns a bit on (makes it a 1)
// reset() - turns a bit off (makes it a 0)
// flip() - flips a bit's value
// Here's an example of how to use some of these functions:

mybitset.set(7);
mybitset.flip(0);
int bitValue = mybitset.test(4);

// There are a few other member functions that are often useful:
// size() - returns the number of bits in the bitset
// count() - returns the number of bits that are set to true
// all() - returns a boolean indicating whether all bits are set to true
// any() - returns a boolean indicating whether any bits are set to true
// none() - returns a boolean indicating whether no bits are set to true

// Also, std::bitset is optimized for speed, not memory saving.
// A std::bitset<8> will typically use either 4 or 8 bytes of memory, even though it only needs one.
// Thus, std::bitset is most useful when we desire convenience, not memory saving.

/************************
    BITWISE OPERATORS
************************/

// C++ provides 6 bit manipulation operators, often called bitwise operators:
// (for the following list: x = a bitset, y = a different bitset, n = a number entered by the programmer)

// Left shift (x << n): The bits from x are shifted left by n positions; new bits are 0.
// Right shift (x >> n): The bits from x are shifted right by n positions; new bits are 0.
// Bitwise NOT (-x): Each bit from x is flipped.
// Bitwise AND (x & y): Each bit is set when both corresponding bits in x and y are 1.
// Bitwise OR (x | y): Each bit is set when either corresponding bit in x and y is 1.
// Bitwise XOR (x ^ y): Each bit is set when the corresponding bits in x and y are different.

// These operators do NOT modify their operands.
// If you want to modify the operand, similarly to algebraic operators, you can suffix "=", like this:

std::bitset<8> x {0b00101100};
std::bitset<8> y {0b11001011};

// Instead of...
x = x << 2;
x = x & y;

// Do...
x <<= 2;
x &= y;

/****************
    BIT MASKS
****************/

// In order to manipulate bits, we need some way to identify the specific bits we want to manipulate.
// The bitwise operators don’t know how to work with bit positions. Instead, they work with bit masks.
/* A bit mask is a predefined set of bits that is used to select which bits will be modified by subsequent
   operations. */

/* Consider a real-life case where you want to paint a window frame. If you’re not careful, you risk
   painting not only the frame, but also the glass itself. */
// You might buy some masking tape and apply it to the glass and any other parts you don’t want painted.
// In the end, only the non-masked parts get painted.
// This is essentially how a bit mask works.

// The simplest set of bit masks is to define one bit mask for each bit position.
// We use 0s to mask out the bits we don’t care about, and 1s to denote the bits we want modified.

#include <cstdint>
constexpr std::uint8_t mask0{ 0b0000'0001 }; // represents bit 0
constexpr std::uint8_t mask1{ 0b0000'0010 }; // represents bit 1
// etc.

// To be continued.

#include "fakeheader.h"