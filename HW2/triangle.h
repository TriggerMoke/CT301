#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "shape.h"
#include <cmath>
#include <iomanip>


class Triangle : public Shape {
    double side;

public:
    Triangle() : side(1.0) {}
    Triangle(double inSide) : side(inSide) {}

    double Height() const { return (side * sqrt(3)) / 2; }
    double& Side() { return side; }

    double GetArea() const override { return (sqrt(3) / 4) * side * side; }
    double GetPerimeter() const override { return 3 * side; }
    std::ostream& Print(std::ostream& os) const override {
        return os << "Triangle\nSide: " << side << "\nHeight: " << Height() 
                  << "\nArea: " << GetArea() << "\nPerimeter: " << GetPerimeter() << "\n";
    }

    // Operator overloads
    Triangle operator+(const Triangle &rhs) const {
        return Triangle(side + rhs.side);
    }
    Triangle operator-(const Triangle &rhs) const {
        return Triangle(std::abs(side - rhs.side));
    }
    Triangle& operator+=(const Triangle &rhs) {
        side += rhs.side;
        return *this;
    }
    Triangle& operator-=(const Triangle &rhs) {
        side = std::abs(side - rhs.side);
        return *this;
    }
    bool operator<(const Triangle &rhs) const {
        return this->GetArea() < rhs.GetArea();
    }
    bool operator==(const Triangle &rhs) const {
        return this->GetArea() == rhs.GetArea();
    }
    bool operator>(const Triangle &rhs) const {
        return this->GetArea() > rhs.GetArea();
    }
    friend std::ostream& operator<<(std::ostream &os, const Triangle &rhs) {
        return rhs.Print(os);
    }
};

#endif // TRIANGLE_H
