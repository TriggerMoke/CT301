#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "shape.h"

#include <cmath>

class Rectangle : public Shape {
 protected:
    double width;
    double height;

 public:
    Rectangle() : width(1.0), height(1.0) {}
    Rectangle(double in_width, double in_height) : width(in_width), height(in_height) {}


    // Need reference and const 
    double& Width() { return width; }
    double& Height() { return height; }

    double Width() const { return width; }
    double Height() const { return height; }

    double GetArea() const override {
        return width * height;
    }

    double GetPerimeter() const override {
        return 2 * (width + height);
    }

    std::ostream& Print(std::ostream& os) const override {
        return os << "Rectangle\nHeight: " << height << "\nWidth: " << width
                            << "\nArea: " << GetArea() << "\nPerimeter: " << GetPerimeter() << "\n";
    }

    // Operator overloads
    Rectangle operator+(const Rectangle& rhs) const {
        return Rectangle(width + rhs.width, height + rhs.height);
    }

    Rectangle operator-(const Rectangle& rhs) const {
        return Rectangle(std::abs(width - rhs.width), std::abs(height - rhs.height));
    }

    Rectangle& operator+=(const Rectangle& rhs) {
        width += rhs.width;
        height += rhs.height;
        return *this;
    }

    Rectangle& operator-=(const Rectangle& rhs) {
        width = std::abs(width - rhs.width);
        height = std::abs(height - rhs.height);
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