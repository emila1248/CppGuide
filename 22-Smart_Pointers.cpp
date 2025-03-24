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