#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "shape.h"

#include <cmath>

// Triangle class inherits from Shape
class Triangle : public Shape {
 private:
    double side_;  // Side length of the triangle
    
 public:
    /* Default constructor, sets side to 1.0 */
    Triangle() : side_(1.0) {}

    /* Parameterized constructor, sets side to provided value */
    explicit Triangle(double in_side) : side_(in_side) {}

    /* Function to calculate height of the triangle */
    double Height() const { return (side_ * sqrt(3)) / 2; }

    // Getter for side
    double& Side() { return side_; }

    /* Override GetArea method from Shape, calculates area of triangle */
    double GetArea() const override { return (sqrt(3) / 4) * side_ * side_; }

    /* Override GetPerimeter method from Shape, calculates perimeter of triangle */
    double GetPerimeter() const override { return 3 * side_; }

    /* Override Print method from Shape, outputs triangle details */
    std::ostream& Print(std::ostream& os) const override {
        return os << "Triangle\nSide: " << side_ << "\nHeight: " << Height() 
                  << "\nArea: " << GetArea() << "\nPerimeter: " << GetPerimeter() << "\n";
    }

    /* Operator+ overload, adds sides of two triangles */
    Triangle operator+(const Triangle &rhs) const {
        return Triangle(side_ + rhs.side_);
    }

    /* Operator- overload, subtracts sides of two triangles */
    Triangle operator-(const Triangle &rhs) const {
        return Triangle(std::abs(side_ - rhs.side_));
    }

    /* Operator+= overload, adds side of rhs to this triangle */
    Triangle& operator+=(const Triangle &rhs) {
        side_ += rhs.side_;
        return *this;
    }

    /* Operator-= overload, subtracts side of rhs from this triangle */
    Triangle& operator-=(const Triangle &rhs) {
        side_ = std::abs(side_ - rhs.side_);
        return *this;
    }

    /* Operator< overload, compares areas of two triangles */
    bool operator<(const Triangle &rhs) const {
        return this->GetArea() < rhs.GetArea();
    }

    /* Operator== overload, compares areas of two triangles */
    bool operator==(const Triangle &rhs) const {
        return this->GetArea() == rhs.GetArea();
    }

    /* Operator> overload, compares areas of two triangles */
    bool operator>(const Triangle &rhs) const {
        return this->GetArea() > rhs.GetArea();
    }

    /* Friend function to overload the << operator for Triangle objects */
    friend std::ostream& operator<<(std::ostream &os, const Triangle &rhs) {
        return rhs.Print(os);
    }
};

#endif  // TRIANGLE_H_