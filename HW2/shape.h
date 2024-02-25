// shape.h
#ifndef SHAPE_H
#define SHAPE_H

#include <iostream>

class Shape {
public:
    virtual ~Shape() = default;
    virtual double GetArea() const = 0;
    virtual double GetPerimeter() const = 0;
    virtual std::ostream& Print(std::ostream &os) const = 0;

    friend std::ostream &operator<<(std::ostream &os, const Shape &rhs);
};

#endif // SHAPE_H
