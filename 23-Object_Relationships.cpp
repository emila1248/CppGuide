/* There are many different kinds of relationships two objects may have in real-life, and we use specific
   “relation type” words to describe these relationships. */
/* For example: a square “is-a” shape. A car “has-a” gas pedal. A programmer “uses-a” keyboard. A baby
   “depends-on” a parent. A student is a “member-of” a class. And your brain is a “part-of” you. */
// All of these relation types have useful analogies in C++.
// We'll discuss “part-of”, “has-a”, “uses-a”, “depends-on”, and “member-of” here.
// "is-a" is-a bit more complicated and will be discusses later.

/*************************
    OBJECT COMPOSITION
*************************/

// In real-life, complex objects are often built from smaller, simpler objects.
// This process of building complex objects from simpler ones is called object composition.
// Broadly speaking, object composition models a “has-a” relationship between two objects.
// A car “has-a” transmission, your computer “has-a” CPU, you “have-a” heart, etc.
// The complex object is sometimes called the whole, or the parent.
// The simpler object is often called the part, child, or component.

/* When we build classes with data members, we’re essentially constructing a complex object from simpler
   parts, which is object composition. */
// For this reason, structs and classes are sometimes referred to as composite types.
// There are two basic subtypes of object composition: composition and aggregation.
/* A note on terminology: the term “composition” is often used to refer to both composition and aggregation,
   not just to the composition subtype. */
/* These notes will use the term “object composition” when referring to both, and “composition” when
   referring specifically to the composition subtype. */

/******************
    COMPOSITION
******************/

// To qualify as a composition, an object and a part must have the following relationship:
// - The part (member) is part of the object (class)
// - The part (member) can only belong to one object (class) at a time
// - The part (member) has its existence managed by the object (class)
// - The part (member) does not know about the existence of the object (class)

// In a composition relationship, the object is responsible for the existence of the parts.
/* Most often, this means that the part is created when the object is created and destroyed when the object
   is destroyed. */
/* But more broadly, it means that the object manages the part’s lifetime in such a way that the user of the
   object doesn't need to get involved. */
/* For example, when a body is created, the heart is created too. When a person’s body is destroyed, their
   heart is destroyed too. */
// Because of this, composition is sometimes called a “death relationship”.
// And finally, the part doesn’t know about the existence of the whole.
// Your heart operates blissfully unaware that it is part of a larger structure.
// We call this a unidirectional relationship; the body knows about the heart, but not the other way around.
/* Note that composition has nothing to say about the transferability of parts; a heart can be transplanted
   from one body to another. */
/* However, even after being transplanted, it still meets the requirements for a composition and can only be
   part of the recipient object unless transferred again. */

// Compositions are one of the easiest relationship types to implement in C++.
// They are typically created as structs or classes with normal data members.
// Compositions that need dynamic allocation/deallocation may be implemented using pointer data members.
/* In this case, the composition class should be responsible for doing all necessary memory management
   itself (not the user of the class). */
// In general, if you CAN design a class using composition, you SHOULD design a class using composition.
// Classes designed using composition are straightforward, flexible, and robust.

/* Although most compositions directly create their parts when the composition is created, there are some
   variations of composition that bend these rules a bit. For example... */
// A composition may defer creation of some parts until they are needed.
// A composition may opt to use a part that has been given to it as input rather than create it itself.
/* A composition may delegate destruction of its parts to some other object. (ex., a garbage collection
   routine) */
// The key point is that the composition should manage its parts without the user having to do anything.

// Tip: A good rule of thumb is that each class should be built to accomplish a single task.
/* That task should either be the storage and manipulation of some kind of data, OR the coordination of its
   members. Ideally not both. */