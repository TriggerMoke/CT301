#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "shape.h"

#include <cmath>

class Triangle : public Shape {
 public:
    Triangle() : side_(1.0) {}
    explicit Triangle(double in_side) : side_(in_side) {}

    double Height() const { return (side_ * sqrt(3)) / 2; }
    double& Side() { return side_; }

    double GetArea() const override { return (sqrt(3) / 4) * side_ * side_; }
    double GetPerimeter() const override { return 3 * side_; }
    std::ostream& Print(std::ostream& os) const override {
        return os << "Triangle\nSide: " << side_ << "\nHeight: " << Height() 
                 << "\nArea: " << GetArea() << "\nPerimeter: " << GetPerimeter() << "\n";
    }

    // Operator overloads
    Triangle operator+(const Triangle &rhs) const {
        return Triangle(side_ + rhs.side_);
    }
    Triangle operator-(const Triangle &rhs) const {
        return Triangle(std::abs(side_ - rhs.side_));
    }
    Triangle& operator+=(const Triangle &rhs) {
        side_ += rhs.side_;
        return *this;
    }
    Triangle& operator-=(const Triangle &rhs) {
        side_ = std::abs(side_ - rhs.side_);
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

 private:
    double side_;
};

#endif  // TRIANGLE_H_