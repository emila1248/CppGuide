/* Inheritance involves creating new objects by directly acquiring the attributes and behaviors of other
   objects, and then extending or specializing them. */
/* Like how a circle and a square both inherit the attributes of a shape, but expand upon it in their own
   way. */
// Inheritance represents an “is-a” relationship between two objects.
// In C++, inheritance takes place between classes.
/* The class being inherited from is called the parent class, base class, or superclass, and the class doing
   the inheriting is called the child class, derived class, or subclass. */
// Here is an example:

#include <string>
#include <string_view>
class Shape {  // The parent class
public:  // (making the members public for simplicity purposes)
    std::string color;

    Shape(std::string_view color = "None") {
        this->color = color;
    }
};

class Circle : public Shape {  // The child class
public:
    int radius;

    Circle(int radius = 1) {
        this->radius = radius;
    }
};

/* Using the "public" keyword here means that this is an example of public inheritance, which will be
   elaborated on later. */
// When Circle inherits from Shape, Circle acquires the member functions and variables from Shape.
// It’s also possible to inherit from a class that is itself derived from another class.

/* Because Circle inherits functions and variables from Shape, you may assume that the members of Shape are
   copied into Circle, but that is not the case. */
// Instead, we can consider Circle as a two part class: one part Circle, and one part Shape.
// When C++ constructs derived objects, it does so in phases.
// First, the most-base class (at the top of the inheritance tree) is constructed.
// Then each child class is constructed in order, up until the most-child class.
// Here is essentially the step-by-step process that happens when instantiating a derived class:

// 1. Memory for derived is set aside (enough for both the Base and Derived portions)
// 2. The appropriate Derived constructor is called
/* 3. The Base object is constructed first using the appropriate Base constructor. If no base constructor is
      specified, the default constructor will be used. */
// 4. The member initializer list initializes variables.
// 5. The body of the constructor executes.
// 6. Control is returned to the caller.

/* Back to our example: one of the shortcomings of our Circle class is that there is no way to initialize
   "color" or "isCurved" when we create a Circle object. */
/* However, C++ prevents classes from initializing inherited member variables in the member initializer list
   of a constructor. */
// Why? The answer has to do with const and reference variables. Look it up if you want I guess.
// So how do we properly initialize inherited member variables when creating a derived class object?
// Fortunately, C++ gives us the ability to explicitly choose which Base class constructor will be called.
// This will allow us to initialize all member variables, like this:

//                                                    vv Calls Shape constructor with value "color"
Circle(std::string_view color = "None", int radius = 1) : Shape(color) {
    this->radius = radius;
}

// Now we can make our member variables private like they're supposed to be.

/************************
    PROTECTED KEYWORD
************************/

// C++ has a third access specifier that is only useful in an inheritance context.
/* The "protected" access specifier allows only the class the member belongs to, friends, and derived
   classes to access the member. */

class MyClass {
public:
    int int1; // Can be accessed by anybody
protected:
    int int2; // Can be accessed by MyClass members, friends, and derived classes
private:
    int int3; // Can only be accessed by MyClass members and friends (not derived classes)
};

// With a protected attribute in a base class, derived classes can access that member directly.
/* This means that if you later change anything about that protected attribute, you’ll probably need to
   change both the base class AND all of the derived classes. */
/* Therefore, using the protected access specifier is most useful when you (or your team) are going to be
   the ones deriving from your own classes, and the number of derived classes is reasonable. */
/* Using private members is good for insulating the public or derived classes from implementation changes,
   and for ensuring invariants are maintained properly. */
/* However, it also means your class may need a larger public/protected interface to support all of the
   functions that the public/derived classes need for operation. */
/* In general, it’s better to make your members private if you can, and only use protected when derived
   classes are planned and the cost to build and maintain an interface is too high. */

// When making a derived class, you have three different ways for it to inherit from another class:
// To choose one, simply specify which type of access you want, like this:

class Triangle : public Shape {};
class Square : protected Shape {};
class Rectangle : private Shape {};
// If you don't choose an inheritance type, it will default to private.

// This gives us 9 combinations: 3 member access specifiers, and 3 inheritance types.
/* So what’s the difference? In a nutshell, when members are inherited, the access specifier for an
   inherited member may be changed in the derived class depending on the type of inheritance used. */
/* For example, members that were public or protected in the base class may change their access specifiers
   in the derived class. */

// Public inheritance is by far the most commonly used type of inheritance.
// In fact, very rarely will you see or use the other types of inheritance.
/* When you inherit a base class publicly, inherited public members stay public, and inherited protected
   members stay protected. Inherited private members stay inaccessible. */
// Protected inheritance is so rarely used that I'm not gonna waste time on it.
// Private inheritance means everything gets inherited privately, including public and protected members.
/* Private inheritance can be useful when the derived class has no obvious relationship to the base class,
   but uses the base class for implementation internally. */

/***************************
    OVERRIDING FUNCTIONS
***************************/

// By default, derived classes inherit all of the behaviors defined in a base class (obviously).
/* When a member function is called on a derived class object, the compiler first looks to see if any
   function with that name exists in the derived class. */
/* If so, all overloaded functions with that name are considered, and the function overload resolution
   process is used to determine whether there is a best match. */
// If not, the compiler walks up the inheritance chain, checking each parent class in the same way.
/* To modify the way a function defined in a base class works in the derived class, simply redefine the
   function in the derived class. */
/* Note that when you redefine a function in the derived class, the function does not inherit the access
   specifier of the function with the same name in the base class. */
/* Therefore, a function that is defined as private in the base class can be redefined as public in the
   derived class, or vice-versa. */
// Here is how you can do this:

class Base {
public:
    int publicInt;
    void publicFunc();
protected:
    int protectedInt;
    void protectedFunc();
};

class Derived : public Base {
public:
    using Base::protectedInt; // From protected to public
    using Base::protectedFunc;
private:
    using Base::publicInt; // From public to private
    using Base::publicFunc;
};

// You can also make a function uncallable by setting it to "delete", like this:

void publicFunc() = delete;

// What if you don't want to rewrite the function, but just add additional functionality?
// Inside the derived class function, simply call the base class function by ussing the :: operator.

class Base {
public:
    void doSomething() {};
};

class Derived : public Base {
    void doSomething() {
        Base::doSomething();
    };
};

/***************************
    MULTIPLE INHERITANCE
***************************/

// C++ provides the ability for a derived class to inherit members from more than one parent.
// The syntax is pretty simple:

class Teacher : public Person, public Employee {};

/* A mixin (also spelled “mix-in”) is a small class that can be inherited from in order to add properties
   to a class. */
// These classes are intended to be mixed into other classes, not instantiated on their own. For example:

class Button : public Box, public Label, public Tooltip {};

// Some programmers say that multiple inheritance in C++ should be avoided at all costs.
// learncpp recommends to avoid it unless alternative solutions lead to more complexity.

/************************
    VIRTUAL FUNCTIONS
************************/

// Let's say you have an array of type "Animal" filled with "Cat" and "Dog" objects.
// Each animal has a "speak()" function that prints the sound each animal makes to the console.
/* If you were to call speak() on a Cat in your Animal array, the compiler would call Animall::speak()
   instead of Cat::speak(). */
/* In order for the compiler to call the most derived version of your function, you must use the "virtual
   keyword in front of the function name. */

#include <iostream>
class Animal {
public:
    virtual void speak() { std::cout << "idk"; }; // Keyword added for base class...
};

class Cat : public Animal {
public:
    virtual void speak() { std::cout << "meow"; }; // And derived class.
};
// Now when you call "speak()" on a Cat object in your Animal array, it will print "meow".

/* You can also make a "pure" virtual function which simply acts as a placeholder in the base class to be
   overridden by the derived class, like this: */

virtual int pureVirtual() const = 0;

/* Note that any class with one or more pure virtual functions becomes an abstract base class, which means
   that it can not be instantiated. */

// So why not just make all functions virtual?
/* The answer is because it’s inefficient, since resolving a virtual function call takes longer than
   resolving a regular one. */
/* To make virtual functions work, the compiler has to allocate an extra pointer for each object of a class
   that has virtual functions. */
// This adds a lot of overhead to objects that otherwise have a small size.

/* A derived class virtual function is only considered an override if its signature and return types match
   exactly. */
// That can lead to issues, where a function that was intended to be an override actually isn’t.
/* To help address this, the override specifier can be applied to any virtual function to tell the compiler
   to enforce that the function is an override. */
/* If a function marked as override does not override a base class function (or is applied to a non-virtual
   function), the compiler will flag it as an error. */
// The override specifier is placed at the end of a member function declaration, right before the {}.
/* Because there is no performance penalty for using the override specifier, all virtual override functions
   should be tagged with it. */
/* Additionally, because the override specifier implies virtual, there’s no need to tag functions using the
   override specifier with the virtual keyword. */

// There may be cases where you don’t want someone to be able to override a virtual function.
// The "final" specifier can be used to tell the compiler to enforce this.
// The final specifier gets placed directly after the override specifier.

// NOTE: Always make your destructors virtual if you’re dealing with inheritance. Here's why:

Derived* derived { new Derived() };
Base* base { derived };
delete base;

// The last line of code only calls the Base destructor, but you'd want it to call both.
// And remember, you really only need a destructor if you're dealing with dynamic memory allocation.

/* Extra note: An interface class is a class that has no member variables, and all of the functions are pure
   virtual. */
/* Interfaces are useful when you want to define the functionality that derived classes must implement, but
   leave the details up to the derived class. */

/*********************
    OBJECT SLICING
*********************/