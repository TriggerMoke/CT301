#ifndef SQUARE_H_
#define SQUARE_H_

#include "rectangle.h"

#include <cmath>
#include <iostream>

// Square class inherits from Rectangle
class Square : public Rectangle {
 public:
  /* Default constructor, sets width and height to 1.0 */
  Square() : Rectangle(1.0, 1.0) {}

  /* Parameterized constructor, sets width and height to provided value */
  explicit Square(double width) : Rectangle(width, width) {}

  // Deleting the height method as square's height is always equal to its width
  double& height() = delete;

  /* Override GetArea method from Shape, calculates area of square */
  double GetArea() const override {
    return width_ * width_;
  }

  /* Override GetPerimeter method from Shape, calculates perimeter of square */
  double GetPerimeter() const override {
    return 4 * width_;
  }

  /* Override Print method from Shape, outputs square details */
  std::ostream& Print(std::ostream& os) const override {
    return os << "Square\nWidth: " << width_ << "\nArea: " << GetArea() 
          << "\nPerimeter: " << GetPerimeter() << "\n";
  }

  /* Operator+ overload, adds widths of two squares */
  Square operator+(const Square& rhs) const {
    double new_width = width_ + rhs.width_;
    return Square(new_width);
  }

  /* Operator- overload, subtracts widths of two squares */
  Square operator-(const Square& rhs) const {
    double new_width = std::abs(width_ - rhs.width_);
    return Square(new_width);
  }

  /* Operator+= overload, adds width of rhs to this square */
  Square& operator+=(const Square& rhs) {
    width_ += rhs.width_;
    height_ = width_;  // Ensure it remains a square
    return *this;
  }

  /* Operator-= overload, subtracts width of rhs from this square */
  Square& operator-=(const Square& rhs) {
    width_ = std::abs(width_ - rhs.width_);
    height_ = width_;  // Ensure it remains a square
    return *this;
  }
};

#endif  // SQUARE_H_