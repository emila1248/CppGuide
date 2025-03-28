class SomeClass {};

// Consider a function in which we dynamically allocate a value, like this:

void func() {
    SomeClass* ptr = new SomeClass();
    // do stuff with ptr here
    delete ptr;
}

// Although the above code is very straightforward, it’s fairly easy to forget to deallocate ptr.
// This can happen via an early return or if an exception is thrown that stops the function early.
// This kind of issue can occur since pointers don't have a way of cleaning up after themselves.
/* One way to fix this is to create a class that holds a pointer value, then deletes that value inside
   of its destructor. */
// This solution works since an object's destructor gets called when it's destroyed or goes out of scope.
/* Essentially, consider a class whose sole job is to hold and “own” a pointer passed to it, and then
   deallocate that pointer when the class object went out of scope, like this: */

template <typename T>
class SmartPointer {
	T* ptr;
public:
	// Pass in a pointer to "own" via the constructor
	SmartPointer(T* ptr=nullptr) {
        this->ptr = ptr;
	}
	// The destructor will make sure it gets deallocated
	~SmartPointer() {
		delete ptr;
	}
	// Overload dereference and operator-> so we can use SmartPointer like ptr.
	T& operator*() const { return *ptr; }
	T* operator->() const { return ptr; }
};

// There is one problem though, and that is the assignment operator.
// If we create a smart pointer, then create another one assigned to that pointer, like this:

SmartPointer ptr1( new SomeClass() );
SmartPointer ptr2 = ptr1;

// Both pointers are now pointing to the same set of data.
// When one goes out of scope, it will delete the data being pointed to.
/* When the other goes out of scope, it will try to delete the already deleted data, which leads to
   undefined behavior (or even a crash). */

// So how do we address this?
// One way is to explicitly define and delete the copy constructor and assignment operator.
// This is problematic because learncpp says so, so instead we can implement move semantics.
/* This means that instead of having our copy constructor and assignment operator copy the pointer, we
   transfer/move ownership of the pointer from the source to the destination object. */
// Click the link in line 2 to see an implementation of this.

// Anyways, C++98 attempted to create a standardized smart pointer called std::auto_ptr.
// However, std::auto_ptr has a number of problems that makes using it dangerous.
// Because of this, std::auto_ptr has been deprecated in C++11 and removed in C++17.
// In C++11, std::auto_ptr has been replaced by a bunch of other types of “move-aware” smart pointers:
// std::unique_ptr, std::weak_ptr, and std::shared_ptr.
// To discuss these, it's good to go over r-value references.

/* I was kinda lazy for this ^ section, so go here
   https://www.learncpp.com/cpp-tutorial/introduction-to-smart-pointers-move-semantics/
   for a more detailed explanation of everything. */

/************************
    RVALUE REFERENCES
************************/

// C++11 adds a new type of reference called an r-value reference.
// This is just a reference that is designed to be initialized with an r-value only.
/* While an l-value reference is created using a single ampersand, an r-value reference is created using
   a double ampersand, like this: */

int&& rRef = 5;

/* While it may seem weird to initialize an r-value reference with a literal and then be able to change
   that value, when initializing an r-value reference with a literal, a temporary object is constructed
   from the literal so that the reference is referencing a temporary object, not a literal value. */
// R-value references are more often used as function parameters.
/* This is most useful for function overloads where you want to have different behavior for l-value and
   r-value arguments. */

void func2(const int& lref) { // l-value arguments will select this function
	std::cout << "l-value reference to const: " << lref << '\n';
}

void func2(int&& rref) { // r-value arguments will select this function
	std::cout << "r-value reference: " << rref << '\n';
}

// This is an important part of move semantics which will be discussed soon.
// Also note that r-value references are l-values, and you should (almost) never return either of them.

/****************************************
    MOVE CONSTRUCTORS/MOVE ASSIGNMENT
****************************************/

// C++11 defines two new functions for move semantics: a move constructor and a move assignment operator.
// Defining a move constructor and move assignment works identically to their copy counterparts.
/* The only difference is that the move functions use non-const rvalue reference parameters and the copy
   functions take a (preferably const) l-value reference parameter. */
/* The example code for this is pretty long, so go here:
   https://www.learncpp.com/cpp-tutorial/move-constructors-and-move-assignment/
   to see it. It's the second code snippet. */

// Note that move functions should always leave both objects in a valid state.
// In the examples from learncpp, both the move functions set a.m_ptr to nullptr.
// This may seem extraneous, since a is a temporary r-value that will get destroyed anyway.
/* The reason we do it is beacause when a goes out of scope, the destructor for a will be called, and
   a.m_ptr will be deleted. */
/* If at that point, a.m_ptr is still pointing to the same object as m_ptr, then m_ptr will be left as a
   dangling pointer. */
// When the object containing m_ptr eventually gets used (or destroyed), we’ll get undefined behavior.
/* The point is, it's important to ensure the moved-from object is left in a valid state, so that it will
   destruct properly. */

// (This next part refers to line 82 in the 2nd learncpp example code linked above)
/* In the generateResource() function of the Auto_ptr4 example above, when variable res is returned by
   value, it is moved instead of copied, even though res is an l-value. */
/* The C++ specification has a special rule that says automatic objects returned from a function by value
   can be moved even if they are l-values. */
// This makes sense, since res was going to be destroyed at the end of the function anyway.
/* Although the compiler can move l-value return values, in some cases it may be able to do even better by
   simply eliding the copy altogether. */
// In such a case, neither the copy constructor nor move constructor would be called.

// If you want to disable copying altogether, you can set the copy functions as "delete", like so:

Auto_ptr(const Auto_ptr& a) = delete;
Auto_ptr& operator=(const Auto_ptr& a) = delete;

/* Sometimes you’ll find cases where you want to invoke move semantics, but the objects you have to work
   with are l-values. Take this function as an example: */

template <typename T>
void mySwapCopy(T& a, T& b)
{
	T temp{ a }; // invokes copy constructor
	a = b; // invokes copy assignment
	b = temp; // invokes copy assignment
}

// Passed in two objects of type T, this function swaps their values by making three copies.
// However, doing copies isn’t necessary here, as sll we’re trying to do is swap the values of a and b.
// The problem here is that parameters a and b are l-value references, not r-value references.
// C++11 lets us use std::move to cast an l-value into a type that will prefer being moved, not copied.
// Here’s the same program as above, but with std::move:

#include <utility> // Needed for std::move
template <typename T>
void mySwapMove(T& a, T& b)
{
	T tmp{ std::move(a) }; // invokes move constructor
	a = std::move(b); // invokes move assignment
	b = std::move(tmp); // invokes move assignment
}

// Keep in mind that moved-from objects will be in a valid, but possibly indeterminate state.
/* Because we can access these objects after their values have been moved, it's useful to know what value
   they are left with. */
// Some believee that objects that have been moved from should be reset back to a default/zero state.
// Others believe that we should do whatever is most convenient.

// std::move can also be useful when sorting an array of elements.
// Many sorting algorithms work by swapping pairs of elements, so std::move would be useful here.
// It can also be useful if we want to move the contents managed by one smart pointer to another.

/**********************
    UNIQUE POINTERS
**********************/

// std::unique_ptr is the C++11 replacement for std::auto_ptr.
// It should be used to manage any dynamically allocated object that is not shared by multiple objects.
// That is, it should completely own the object it manages, not share ownership with other classes.
// You can access std::unique_ptr in the <memory> header.
// Here is what one looks like:

#include <memory>
// NOTE: Always define smart pointers on the stack, since that guarantees it will go out of scope.
std::unique_ptr<SomeClass> uniquePtr( new SomeClass() );

/* Because std::unique_ptr is designed with move semantics in mind, copy initialization and copy assignment
   are disabled. */
// If you want to transfer the contents of std::unique_ptr, you must use move semantics.
// std::unique_ptr also has an overloaded operator* and operator->.
// Operator* returns a reference to the managed resource, and operator-> returns a pointer.
/* Before we use either of these, we should check whether the std::unique_ptr actually has a resource since
   it may not always be managing an object. */
/* Fortunately, std::unique_ptr has a cast to bool that returns true if it is managing a resource, which can
   be used like this: */

if (uniquePtr) {
    // Do something
};

// To get a raw pointer from a std::unique_ptr, you can use the get() member function, like this:

SomeClass* regularPtr = uniquePtr.get();

// Note that std::unique_ptr can be safely returned by value from a function.
// C++14 comes with an additional function named std::make_unique().
/* This constructs an object of the template type and initializes it with the arguments passed into the
   function, like this: */

class Fraction {
private:
	int num = 0;
	int den = 1;
public:
	Fraction(int num = 0, int den = 1) {
        this->num = num; this->den = den;
	}
};

auto frac = std::make_unique<Fraction>(3, 5);

// "frac" is now a unique pointer to a Fraction object.
// Use of std::make_unique() is optional, but is recommended over creating std::unique_ptr.
// This is mostly because it's simpler and requires less typing.
/* It also resolves an exception safety issue that can result from C++ leaving the order of evaluation for
   function arguments unspecified. */

// There are two easy ways to misuse std::unique_ptrs.
// The first is by letting multiple objects manage the same resource, like this:

SomeClass* x( new SomeClass() );
std::unique_ptr<SomeClass> x1(x);
std::unique_ptr<SomeClass> x2(x);

// The second is by manually deleting the resource out from underneath the std::unique_ptr, like this:

SomeClass* y( new SomeClass() );
std::unique_ptr<SomeClass> y1(y);
delete y;

// Note that std::make_unique() prevents both of the above cases from happening inadvertently.

/**********************
    SHARED POINTERS
**********************/

// std::shared_ptr is meant to solve the case where you need multiple smart pointers co-owning a resource.
// Internally, std::shared_ptr keeps track of how many std::shared_ptr are sharing the resource.
/* As long as at least one std::shared_ptr is pointing to the resource, the resource will not be
   deallocated, even if individual std::shared_ptrs are destroyed. */
/* As soon as the last std::shared_ptr managing the resource goes out of scope (or is reassigned to point at
   something else), the resource will be deallocated. */
// Like std::unique_ptr, std::shared_ptr lives in the <memory> header.
// Here is an example of a shared pointer:

SomeClass* a = new SomeClass{};

std::shared_ptr<SomeClass> aPtr1{ a };
std::shared_ptr<SomeClass> aPtr2{ aPtr1 };

// Note that we created a second shared pointer from the first shared pointer.
// This is important. Consider the following similar program:

SomeClass* b = new SomeClass{};

std::shared_ptr<SomeClass> bPtr1{ b };
std::shared_ptr<SomeClass> bPtr2{ b };

// The difference here is that we created two std::shared_ptr independently from each other.
// As a consequence, even though they’re both pointing to the same thing, they aren’t aware of each other.
// When bPtr2 goes out of scope, it thinks it’s the only owner of b, and deallocates it.
// When bPtr1 later goes out of the scope, it thinks the same thing, and tries to delete b again.
// In conclusion: if you need more than one std::shared_ptr to a given resource, copy an existing one.
/* Just like with std::unique_ptr, std::shared_ptr can be a null pointer, so check to make sure it is valid
   before using it. */

/* Much like std::make_unique() can be used to create a std::unique_ptr, std::make_shared() can(and should)
   be used to make a std::shared_ptr.*/
/* A std::unique_ptr can be converted into a std::shared_ptr via a special std::shared_ptr constructor that
   accepts a std::unique_ptr r-value. */
// The contents of the std::unique_ptr will be moved to the std::shared_ptr.
// However, std::shared_ptr can not be safely converted to a std::unique_ptr.

// In C++17 and earlier, std::shared_ptr does not have proper support for managing arrays.
// As of C++20, std::shared_ptr does have support for arrays.

/********************
    WEAK POINTERS
********************/

/* std::weak_ptr was designed to solve the “cyclical ownership” problem, where following a set of pointers
   results in going in a circle. */
// A std::weak_ptr can observe the same object as a std::shared_ptr, but it's not considered an owner.

/* Because std::weak_ptr won’t keep an owned resource alive, it’s possible for a std::weak_ptr to be left
   pointing to a resource that has been deallocated. */
/* However, because it has access to the reference count for an object, it can determine if it is pointing
   to a valid object or not. */
// The easiest way to test whether a std::weak_ptr is valid is to use the expired() member function.

#include "fakeheader"