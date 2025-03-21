/************
	SCOPE
************/

// A BLOCK (or a compound statement) is a group of statetements that is treated by the compiler as one.
// Blocks are represented with curly brackets, like this --> { }
// A block within another block is called a nested block.
// C++ supports a nesting level of 256. (don't EVER nest that far)

// A LOCAL variable is a variable that is defined INSIDE of a block.
// A GLOBAL variable is a variable that is defined OUTSIDE of a block.
// Local variables get deleted when their block ends.
// Global variables get deleted when the program ends.

// The SCOPE of a variable refers to where it can be seen and used within the source code.
// Local variables can only be used within their block, and any block nested inside their block.
// Global variables can be used anywhere within the file they are created in.
// The best practice is to keep the scope of a variable as limited as possible.
// Two variables within the same scope cannot have the same name. This is called a naming collision.
// One way to resolve this is with a NAMESPACE.

// NOTE FOR LOCAL VARIABLES:
// --------------------------
/* If you don't want a local variable to get deleted after it's creation, you can put the "static" keyword
   in front of it. */
/* For example, if you create a static local variable inside of a function, it will remember it's value when
   the function is called again. */
// You still can't directly access it from outside of it's scope.
// The "static" keyword has multiple meanings when used in different contexts. This is just one of them.

/*****************
	NAMESPACES
*****************/

// The syntax for a namespace is as such:

namespace myNamespace {
	void myFunction() {};
}

// A namespace must be defined in the global scope or in another namespace.
// Historically, namespaces have not been capitalized. But ignore the haters, you just do you <3
// Any variables in a namespace are part of the global scope.
// To access something in a namespace, use the scope resolution operator (::) like this:

myNamespace::myFunction();

// Some new terminology:
// A QUALIFIED name is a name that includes an associated scope, usually with the "::" operator.
// An UNQUALIFIED name is a name that does not include a scope qualifier.

/* As you might have realized, things like std::cout and std::string are part of a namespace called the
   standard (std) namespace. */
// You can also use the :: operator WITHOUT putting a namespace in front of it, like this:

::print();

// This tells the compiler to look for the function/variable in the GLOBAL namespace.
/* This is useful if you have a function in your namespace with the same name as a function in the global
   namespace. */
// You can also nest namespaces.

/* It is okay to put the same namespace in different header files, then include BOTH header files in one
   source file. */
// The compiler will not treat this as an attempt to create the same namespace twice.

// You can also create namespace aliases to save you time when writing code.
/* For example, if you're using a nested namespace like space1::space2, you can create an "alias" so you
   don't have to write that namespace over and over again, like this: */

namespace space1 {
	namespace space2 {
		void function() {};
	}
}
namespace Active = space1::space2;

Active::function();	// As opposed to "space1::space2::function()"

// THE "USING" KEYWORD
// ---------------------
// The "using" keyword allows you to use unqualified names instead of qualified names when writing code.
// For example, the line "using std::cout" allows you to just write "cout" instead of "std::cout" like this:

#include <iostream>
using std::cout; // Considered a using-declaration

cout << "Hello";

// You can also use the "using" keyword for an entire namespaces, like this:

using namespace std; // Considered a using-directive

int userInput;
cin >> userInput;

// The using declaration/directive is active from the point of it's declaration to the end of it's scope.
// Never put the "using" keyword in header files.
// Also avoid putting using-directives in the global namespace, as it can not be "canceled" once declared.
// Using-declarations are a lot safer.

/**************
	LINKAGE
**************/

// An identifier"s linkage is whether or not other declarations of that name refer to the same object.
/* Local variables have no linkage, while global variables (and functions) can have either external or
   internal linkage. */

// Internal
// ---------
/* An identifier with internal linkage can be seen within a single source file, but it is not accessible
   from other source files. */
/* This means that if two source files have identically named identifiers with internal linkage, those
   identifiers will be treated as independent. */
// These identifiers are not exposed to the linker.
// To make a non-constant global variable internal, use the static keyword, as such:

static int internalVar = 0;	// Constants are internal/static by default

/* Note: The "static" keyword is an example of a storage class specifier, which sets the name's linkage and
   storage duration. */
// The most commonly used specifiers are "static", "extern", and "mutable".

// Functions can also be static. They are external by default, so you must declare them as static.

// External
// ---------
/* An identifier with external linkage can be seen and used both from the file in which it is defined,
   and from other code files via a forward declaration. */
// These identifiers are exposed to the linker.
// Functions and global variables have external linkage by default.
// To make a constant global variable external, use the "extern" keyword, as such:

extern constexpr int externalVar = 1;

/* To access an external variable from another source file, you must include a forward declaration for
   that identifier. */
// This means that in some cases, the extern keyword means "give this variable external linkage".
/* In other cases, the extern keyword means "this is a forward declaration for an external variable that
   is defined somewhere else". */

/* NOTE: Constexpr variables can be given external linkage via the extern keyword, but they CANNOT be
   forward declared as constexpr. Forward declare them as const instead. */

// Unlike variables, functions don't need the extern keyword.
/* The compiler is able to tell whether you're defining a function or making a forward declaration based
   on whether or not you supply a function body. */

// TIP: Avoid non-constant external global variables!
/* This is because they can be changed by ANY function that is called, and there is no easy way for the
   programmer to know that this has happened. */

/*************************
	THE INLINE KEYWORD
*************************/

// Inline variables and functions should only be used in header files.
/* Marking an identifier as inline means that it can be defined in more than one file, as long as the
   definitions are the same. */
// This is very useful when you want to define (NOT just initialize) a function in a header file.
/* Since header files are basically copy-pasted into other source files, that means your function will be
   defined in more than one place. That is what the "inline" keyword is for. */
/* If you don't use the inline keyword, the linker will throw an error for multiple definitions of the
   same identifier. */
// If you're familiar with structs and classes, all functions within those are inline by default.
// Here is the inline keyword in use:

inline int inlineVar = 2;
void inline inlineFunc() {}

#include "fakeheader.h"