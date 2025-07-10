/* Classes are almost identical to structs in that they allow us to group multiple variables together to
   represent something of interest. */
// They are both considered "class types", along with unions. (Which will be discussed in another chapter)
// One thing we didn't mention is that we can add functions to them instead of just raw data, like this:

#include <string>
#include <iostream>
class Person {  // Just replace "struct" with "class" to define a class
    std::string firstName;
    std::string lastName;
    int age;

    void sayName() { // <-- A function (also called a "method")
        std::cout << "I am " << firstName << " " << lastName << "\n";
    };
}; // NOTE: To make the return value const, place the const keyword right before the {}.

// Now a "person" can "say their name" by calling the function like this:

Person personObject; // <-- Creates a "Person" object
personObject.sayName();

// All (non-static) member functions must be called on an object of that class type. So this:

sayName();

// Is invalid, as there is no "Person" object to attach it to.
// Member functions can be overloaded. (Two functions with the same name, but different parameters.)
// Also note that member variables/functions can be defined in any order.
// This means that a variable/function can be referenced before it's even created.
// So what order should you put them in? Either private to public or public to private (discussed next).

/************************
    ACCESS SPECIFIERS
************************/

// Each member of a class has a property called an access level that determines who can access it.
// C++ has three different access levels: public, private, and protected.
// Protected has to do with inheritance, which will be talked about later.

// Public members do not have any restrictions on how they can be accessed.
// This means you can access them in the main() function and any other code file.
// Private members can only be accessed by other members of the same class.
// This means that they can only be accessed within the code file they are defined in.
// This is useful to guarantee that no data members can be changed from another code file.
// A good rule of thumb is to make all members as private as they need to be.

// Structs are public by default, and classes are private by default.
// If you want to change the access specifier for any data members, use a class, not a struct.
// You can do this by using access specifier keywords, like so:

class Person2 {
public:  // Anything following this specifier is public
    std::string firstName;
    std::string lastName;
    
    void sayName() { // <-- A function (also called a "method")
        std::cout << "I am " << firstName << " " << lastName << "\n";
    };
private:  // Anything following this specifier is private
    int age;
};


// So, what are the fundamental differences between a class and a struct?
// A class defaults its members to private, whereas a struct defaults its members to public.
// That's it. Like actually, that's it.
// So how do you know which one to use when?
// Well here's a general rule of thumb: Use a struct when all of the following are true:

// 1. You have a simple collection of data that doesn’t benefit from restricting access.
// 2. You have no class invariants, setup needs, or cleanup needs.

/**********************
    GETTERS/SETTERS
**********************/

/* An access function is a public member function whose job is to retrieve or change the value of a private
   member variable. */
// A short name for these are "getters" and "setters"; one gets a value, and the other sets it.
// They look like this:

int getAge() { return age; }
void setAge(int age) { this->age = age; }

// There's a new keyword in the setter: "this"
/* "this" is a const pointer that holds the address of the current implicit object (the object the member
   function will be called on). */
// This can be useful when a parameter has the same name as a data member.
// In the example above, "this.age" means the OBJECT'S age, and "age" means the PARAMETER "age".
// You may be wondering why "this" is pointer and not a reference.
// That's because references didn't exist when the "this" keyword was added to C++.
// Otherwise, "this" would undoubtedly be a reference.

// While you can name your getter/setter age() and age(int) respectively, it is not recommended.
// Naming the getter without the prefix is considered acceptable, but not the setter.
// Since the setter can change data, you want to make it explicit that this is what you're doing.
// But why even make members private if you're going to access them anyway? Good question :)

/**********************************
    REASONS FOR PRIVATE MEMBERS
**********************************/

/* One simple reason to have getters/setters is so you can return values by reference if they are expensive
   to copy. */
// Data hiding is also beneficial for maintaining class invariants.
/* Class invariants are conditions that must be true throughout the lifetime of an object in order for the
   object to stay in a valid state. */
// For example, an object could have a data member that you don't want exceeding a certain number.
// The other benefits of data hiding need a little more explaining:

/* In modern life, we have access to many mechanical or electronic devices. You turn your TV on/off with a
   remote, you turn on your lights by flipping a switch, etc. All of these devices have something in common:
   They provide a simple user interface that allows you to perform key actions. The specifics of how these
   devices actually operate is hidden away from you. This is similar to how access functions allow you to
   interact with objects. */
// The way users access and modify objects is called its interface.
// The actual code/data members attached to the object is called its implementation.
/* Data hiding (or data abstraction) is the technique used to enforce the separation of interface and
   implementation */
// This is done by 1: ensuring that data members are private.
// And 2: ensuring that member functions are public.
// This only applies to classes. Structs should be entirely public.

/*******************
    CONSTRUCTORS
*******************/

/* When a class type is an aggregate, we can use aggregate initialization to initialize the class type
   directly, like we do with structs. */
// With aggregate initialization, (curly brackets) members are initialized in the order they are defined.
// To initialize a non-aggretate class-type object, we need a constructor.

// A constructor is a MEMBER FUNCTION that is called after a non-aggregate class type object is created.
/* When the object is defined, the compiler looks for an accessible constructor that is a match for the
   initialization values provided by the caller, if any. */
/* If an accessible matching constructor is found, memory for the object is allocated and the constructor
   function is called. */
// If no accessible matching constructor is found, a compilation error will be generated.
// Besides this, constructors generally perform two functions:
// 1. They typically perform initialization of any member variables
// 2. They may perform other setup functions via statements in the body of the constructor.

/* Note that aggregates are not allowed to have constructors. So if you add a constructor to an aggregate,
   it is no longer considered an aggregate. */

// Unlike normal member functions, constructors have specific rules for how they must be named:
/* Constructors must have the same name as the class with the same capitalization. (For template classes,
   this name excludes the template parameters.) */
// Constructors have no return type, not even void.
// Also, because constructors are typically part of the interface for your class, they are usually public.

// Here is an example of a constructor, along with an example of giving data members default values:

class Person3 {
private:
    std::string firstName = "Jane";  // Default value
    std::string lastName = "Doe";  // Default value
    int age;
public:
    // The following is the constructor:
    Person3(std::string firstName, std::string lastName, int age) {
        this->firstName = firstName;
        this->lastName = lastName;
        this->age = age;
    }
};

// These are the ways you can call the constructor function:
Person3 charles("Charles", "Charleston", 20);   // direct initialization
Person3 david{"David", "Davidson", 20};         // direct list initialization
Person3 erick = {"Erick", "Erickson", 20};      // copy list initialization

// Use whichever one you want.
// Constructors will also perform implicit conversions, like so:
Person3 frank("Frank", "Frankson", true);  // "true" implicitly converts to 1

// A default constructor is a constructor that take in no values.
/* If no default constructor is provided by the programmer, the compiler will generate one called an
   "implicit default constructor" so that our object can be instantiated. */
// We can make a constructor equivalent to the implicit one by using the "default" keyword:

Person3() = default;  // You would define this inside of the class

// Here are cases where the default constructor will be called:

Person3 gib;        // default initialization
Person3 harry{};    // value initialization

// Use whichever one you want.
// This is useful to include when you've given all data members default values.
/* The default constructor will allow you to create an object where all the data members are set to their
   default values. */
/* But let's say you want to have a "Person" constructor that requires the user to provide a firstName and
   lastName, and optionally an age. You would do so like this: */

Person3(std::string firstName, std::string lastName, int age = 0)
    : firstName(firstName), lastName(lastName), age(age) {}

// Or like this:

Person3(std::string firstName, std::string lastName, int age = 0) {
    this->firstName = firstName;
    this->lastName = lastName;
    this->age = age;
};

// Prefer the first one. Think of it like this:
// First method: “Build the box with exactly the right parts from the start.”
// Second method: “Build the box with default parts, then rip them out and replace them.”

/* Giving "age" a default value allows you to essentially combine two constructors into one: A constructor
   that take a firstName, lastName, and age... and a constructor that takes a firstName and lastName. */
// This is why data members that MUST be initialized should be defined first.

// We can also use templates with classes just like we used with structs.
// Here's what a templated class could look like:

// In "Pair.h":
template <typename T>
class Pair
{
private:
    T first{};
    T second{};
public:
    Pair<T>(T first, T second) { // Note that the constructor doesn't NEED the <T> suffix
        this->first = first;
        this->second = second;
    }

    bool isEqual(Pair<T>& pair);
};

// Then, we would define the "isEqual" function in the source file, like this:

// In "Pair.cpp"
#include "Pair.h"

template <typename T> // Note that we need another template declaration
bool Pair<T>::isEqual(Pair<T>& pair) {
    return this->first == pair.first && this->second == pair.second;
}

// learncpp says that templated member functions should be defined in the header file, but idk why tbh.

/***************************
    THE COPY CONSTRUCTOR
***************************/

// A copy constructor is used to initialize an object with an existing object of the same type.
// After the copy constructor executes, the newly created object should be a copy of the first object.
// For example, the copy constructor is called when you pass a class-type object by value.
// If you don't provide a copy constructor, C++ will create an implicit one for you.
// We can also explicitly define our own copy constructor, like this:

Person3(Person3& person) {
    this->firstName = person.firstName;
    this->lastName = person.lastName;
    this->age = person.age;
}

// Or like this:

Person3(const Person3& person) = default;

// Here are cases where the copy constructor will be called:

Person3 charlesTwin = charles;  // copy initialization
Person3 davidsTwin(david);      // direct initialization
Person3 ericksTwin{erick};      // direct list initialization
Person3 franksTwin = {frank};   // copy list initialization

// Use whichever one you want.
// A copy constructor should NOT do anything other than copy an object.
// This is because the compiler may optimize the copy constructor out in cases where copying in unnecessary.
// It is advised to use the implicit copy constructor unless you have a specific reason to create your own.

// If you do not want your class-type to be copyable, you can use the "delete" keyword, like this:

Person3(const Person3& person) = delete;

// NOTE: The rule of three is a well known C++ principle that states:
/* If a class requires a user-defined copy constructor, destructor, or copy assignment operator, then it
   probably requires all three. */

/*********************************
    USING CLASSES ACROSS FILES
*********************************/

/* As classes get longer and more complicated, having all the member function defined inside the class can
   make it harder to work with. */
/* To help this, C++ allows us to separate the “declaration” part of the class from the “implementation” part
   by defining member functions outside of the class definition. */
// The only difference is that we must prefix the member function names with the name of the class type.
// Here is an example of a class within a header file and source file:

// (in MyClass.h)
class MyClass {
private:
    int x;
    int y;
public:
    MyClass(int x, int y) {
        this->x = x; this->y = y;
    }

    int x() { return x; } // Getters/setters are usually defined in the header since they are short functions
    int y() { return y; }
    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }

    int getGreater(); // Forward declarations
    int getLesser();
};

// (in MyClass.cpp)
#include "MyClass.h"

// These don't account for cases where x and y are equal, but that's ok, this is for demonstration purposes.
int MyClass::getGreater() {
    return x > y ? x : y;
};

int MyClass::getLesser() {
    return x < y ? x : y;
};

// Types (this includes classes) are exempt from the one-definition rule.
// Otherwise, you would not be able to include your classes in multiple source files.
// Also, member functions defined inside the class definition are implicitly inline.
// This is why you can define it again in the class's source file.
// THOSE functions are not inline, but can be made inline by using the keyword.

/******************
    DESTRUCTORS
******************/

// The destructor function gets called any time an object of that class type is destroyed.
// This allows for any necessary cleanup before the object gets destroyed.
// The destructor must have the same name as the class, preceded by a tilde, like this:

~MyClass() { // (should be defined under "public:")
    // cleanup code
}

// It cannot take arguments and cannot have a return type.
// Generally, you should not call a destructor explicitly, as it will be called automatically when needed.
// Destructors may safely call other member functions since the object isn’t destroyed until it executes.

/*********************
    STATIC KEYWORD
*********************/

// Static member variables are shared by all objects of the class and are not associated with class objects.
/* Although you can access static members through objects of the class, static members exist even if no
   objects of the class have been instantiated. */
/* This is because they are created at the start of the program and destroyed at the end of the program.
/* Because static members exists independently of any class objects, they can be accessed directly (if they
   are public) using the class name and the scope resolution operator (::).
// This is the recommended way to access static member variables.

/* When we declare a static member variable inside of a class type, we’re telling the compiler about the
   existence of a static member variable, but not actually defining it. */
// This is because they are essentially global variables, which must be defined in the global scope.
/* To define a static member variable inside the class definition, we must use the inline or constexpr
   keyword to get around the one definition rule for global variables. */
// The constexpr keyword works because constexpr variables are implicitly inline.
// Static member variables are also the only variables that can have the "auto" keyword.

// Member functions can also be static.
/* Because static member functions are not associated with any object, they can be called directly by using
   the class name and the scope resolution operator (::). */
// Static member functions cannot access non-static member variables, unless they are passed as a parameter.
// Static member functions defined in a header file should also be made inline or constexpr.

/*****************
    FRIENDSHIP
*****************/

/* A "friend" in C++ is a class or function that has been granted full access to the private and protected
   members of another class. */
/* Friendship is always granted by the class whose members will be accessed, not by the class or function
   desiring access. */
// Here is an example of a class declaring a non-member function a friend:

#include <iostream>
class Friendship {
private:
    int level = 0;
public:
    Friendship(int level) {
        this->level = level;
    }
    friend void print (Friendship& f);
};

void print(Friendship& f) { // A friend function of "Friendship" class.
    std::cout << "Friendship level: " << f.level;
}

// Now the print function can access private members of a "Friendship" object being passed as a parameter.
// Friend non-member functions can also be defined inside the class granting the friendship.
// Defining a friend function inside of a class makes it look like a member function, but this is not true.
// It is instead treated as a non-member function, as if it had been defined outside the class.
/* This may seem useless, but there are cases where you might prefer a friend function over a member function,
   like in the following example. */
// Also note that functions can be friends of multiple classes at once, like this:

class Humidity; // Forward declaration needed for line 410

class Temperature {
private:
    int temp;
public:
    Temperature(int temp) {
        this->temp = temp;
    }
    friend void printWeather(Temperature &t, Humidity& h);
};

class Humidity {
private:
    int humid;
public:
    Humidity(int humid) {
        this->humid = humid;
    }
    friend void printWeather(Temperature &t, Humidity& h);
};

void printWeather(Temperature &t, Humidity& h) {
    std::cout << "Temperate & humidity: " << t.temp << ", " << h.humid;
}

/* The printWeather() function operates on both a Temperature and Humidity, so it wouldn't make sense for it
   to be a member of either one. */
// Although friend functions serve their purposes, prefer not to use them if not necessary.
// You can also make an entire class a friend, like this:

class Class1 {
    friend class Class2;
};
class Class2 {

};

// Now Class2 can access the private members of Class1, but NOT vice versa.
// For both classes to access each other, each would have to declare the other a friend.
/* Class friendship is not transitive. If class A is a friend of B, and B is a friend of C, that does not
   mean A is a friend of C. */
// Nor is friendship inherited. If class A makes B a friend, classes derived from B are not friends of A.
// A friend class declaration acts as a forward declaration for the class being friended.
// Friend classes do not have access to the "this" pointer of the other class.