#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include <cmath>

#include "shape.h"

class Rectangle : public Shape {
 protected:
    double width_;
    double height_;

 public:
    Rectangle() : width_(1.0), height_(1.0) {}
    Rectangle(double width, double height) : width_(width), height_(height) {}

    double& width() { return width_; }
    double& height() { return height_; }

    double width() const { return width_; }
    double height() const { return height_; }

    double GetArea() const override {
        return width_ * height_;
    }

    double GetPerimeter() const override {
        return 2 * (width_ + height_);
    }

    std::ostream& Print(std::ostream& os) const override {
        return os << "Rectangle\nHeight: " << height_ << "\nWidth: " << width_
                            << "\nArea: " << GetArea() << "\nPerimeter: " << GetPerimeter() << "\n";
    }

    Rectangle operator+(const Rectangle& rhs) const {
        return Rectangle(width_ + rhs.width_, height_ + rhs.height_);
    }

    Rectangle operator-(const Rectangle& rhs) const {
        return Rectangle(std::abs(width_ - rhs.width_), std::abs(height_ - rhs.height_));
    }

    Rectangle& operator+=(const Rectangle& rhs) {
        width_ += rhs.width_;
        height_ += rhs.height_;
        return *this;
    }

    Rectangle& operator-=(const Rectangle& rhs) {
        width_ = std::abs(width_ - rhs.width_);
        height_ = std::abs(height_ - rhs.height_);
        return *this;
    }

    bool operator<(const Rectangle& rhs) const {
        return this->GetArea() < rhs.GetArea();
    }

    bool operator==(const Rectangle& rhs) const {
        return this->GetArea() == rhs.GetArea();
    }

    bool operator>(const Rectangle& rhs) const {
        return this->GetArea() > rhs.GetArea();
    }

    friend std::ostream& operator<<(std::ostream& os, const Rectangle& rhs) {
        return rhs.Print(os);
    }
};

#endif  // RECTANGLE_H_