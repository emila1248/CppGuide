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
   deallocate that pointer when the class object went out of scope. */
// There is one problem though, and that is the assignment operator.
// If we create a smart pointer, then create another one assigned to that pointer, like this:

SmartPointer ptr1 = new SomeClass();
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
