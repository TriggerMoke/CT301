#include <iostream>

// Assuming that the basic_vector template class is defined in "basic_vector.h"
#include "basic_vector.h"

int main() {
    basic_vector<int> int_vector;
    basic_vector<char> char_vector;
    basic_vector<double> double_vector;

    // Add some elements to the vectors
    int_vector.push_back(1);
    int_vector.push_back(2);

    char_vector.push_back('a');
    char_vector.push_back('b');
    char_vector.push_back('c');

    double_vector.push_back(1.1);
    double_vector.push_back(2.2);
    double_vector.push_back(3.3);
    double_vector.push_back(4.4);

    // Output the sizes of the vectors
    std::cout << "int_vector size: " << int_vector.size() << std::endl;
    std::cout << "char_vector size: " << char_vector.size() << std::endl;
    std::cout << "double_vector size: " << double_vector.size() << std::endl;

    return 0;
}
