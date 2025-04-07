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

/******************
    AGGREGATION
******************/

// To qualify as an aggregation, a whole object and its parts must have the following relationship:
// - The part (member) is part of the object (class)
// - The part (member) can (if desired) belong to more than one object (class) at a time
// - The part (member) does not have its existence managed by the object (class)
// - The part (member) does not know about the existence of the object (class)

/* Like a composition, an aggregation is still a part-whole relationship, where the parts are contained
   within the whole, and it is a unidirectional relationship. */
/* However, unlike a composition, parts can belong to more than one object at a time, and the whole object
   is not responsible for the existence and lifespan of the parts. */

// For example, consider the relationship between a person and their home address.
// In this example, for simplicity, we’ll say every person has an address.
/* That address can belong to more than one person at a time: for example, to both you and your roommate or
   you and your significant other. */
/* However, that address isn’t managed by the person; the address probably existed before the person got
   there, and will continue to exist after the person is gone. */
// Additionally, a person knows what address they have, but the address doesn’t know what people live there.

/* Because aggregations are similar to compositions in that they are both part-whole relationships, they are
   implemented almost identically. The difference between them is mostly semantic. */
// In aggregation, we add parts as member variables just like in a composition.
/* However, these member variables are typically either references or pointers that are used to point at
   objects that have been created outside the scope of the class. */
/* Consequently, an aggregation usually either takes the objects it is going to point to as constructor
   parameters, or it starts empty and the sub-objects are added later. */

/* Tip: Implement the simplest relationship type that meets the needs of your program, not what seems right
   in real-life. */
// However, composition is prefered since aggregation does not handle the deallocation of its parts.
// Also, it's worth noting that composition and aggregation can be mixed freely within the same class.

/* NOTE: Earlier, we discussed aggregate data types (such as structs and classes) as data types that group
   multiple variables together. */
// Despite the similarities in naming, aggregates and aggregation are different and should not be confused.

/******************
    ASSOCIATION
******************/

// To qualify as an association, an object and another object must have the following relationship:
// - The associated object (member) is otherwise unrelated to the object (class)
// - The associated object (member) can belong to more than one object (class) at a time
// - The associated object (member) does not have its existence managed by the object (class)
// - The associated object (member) may or may not know about the existence of the object (class)
/* In general, you should avoid bidirectional associations if a unidirectional one will do, as they add
   complexity and tend to be harder to write without making errors. */
// Most often, associations are implemented as pointers, where the object points at the associated object.

// The relationship between doctors and patients is a great example of an association.
// The doctor clearly has a relationship with his patients, but it’s not a part/whole relationship.
// A doctor can see many patients in a day, and a patient can see many doctors.
// Neither of the object’s lifespans are tied to the other.
// We can say that association models as “uses-a” relationship.
// The doctor “uses” the patient (to earn income) and the patient “uses” the doctor (for medical purposes).

/* Sometimes objects may have a relationship with other objects of the same type. This is called a reflexive
   association. */
// A good example is a university course and its prerequisites (which are also university courses).
// Consider the simple case where a course can only have one prerequisite. We can do something like this:

#include <string>
#include <string_view>
class Course
{
private:
    std::string name;
    const Course* prerequisite;
public:
    Course(std::string_view name = "None", const Course* prerequisite = nullptr) {
        this->name = name;
        this->prerequisite = prerequisite;
    }
};

// This can lead to a chain of associations (a course has a prerequisite, which has a prerequisite, etc.).

// In associations, it is not required to use pointers or references to directly link objects together.
// Any kind of data that allows you to link two objects together suffices.
// For example, let's say a Driver class has an association with a Car class.
// Instead of a pointer to the Car, the Driver can have the ID number of a car in integer form.
/* If space is limited and the number of unique objects is fairly low, referencing them by an 8-bit or
   16-bit integer can save lots of memory since a pointer can take up 4 or 8 bytes. */
// Here is a summary of what we discussed do far:

/*************************************************************************************************
                                          COMPOSITION      AGGREGATION      ASSOCIATION
                                         -----------------------------------------------------
                     Relationship Type:   whole/part       whole/part       otherwise unrelated
Members can belong to multiple classes:   No               Yes              Yes
   Members’ existence managed by class:   Yes              No               No
                        Directionality:   Unidirectional   Unidirectional   Uni or bidirectional
                     Relationship Verb:   Part-of          Has-a            Uses-a
*************************************************************************************************/

/*******************
    DEPENDENCIES
*******************/

// This is the simplest of the relationships we've learned so far.
/* In casual conversation, we use the term dependency to indicate that an object is reliant upon another
   object for a given task. */
// For example, if you break your foot, you are dependent on crutches to get around (but not otherwise).
// A dependency occurs when one object invokes another object’s functionality to accomplish something.
// A dependency is always a unidirectional relationship.
// A good example of a dependency is std::ostream.
// Classes use std::ostream to accomplish the task of printing something to the console, but not otherwise.

/************************
    CONTAINER CLASSES
************************/

/* In real life, we use containers all the time; your breakfast cereal comes in a box, the pages in your
   book come in a cover and binding, etc. */
// Without containers, it would be extremely inconvenient to work with many of these objects.
// A container class is a class designed to hold and organize multiple instances of another type.
// Container classes implement a "member-of" type of relationship.
// By far, the most commonly used container in programming is the array.
/* Although C++ has built-in array functionality, programmers will often use an array container class
   (std::array or std::vector) instead because of the additional benefits they provide. */
// Container classes typically implement a fairly standardized minimal set of functionality.
// Most well-defined containers will include functions that...
// - Create an empty container (via a constructor)
// - Insert a new object into the container
// - Remove an object from the container
// - Report the number of objects currently in the container
// - Empty the container of all objects
// - Provide access to the stored objects
// - Sort the elements (optional)

// Container classes generally come in two different varieties: value containers and reference containers.
/* Value containers are compositions that store copies of the objects that they are holding (and thus are
   responsible for creating and destroying those copies). */
/* Reference containers are aggregations that store pointers or references to other objects (and thus are
   not responsible for creation or destruction of those objects). */
// Also, in C++, containers typically only hold one type of data.