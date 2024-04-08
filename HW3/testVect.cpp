#include <iostream>
#include "basic_vector.h"

// Helper function to report test results
void report_test(const std::string& test_name, bool passed) {
    // Output test results
    std::cout << "Test " << test_name << ": " << (passed ? "PASSED" : "FAILED") << std::endl;
    // output size of the vector
    std::cout << "Size of the vector: " << sizeof(basic_vector<int>) << std::endl;
}

// Test function
void test_size() {
    basic_vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);

    // Expected vs Actual
    size_t expected_size = 2;
    size_t actual_size = vec.size();

    report_test("test_size", expected_size == actual_size);
}

void million_size_test() {
    basic_vector<int> vec;
    for (int i = 0; i < 1000000; i++) {
        vec.push_back(i);
    }

    // Expected vs Actual
    size_t expected_size = 1000000;
    size_t actual_size = vec.size();

    report_test("million_size_test", expected_size == actual_size);
}

int main() {
    test_size();


    return 0;
}
