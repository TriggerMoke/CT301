#include "shape.h"

/* operator overload needed in .cpp file*/
std::ostream &operator<<(std::ostream &os, const Shape &shape) {
    return shape.Print(os);
}