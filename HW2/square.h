#ifndef SQUARE_H
#define SQUARE_H

#include "rectangle.h"
#include <cmath>


class Square : public Rectangle {
public:
    Square() : Rectangle(1.0, 1.0) {}
    Square(double inWidth) : Rectangle(inWidth, inWidth) {}

    // Deleting the Height method to prevent misuse
    double& Height() = delete;

    double GetArea() const override {
        return Rectangle::Width() * Rectangle::Width();
    }
    double GetPerimeter() const override {
        return 4 * Rectangle::Width();
    }
    std::ostream& Print(std::ostream& os) const override {
        return os << "Square\nWidth: " << Rectangle::Width() << "\nArea: " << GetArea() 
                  << "\nPerimeter: " << GetPerimeter() << "\n";
    }

    // Operator overloads specific to Square
    Square operator+(const Square &rhs) const {
        double newWidth = Rectangle::Width() + rhs.Rectangle::Width();
        return Square(newWidth);
    }
    Square operator-(const Square &rhs) const {
        double newWidth = std::abs(Rectangle::Width() - rhs.Rectangle::Width());
        return Square(newWidth);
    }
    Square& operator+=(const Square &rhs) {
        this->width += rhs.Rectangle::Width();
        this->height = this->width; // Ensure it remains a square
        return *this;
    }
    Square& operator-=(const Square &rhs) {
        this->width = std::abs(this->width - rhs.Rectangle::Width());
        this->height = this->width; // Ensure it remains a square
        return *this;
    }
};

#endif // SQUARE_H
