#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "shape.h"

#include <cmath>

class Circle : public Shape {
 protected:
    double radius;

 public:
    Circle() : radius(1.0) {}
    Circle(double in_radius) : radius(in_radius) {}

    double& Radius() { return radius; }

    double GetArea() const override {
        return 3.14 * radius * radius;
    }

    double GetPerimeter() const override {
        return 2 * 3.14 * radius;
    }

    std::ostream& Print(std::ostream& os) const override {
        return os << "Circle\nRadius: " << radius << "\nArea: " << GetArea()
                            << "\nPerimeter: " << GetPerimeter() << "\n";
    }

    // Operator overloads
    Circle operator+(const Circle& rhs) const {
        return Circle(radius + rhs.radius);
    }

    Circle operator-(const Circle& rhs) const {
        return Circle(std::abs(radius - rhs.radius));
    }

    Circle& operator+=(const Circle& rhs) {
        radius += rhs.radius;
        return *this;
    }

    Circle& operator-=(const Circle& rhs) {
        radius = std::abs(radius - rhs.radius);
        return *this;
    }

    bool operator<(const Circle& rhs) const {
        return this->GetArea() < rhs.GetArea();
    }

    bool operator==(const Circle& rhs) const {
        return this->GetArea() == rhs.GetArea();
    }

    bool operator>(const Circle& rhs) const {
        return this->GetArea() > rhs.GetArea();
    }

    friend std::ostream& operator<<(std::ostream& os, const Circle& rhs) {
        return rhs.Print(os);
    }
};

#endif  // CIRCLE_H_