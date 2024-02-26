#include "shape.h"

std::ostream &operator<<(std::ostream &os, const Shape *shape) {
    if (shape) // Ensure the pointer is not null
        return shape->Print(os); // Call the virtual Print method
    else
        return os << "Null Shape\n"; // Handle null pointer case
}