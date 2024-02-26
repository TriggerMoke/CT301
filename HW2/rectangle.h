#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include <cmath>
#include "shape.h"

// Rectangle class inherits from Shape
class Rectangle : public Shape {
 protected:
    double width_;  // Width of the rectangle
    double height_;  // Height of the rectangle

 public:
    /* Default constructor, sets width and height to 1.0 */
    Rectangle() : width_(1.0), height_(1.0) {}

    /* Parameterized constructor, sets width and height to provided values */
    Rectangle(double width, double height) : width_(width), height_(height) {}

    // Getter and setter for width
    double& width() { return width_; }
    double width() const { return width_; }

    // Getter and setter for height
    double& height() { return height_; }
    double height() const { return height_; }

    /* Override GetArea method from Shape, calculates area of rectangle */
    double GetArea() const override {
        return width_ * height_;
    }

    /* Override GetPerimeter method from Shape, calculates perimeter of rectangle */
    double GetPerimeter() const override {
        return 2 * (width_ + height_);
    }

    /* Override Print method from Shape, outputs rectangle details */
    std::ostream& Print(std::ostream& os) const override {
        return os << "Rectangle\nHeight: " << height_ << "\nWidth: " << width_
                            << "\nArea: " << GetArea() << "\nPerimeter: " << GetPerimeter() << "\n";
    }

    /* Operator+ overload, adds widths and heights of two rectangles */
    Rectangle operator+(const Rectangle& rhs) const {
        return Rectangle(width_ + rhs.width_, height_ + rhs.height_);
    }

    /* Operator- overload, subtracts widths and heights of two rectangles */
    Rectangle operator-(const Rectangle& rhs) const {
        return Rectangle(std::abs(width_ - rhs.width_), std::abs(height_ - rhs.height_));
    }

    /* Operator+= overload, adds width and height of rhs to this rectangle */
    Rectangle& operator+=(const Rectangle& rhs) {
        width_ += rhs.width_;
        height_ += rhs.height_;
        return *this;
    }

    /* Operator-= overload, subtracts width and height of rhs from this rectangle */
    Rectangle& operator-=(const Rectangle& rhs) {
        width_ = std::abs(width_ - rhs.width_);
        height_ = std::abs(height_ - rhs.height_);
        return *this;
    }

    /* Operator< overload, compares areas of two rectangles */
    bool operator<(const Rectangle& rhs) const {
        return this->GetArea() < rhs.GetArea();
    }

    /* Operator== overload, compares areas of two rectangles */
    bool operator==(const Rectangle& rhs) const {
        return this->GetArea() == rhs.GetArea();
    }

    /* Operator> overload, compares areas of two rectangles */
    bool operator>(const Rectangle& rhs) const {
        return this->GetArea() > rhs.GetArea();
    }

    /* Friend function to overload the << operator for Rectangle objects */
    friend std::ostream& operator<<(std::ostream& os, const Rectangle& rhs) {
        return rhs.Print(os);
    }
};

#endif  // RECTANGLE_H_