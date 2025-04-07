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
class Shape {  // The parent class
public:  // (making the members public for simplicity purposes)
    std::string color;
    bool isCurved;

    Shape(std::string color = "None", bool isCurved = false) {
        this->color = color;
        this->isCurved = isCurved;
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