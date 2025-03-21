// Fundamental types are defined as part of the C++ language and are available for immediate use.
/* To store more complicated data, we can make our own types called user-defined types. (Or
   program-defined types) */
// All user-defined types must be fully defined before use. No forward declarations.
// These types come in two categories: Enumerated types and class types.
// NOTE: It's best to start your user-defined type with a capital letter.

/* An enumeration (enum) is a compound data type whose values are restricted to a set of named
   symbolic constants (enumerators) that evaluate to integers. */
// C++ supports two kinds of enumerations: scoped and unscoped.

/***************
    UNSCOPED
***************/

// Unscoped enums are defined like this:

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

// By default, the first value = 0, then each subsequent value = the previous value + 1.
// To start at a value other than 0, you can put (= x) at the end of the first value, like this:

enum Direction2 {
    UP2 = -1,
    DOWN2,
    LEFT2,
    RIGHT2
};
// Now up = -1, down = 0, left = 1, and right = 2

/* NOTE: Although not necessary, it's best to have the value that best equates to the "default"
   value of the enum equal to 0. */

/* Unscoped enums are named such because they put their enumerator names into the same scope as
   the enumeration definition itself. */
// This means that an enum name can’t be used in multiple enumerations within the same scope.
// Enums can also be defined in a function or in a class.
// Enum values are inexpensive to copy, so passing them by value is fine.

// Enumerated types will implicitly convert to an integral value.
// The exact type of integral value the enum will convert to is called its underlying type.
/* The C++ standard does not specify which type should be used as the underlying type, but most
   compilers will use int. */
// You can explicitly declare an underlying type like this:

#include <cstdint>
enum Enum : std::int8_t {

};

/* C++ does not provide a way to convert an enum value to a string, so here is an example of a
   function you can write to do that. */

#include <string_view>
std::string_view directionToString(Direction d) {
    switch (d) {
        case UP: return "Up";
        case DOWN: return "Down";
        case LEFT: return "Left";
        case RIGHT: return "Right";
        default: return "???";
    }
}
// NOTE: Since string literals exist for the entire program, it is ok to return a string_view.

/*************
    SCOPED
*************/

// Scoped enumerations work similarly to unscoped enumerations with two primary differences:
// 1. They won’t implicitly convert to integers.
/* 2. the enumerators are only placed into the scope region of the enumeration, not into the
      scope region where the enumeration is defined. (In other words, scoped enumerations act
      like a namespace for their enumerators) */
// To make a scoped enumeration, we use the keywords "enum class", like this:

enum class ScopedDirection {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

// Now, instead of this...
Direction up = UP;

// You must do this...
auto down = ScopedDirection::DOWN;  // auto keyword not necessary, just requires less typing

// To convert a scoped enum to an integral value, you can cast it as such, like this:
int left = (int)ScopedDirection::LEFT;

// NOTE: If using C++23, it is better to use std::to_underlying() instead.
// However you must #include <utility> first.

/* The lack of implicit conversion to integers can sometimes be a pain point, so a useful hack
   is to overload the unary operator + to perform this conversion. */
// That would look something like this:

int right = +ScopedDirection::RIGHT;

// Operator overloading is discussed in another section.

// In C++ 20, you can use the "using" keyword with enums just like you can with namespaces.