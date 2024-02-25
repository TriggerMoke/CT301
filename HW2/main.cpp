#include "circle.h"
#include "rectangle.h"
#include "square.h"
#include "triangle.h"
#include <iostream>

using std::cout;

std::ostream &operator<<(std::ostream &os, const Shape &rhs) {
    return rhs.Print(os); // Call Print on the reference directly.
}

int main() {
	// Circle test
    Circle circle_1(10);
    Circle circle_2(5);
    Circle circle_3 = circle_1 + circle_2;

    cout << "circle_1:\n" << circle_1 << '\n';
    cout << "circle_2:\n" << circle_2 << '\n';
    cout << "circle_1 + circle_2:\n" << circle_3 << '\n';

    // Rectangle test
    Rectangle rect_1(4, 5);
    Rectangle rect_2(2, 3);
    Rectangle rect_3 = rect_1 + rect_2;

    cout << "rect_1:\n" << rect_1 << '\n';
    cout << "rect_2:\n" << rect_2 << '\n';
    cout << "rect_1 + rect_2:\n" << rect_3 << '\n';

    // Square test
    Square square_1(4);
    Square square_2(2);
    Square square_3 = square_1 + square_2; // Assuming operator+ treats squares like rectangles for simplicity

    cout << "square_1:\n" << square_1 << '\n';
    cout << "square_2:\n" << square_2 << '\n';
    cout << "square_1 + square_2:\n" << square_3 << '\n';

    // Triangle test
    Triangle tri_1(4);
    Triangle tri_2(3);
    Triangle tri_3 = tri_1 + tri_2; // Assuming simple side addition

    cout << "tri_1:\n" << tri_1 << '\n';
    cout << "tri_2:\n" << tri_2 << '\n';
    cout << "tri_1 + tri_2:\n" << tri_3 << '\n';

	return 0;
}