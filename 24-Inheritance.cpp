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