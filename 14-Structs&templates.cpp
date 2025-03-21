/**************
    STRUCTS
**************/

// A struct is a way we can group multiple variables together to represent something of interest.
// They can be defined like this:

struct Person {
    const char* firstName;
    const char* lastName;
    int age;
};

// The pieces of data inside a struct are called data members or member variables.
// Structs are aggregate, which means a type that can contain multiple data members.
// Here's how to define a struct and access variables inside of one:

Person abby {};  // Creates unititialed object
Person ben { "Ben", "Benson", 32 };  // Cretaes initialized object
abby.age = 24;  // Sets abby.age equal to 24
int bensAge = ben.age;  // Sets bensAge to the value of ben.age

// Just like in function parameters, you can give member variables default values.

struct Fraction {
    int numerator = 1;
    int denominator = 1;
};

Fraction twoThirds { 2, 3 };
Fraction four { 4 };  // Denominator defaults to 1 since numerator is the first parameter

// It's best to provide default values for all members of a struct.

// You can use the . operator on a struct object to access values directly, such as abby.age
// This also works on references to struct objects.
// To access members of a POINTER to a struct object, you must use the -> operator instead.

// Sometimes the size of a struct is not equal to the size of the member types added together.
// For performance reasons, the compiler will sometimes add gaps into structures called padding.
// You can minimize padding by defining your members in decreasing order of size.

/****************
    TEMPLATES
****************/

/* In C++, the template system was designed to simplify the process of creating functions (or structs)
   that are able to work with different data types. */
/* Instead of creating a bunch of mostly-identical functions/structs for each set of different data
   types, we can create a single template instead. */
/* We start by creating a "template parameter declaration", which defines any template parameters that
   will be subsequently used, like this: */

template <typename T, typename U>

// Then we can use these "types" in our struct, like this:

struct Pair {
    T first;
    U second;
};

// Now we can create instances of this struct using any types we want, like this:

Pair<short, int> pair1 {1, 2};
Pair<float, double> pair2 {1.5f, 2.5};

/* NOTE: Working with pairs of data is so common that the C++ standard library contains a data type
   called std::pair, which makes use of a template. */
// You must include the <utility> header to use it.

// Templates also work with function definitions, like this:

template <typename T, typename U>
auto func(T param1, U param2) {
    return param1 + param2;
}
/* NOTE: Every time you create a templated struct/function, you need a new template definition
   statement, even if the type names are the same. */

/* Template definitions are typically defined in header files so they can be included in other
   files that need them. */
// Template definitions are exempt from the one-definition rule.
// You can also use aliases for templates, like this:

using Ints = Pair<int, int>;
Ints twos {2, 2};