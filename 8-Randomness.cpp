// Computers are generally incapable of generating truly random numbers (at least through software).
// Instead, modern programs typically simulate randomness using an algorithm.
/* For clarity's sake: an algorithm is a finite sequence of instructions that can be followed to solve some
   problem or produce some useful result. */
/* A pseudo-random number generator (PRNG) is an algorithm that generates a sequence of numbers whose
   properties simulate a sequence of random numbers.*/
// The value (or values) used to set the initial state of a PRNG is called a seed.
// If a PRNG is not provided with enough bits of quality seed data, we say that it is underseeded.
// An underseeded PRNG may produce results whose quality is compromised in some way.

// The randomization capabilities in C++ are accessible via the <random> header of the standard library.
// Within the random library, there are 6 PRNG families available for use (as of C++20).
// For most applications, the Mersenne Twister algorithm is fine, both in performance and quality.
// The biggest issue is that its results can be predicted after seeing 624 generated numbers.
// For a truly high-quality PRNG, you'll have to use a 3rd party library.

// Here are the 2 Mersenne Twister identifiers:
#include <random>

std::mt19937 mt1;       // Generates 32-bit unsigned integers (2^32)
std::mt19937_64 mt2;    // Generates 64-bit unsigned integers (2^64)

// Here's how to generate a random number:

int randomNum = mt1();

// Here's how to generate a random number from x to y:

int getRandNum(int x, int y) {
    return mt1() % (y - x + 1) + x;
}

/* Without providing a different seed each time the program is run, std::mt19937 will generate the same
   "random" sequence every time. */
// This may not be a problem, or may even be desired.
// To guarantee a new seed for each iteration, we can use the system clock.
// To get the current time, simply use std::time(), like this:

#include <ctime>
std::mt19937 mt3{std::time(0)};

/* To minimize the chance of two time values being identical if the program is run quickly in succession, we
   want to use some time measure that changes as quickly as possible. */
// For this, we’ll ask the clock how much time has passed since the earliest time it can measure.
/* This time is measured in “ticks”, which is a very small unit of time. (Usually nanoseconds, but could be
   milliseconds) */

#include <chrono>
std::mt19937 mt4{std::chrono::steady_clock::now().time_since_epoch().count()};

// Many PRNGs can be reseeded after the initial seeding.
/* Reseeding should generally be avoided unless you have a specific reason to do so, as it can cause the
   results to be less random or not random at all.*/
// Some PRNGs benefit from being “warmed up”, which is where the first N results from the PRNG are discarded.
// Typically a few hundred to a few thousand initial results are discarded.
// The seed_seq initialization used by std::mt19937 performs a warm up, so we don’t need to explicitly do so.

// What happens if we want to use a random number generator in multiple functions or files?
// The best way would be to have a single PRNG object that we can share and access anywhere.
// This can be done by defining an INLINE random number object in a "Random.h" header file.
// (Inline functions/variables are discussed in "Scope&Linkage")