#include "shape.h"

std::ostream &operator<<(std::ostream &os, const Shape &shape) {
    return shape.Print(os);
}