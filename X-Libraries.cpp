// A library is just a collection of object files (compiled code/binary).
// There are two types of libraries: static and dynamic

/* STATIC libraries (AKA archives) consist of functions that are compiled and linked directly into your
   program. */
/* When you compile a program that uses a static library, all the functionality of the static library
   that your program uses becomes part of your executable. */
// Static libraries typically have a .lib extension.
// Properties:
/* - Because the library becomes part of your program, you ONLY have to distribute the executable in
     order for users to run your program. */
// - To update the library, the entire executable needs to be replaced.

/* DYNAMIC libraries (AKA shared libraries) consist of functions that are loaded into your application
   at run time. */
// When you compile a program that uses a dynamic library, it does not become part of your executable.
// Dynamic libraries typically have a .dll (dynamic link library) extension.
// Properties:
// - Many programs can share one copy.
// - The library can be updated without replacing all of the executables that use it.

/* When using a static library, you can tell the linker where to look for the files by inputting a path
   in the "link directories" setting. */