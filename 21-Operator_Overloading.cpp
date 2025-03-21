/* In C++, operators are implemented as functions. By using function overloading on the operator functions,
   you can define your own versions of the operators. */
// When evaluating an expression containing an operator, the compiler uses the following rules:
// 1. If all the operands are fundamental types, the compiler will call a built-in routine if one exists.
/* 2. If any of the operands are program-defined types, (ex. one of your classes or an enum type) the
      compiler will use the function overload resolution algorithm, discussed later. */

// There are some limitations when it comes to operator overloading:
// Almost any existing operator in C++ can be overloaded.
/* The exceptions are: conditional (?:), sizeof, scope (::), member selector (.), pointer member selector
   (.*), typeid, and the casting operators. */
/* You can not create new operators or rename existing ones. For example, you could not create an operator
   ** to do exponents. */
/* At least one of the operands in an overloaded operator must be a user-defined type. (Standard library
   classes like std::string are considered to be user-defined as well) */
// It is not possible to change the number of operands an operator supports.
// Finally, all operators keep their default precedence and associativity.
// This is why it's best to keep the function of the operators as close to the original intent as possible.

/* There are three different ways to overload operators: the member function way, the friend function way,
   and the normal function way. */
// The friend function way works like this:

class Cents
{
private:
    int cents;
public:
    Cents(int cents) { this->cents = cents; }
    int getCents() { return cents; }

    friend Cents operator+(Cents& c1, Cents& c2); // Friend function declaration
};

Cents operator+(Cents& c1, Cents& c2) { // Friend function definition
    return Cents(c1.cents + c2.cents);
}

// The above example overloads the binary + operator.
// You can overload the other arithmetic operators in the same way by simply swapping out the symbols.
// Note that the operator+ function is defined OUTSIDE of the Cents class and is NOT a member function.

// You'll often want your overloaded operators to work with operands that are different types.
// For example, if we have Cents(4), we may want to add the integer 6 to make Cents(10).
/* Overloading binary operators for operands of different types requires two functions: One for x + y, and
   one for y + x. Here is an example: */

Cents operator+(Cents& c1, int c2) { // Must be declared a friend inside of "Cents" class
    return Cents(c1.cents + c2);
}
Cents operator+(int c1, Cents& c2) {
    return Cents(c1 + c2.cents);
}

// Arithmetic operators like + and - can be chained together more than once. (For example, 1 + 2 + 3 + 4)
// For that reason, it's important to remember which direction your operator evaluates in.
// The + operator evaluates from left to right.

/* Operator overloading the normal function way is the same as the friend function way, except we use access
   functions like this: */

Cents operator+(Cents& c1, Cents& c2) {
    return Cents(c1.getCents() + c2.getCents()); // We use "getCents()" to access cents value
}

/* You should prefer overloading operators as normal functions instead of friend functions if it’s possible
   to do so without adding any additional functions. */

// You can also overload operators through the use of member functions. When doing this, remember that...
// 1. The overloaded operator must be added as a member function of the left operand.
// 2. The left operand becomes the implicit *this object.
// 3. All other operands become function parameters.
// Here is an example:

class Cents
{
private:
    int cents;
public:
    Cents(int cents) { this->cents = cents; }
    int getCents() { return cents; }

    Cents operator-(); // Unary operator (only one operand)
};
// Returns a Cents object with the negated cents value of the operand
Cents Cents::operator-() {
    return Cents{-cents};
}

/* Note that not everything can be overloaded as a friend function, and not everything can be overloaded as
   a member function. */
// The former includes assignment (=), subscript ([]), function call (()), and member selection (->).
// The latter includes the << operator.

// So, when do we use a normal, friend, or member function overload?
// If you’re overloading a unary operator, prefer to do so as a member function.
/* When dealing with binary operators that don’t modify the left operand, the normal or friend function
   version is typically preferred because it works for all parameter types. */
/* When dealing with binary operators that do modify the left operand (ex. operator+=), the member function
   version is typically preferred. */
/* Because the rightmost operand becomes an explicit parameter, there’s no confusion over who is getting
   modified and who is getting evaluated. */

/********************
    I/O OPERATORS
********************/

// An overloaded operator function for << would look like this:

#include <iostream>
std::ostream& operator<< (std::ostream& out, Cents& c) {
    out << "I have " << c.getCents() << " cents\n";
    return out;
};

// std::cout is actually an object of type std::ostream.
// We need to return by reference here because std::ostream disallows being copied.

// Overloading the >> operator is a bit more complicated
// Here's a link explaining it because I don't feel like writing it all out:
// https://www.learncpp.com/cpp-tutorial/overloading-the-io-operators/

/****************
    ++ AND --
****************/

// There are two versions of the ++ and -- operators: a prefix and a postfix version.
// Overloading the prefix version is quite simple: (using the member function method)

Cents& Cents::operator++() {
    ++cents;
    return *this;
}

/* The overloaded ++ and -- operators return the current implicit object so multiple operators can be
   “chained” together. */

// So how do we differentiate the prefix and postfix versions of these operators to the compiler?
/* The C++ language specification has a special case for this: the compiler looks to see if the overloaded
   operator has an int parameter. */
// If it does, the operator is a postfix overload. Here's an example:

Cents Cents::operator--(int) {
    Cents temp{*this};
    --(*this);
    return temp;
}

// Note that the dummy parameter is not used in the function implementation, so it doesn't have a name.
// This tells the compiler to treat this variable as a placeholder
// Also note that the difference between the two types of overloads is the value they return.
// The prefix operators return the object AFTER it has been changed.
/* The postfix operators return the state of the object BEFORE it is changed, which is why we need to store
   its original state in a temporary variable. */

/*****************************
    THE SUBSCRIPT OPERATOR
*****************************/

// This operator must be overloaded as a member function.
// We expect the user to pass in an integer index, and we’ll return the value at that index as a result.
// Here is an example:

class FloatList
{
private:
    float list[10]{};
public:
    float& operator[] (int index) { return list[index]; }
};

// That's it.
/* However, if our list was const, we wouldn’t be able to call the non-const version of operator[] because
   it would allow us to potentially change the state of a const object. */
// All we need to do is define a non-const and a const version of operator[] separately.
// The const version would look like this:

const float& operator[] (int index) const { return list[index]; }

// Notice that the implementations for both the const and non-const functions are identical.
// This is fine in this case, since we only have one line of code.
// But what if the implementation of these operators was complex, requiring many statements?
/* The preferred solution is to implement the logic for the const version, and have the non-const version
   call the const function and use const_cast to remove the const. */
// It would look something like this:

#include <utility> // needed for std::as_const
class IntList
{
private:
    int list[10]{};
public:
    const int& operator[] (int index) const { return list[index]; }
    int& operator[] (int index) { const_cast<int&>(std::as_const(*this)[index]); }
};

// Normally using const_cast to remove const is something we want to avoid, but it’s fine for this case.
// Another thing we can do is make our overloaded operator check to ensure the index is within bounds.
/* Doing this with an assert statement will cause the program to terminate with an error message instead of
   possibly corrupting memory by letting it go unchecked. */
// You can also just use an if-statement and your favorite error handling method.

// Pointers to objects and the overloaded operator[] do not mix.
/* If you try to call operator[] on a pointer to an object, C++ will assume you’re trying to index an array
   of objects of that type. */
// The proper syntax would be to dereference the pointer first (making sure to use parentheses).

/******************
    PARENTHESES
******************/

/* The parenthesis operator allows you to vary the return type, and both the type and number of parameters
   it takes. */
// Also, remember that it must be implemented as a member function.
// Here's an example that allows us to easily index a 2-dimensional array:

class Matrix
{
private:
    double data[4][4]{};
public:
    double& operator()(int row, int col) { return data[row][col]; }
};

// Now we can make calls that look like this:

Matrix m{};
m(0, 1) = 1.5;

/*****************
    TYPE CASTS
*****************/

// User-defined conversions allow us to convert our class into another data type.
// Here's an example of converting our Cents class to a std::string and an int:

#include <string>
class Cents
{
private:
    int cents;
public:
    Cents(int cents) { this->cents = cents; }
    operator std::string() { return cents + " cents"; }
    operator int() { return cents; }
};

// Now we can do things like...

Cents five{5};
std::string fiveCents1 = static_cast<std::string>(five);
int fiveCents2 = (int)five;

/* We can use the "explicit" keyword before the "operator" keyword to make it so that we can only invoke
   conversions that can be called explicity (by using static_cast). */
// This is good when you want to disallow implicit conversions for your object.

/**************************
    ASSIGNMENT OPERATOR
**************************/

// The purpose of the copy constructor and the copy assignment operator are almost equivalent.
/* However, the copy constructor initializes new objects, whereas the assignment operator replaces the
   contents of existing objects. */
// Here is an example of an overloaded = operator:

class Cents
{
private:
    int cents;
public:
    Cents(int cents) { this->cents = cents; }
    Cents& operator= (Cents& c);
};

Cents& Cents::operator= (Cents& c) {
    this->cents = c.cents;
    return *this; // return the existing object so we can chain this operator
}

// One thing to watch out for is accidental self-assignment, which is when an object is assigned to itself.
// You only need to consider this when dealing with objects that dynamically allocate memory.
// This has to do with freeing memory and assigning that same (now "deleted") memory to the same object.
// You can implement a simple check to make sure this doesn't happen:

Cents& Cents::operator= (Cents& c) {
    // The check v
    if (this == &c) {
        return *this;
    }
    // remaining code
}

// NOTE:
// Making a copy of an object without allocating new memory is called a shallow copy.
/* For example, if you copy an object that has a pointer, and you only copy the pointer address and assign
   it to the new object, then you made a shallow copy. */
// This results in both objects having pointers that point to the same memory address.
/* If you create a new pointer with a new address, then copy the memory stored at the old address into the
   new address, then you made a deep copy. */
// A deep copy requires overloading the copy constructor and the assignment operator.
/* However, classes in the standard library that deal with dynamic memory (such as std::string and std::
   vector) already handle all of their memory management. */
/* This means that instead of doing your own memory management, you can just initialize or assign them like
   normal fundamental variables. */

#include "fakeheader.h"