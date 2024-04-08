#include <iostream>
#include "basic_vector.h"

// Helper function to report test results
void report_test(const std::string& test_name, bool passed) {
    std::cout << "Test " << test_name << ": " << (passed ? "PASSED" : "FAILED") << std::endl;
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

int main() {
    test_size();


    return 0;
}
