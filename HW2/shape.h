// Aidan Michalos
// aidanmih

#ifndef SHAPE_H_
#define SHAPE_H_

#include <iostream>

// Abstract base class for all shapes
class Shape {
 public:
    /* Virtual destructor, required for abstract classes */
    virtual ~Shape() = default;

    /* Pure virtual function for calculating area, to be implemented by classes
       that call upon this and the following virtual functions */
    virtual double GetArea() const = 0;

    /* virtual function for calculating perimeter */
    virtual double GetPerimeter() const = 0;

    /* virtual function for printing shape details */
    virtual std::ostream& Print(std::ostream& os) const = 0;

    /* Friend function to overload the << operator for Shape objects */
    friend std::ostream& operator<<(std::ostream& os, const Shape& rhs);
};

#endif  // SHAPE_H_