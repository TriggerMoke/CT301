//Aidan Michalos
//HW3 - Basic Vector

#include <stdexcept>
#include <utility>
#include <type_traits>

template<typename T>
class basic_vector {
public:
    // Constructors
    basic_vector(); // Default constructor
    explicit basic_vector(size_t capacity); // Capacity constructor
    basic_vector(const basic_vector& rhs); // Copy constructor
    basic_vector& operator=(basic_vector rhs); // Copy assignment operator

    // Destructor
    ~basic_vector();

    // Capacity methods
    size_t size() const;
    size_t max_size() const;
    size_t capacity() const;
    void resize(size_t n);
    void resize(size_t n, const T& val);
    bool empty() const;
    void reserve(size_t n);
    void shrink_to_fit();

    // Element access
    T& operator[](size_t n);
    T& at(size_t n);
    T& front();
    T& back();
    T* data();

    // Modifiers
    void push_back(const T& val);
    void pop_back();
    void swap(basic_vector& swerp);
    void clear();

private:
    T* data_ = nullptr; // Pointer to the first element
    size_t size_ = 0; // Current size
    size_t capacity_ = 0; // Current capacity

    void reallocate(size_t new_capacity); // Helper function for reallocation
    void destroy_elements(T* start, size_t n); // Helper for destroying elements
};

/* Constructors/destructor */

/* Constructor */
// Input: None
// Returns: None
// Description: Initializes a basic_vector with a default capacity of 1.
// Implementation: Allocates dynamic array of type T with initial capacity.
template<typename T>
basic_vector<T>::basic_vector() : capacity_(1) {
    data_ = new T[capacity_];
}

/* Constructor */
// Input, size_t capacity: Initial capacity of the vector.
// Returns: None
// Description: Initializes a basic_vector with the specified capacity.
// Implementation: Allocates dynamic array of type T with specified capacity.
template<typename T>
basic_vector<T>::basic_vector(size_t capacity) : capacity_(capacity) {
    data_ = new T[capacity_];
}

/* Copy Constructor */
// Input, const basic_vector& rhs: Vector to be copied.
// Returns: None
// Description: Initializes a basic_vector as a copy of an existing vector.
// Implementation: Allocates new memory and copies elements from rhs to the newly allocated space.
template<typename T>
basic_vector<T>::basic_vector(const basic_vector& rhs) : size_(rhs.size_), capacity_(rhs.capacity_) {
    data_ = new T[capacity_];
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = rhs.data_[i];
    }
}

/* Destructor */
// Input: None
// Returns: None
// Description: Destroys the basic_vector, freeing its memory.
// Implementation: Deallocates the dynamic array used by the vector.
template<typename T>
basic_vector<T>::~basic_vector() {
    delete[] data_;
}

/* Copy Assignment Operator */
// Input, basic_vector rhs: Vector to be copied.
// Returns, basic_vector&: Reference to *this vector after copying.
// Description: Assigns rhs to the current vector.
// Implementation: Swaps *this with rhs, effectively copying rhs and deallocating old memory of *this.
template<typename T>
basic_vector<T>& basic_vector<T>::operator=(basic_vector rhs) {
    if (&rhs != this) {
        swap(rhs);
    }
    return *this;
}

// Capacity methods

/* size */
// Input: None
// Returns, size_t: Current size of the vector.
// Description: Returns the number of elements currently stored in the vector.
// Implementation: Directly returns the size_ member variable.
template<typename T>
size_t basic_vector<T>::size() const {
    return size_;
}

/* max_size */
// Input: None
// Returns, size_t: The theoretical maximum size of the vector based on memory constraints.
// Description: Calculates and returns the maximum number of elements the vector can hold.
// Implementation: Utilizes sizeof(T) to determine the maximum number of elements that can be allocated.
template<typename T>
size_t basic_vector<T>::max_size() const {
    return (static_cast<size_t>(-1) / sizeof(T)) - 1;
}

/* capacity */
// Input: None
// Returns, size_t: The current capacity of the vector.
// Description: Returns the total amount of space currently allocated for the vector, which may be greater than the current size.
// Implementation: Returns the capacity_ member variable which tracks the allocated memory size.
template<typename T>
size_t basic_vector<T>::capacity() const {
    return capacity_;
}

/* resize */
// Input, size_t n: The new size for the vector.
// Throws std::length_error: If n exceeds max_size().
// Description: Adjusts the size of the vector to n, initializing new elements to default if size increases.
// Implementation: If n is greater than current capacity, reallocates storage. Truncates or default-initializes elements as needed.
template<typename T>
void basic_vector<T>::resize(size_t n) {
    if (n > max_size()) {
        throw std::length_error("resize beyond max_size");
    }
    if (n > capacity_) {
        reallocate(n);
    }
    if (n > size_) {
        for (size_t i = size_; i < n; ++i) {
            data_[i] = T{}; // Default-initialization
        }
    } else {
        destroy_elements(data_ + n, size_ - n);
    }
    size_ = n;
}

/* resize with value */
// Input, size_t n: The new size for the vector.
// Input, const T& val: The value to initialize new elements with, if size increases.
// Throws std::length_error: If n exceeds max_size().
// Description: Resizes the vector to n, using val to initialize new elements if size increases.
// Implementation: Similar to resize(size_t n), but initializes new elements with val instead of default value.
template<typename T>
void basic_vector<T>::resize(size_t n, const T& val) {
    if (n > max_size()) {
        throw std::length_error("resize beyond max_size");
    }
    if (n > capacity_) {
        reallocate(n);
    }
    if (n > size_) {
        for (size_t i = size_; i < n; ++i) {
            data_[i] = val;
        }
    } else {
        destroy_elements(data_ + n, size_ - n);
    }
    size_ = n;
}

/* empty */
// Input: None
// Returns, bool: True if the vector is empty, false otherwise.
// Description: Checks if the vector is empty (i.e., size is 0).
// Implementation: Returns true if size_ is 0; otherwise returns false.
template<typename T>
bool basic_vector<T>::empty() const {
    return size_ == 0;
}

/* reserve */
// Input, size_t n: The new capacity to reserve.
// Description: Allocates memory to increase the capacity of the vector to n, if n is greater than the current capacity.
// Implementation: If n is greater than current capacity, reallocates the array to the size of n, preserving existing elements.
template<typename T>
void basic_vector<T>::reserve(size_t n) {
    if (n > capacity_) {
        reallocate(n);
    }
}

/* shrink_to_fit */
// Input: None
// Returns: None
// Description: Reduces the capacity of the vector to fit its size, potentially reducing memory usage.
// Implementation: If the size is less than the capacity, reallocates the array to match the size, reducing the capacity to fit the size.
template<typename T>
void basic_vector<T>::shrink_to_fit() {
    if (size_ < capacity_) {
        reallocate(size_);
    }
}

// Element access

/* operator[] */
// Input, size_t n: Index of the element to access.
// Returns, T&: Reference to the element at index n.
// Description: Accesses the element at index n without bounds checking.
// Implementation: Returns the element at the specified index. Users are responsible for ensuring the index is within bounds.
template<typename T>
T& basic_vector<T>::operator[](size_t n) {
    return data_[n];
}

/* at */
// Input, size_t n: Index of the element to access.
// Returns, T&: Reference to the element at index n.
// Throws std::range_error: If n is out of bounds.
// Description: Accesses the element at index n with bounds checking.
// Implementation: Checks if the index is within bounds and throws std::range_error if not; otherwise, returns the element.
template<typename T>
T& basic_vector<T>::at(size_t n) {
    if (n >= size_) {
        throw std::range_error("Index out of range");
    }
    return data_[n];
}

/* front */
// Input: None
// Returns, T&: Reference to the first element in the vector.
// Description: Returns a reference to the first element in the vector.
// Implementation: Directly returns the first element. Assumes vector is not empty.
template<typename T>
T& basic_vector<T>::front() {
    return data_[0];
}

/* back */
// Input: None
// Returns, T&: Reference to the last element in the vector.
// Description: Returns a reference to the last element in the vector.
// Implementation: Directly returns the last element. Assumes vector is not empty.
template<typename T>
T& basic_vector<T>::back() {
    return data_[size_ - 1];
}

/* data */
// Input: None
// Returns, T*: Pointer to the underlying array.
// Description: Provides direct access to the underlying array.
// Implementation: Returns the pointer to the beginning of the array.
template<typename T>
T* basic_vector<T>::data() {
    return data_;
}


// Modifiers

/* push_back */
// Input, const T& val: The value to be added to the end of the vector.
// Returns: None
// Description: Adds a new element to the end of the vector, resizing if necessary.
// Implementation: Checks if resizing is necessary and doubles capacity if so. Then adds the new element to the end.
template<typename T>
void basic_vector<T>::push_back(const T& val) {
    if (size_ == capacity_) {
        reallocate(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    data_[size_++] = val;
}

/* pop_back */
// Input: None
// Returns: None
// Description: Removes the last element from the vector, reducing its size by one.
// Implementation: Directly reduces the size of the vector. Does not reallocate memory.
template<typename T>
void basic_vector<T>::pop_back() {
    if (size_ > 0) {
        --size_;
        delete data_[size_];
    }
}

/* clear */
// Input: None
// Returns: None
// Description: Removes all elements from the vector, setting its size to 0.
// Implementation: Calls the destructor for each element if necessary and sets the size to 0.
template<typename T>
void basic_vector<T>::clear() {
    destroy_elements(data_, size_);
    size_ = 0;
}

/* swap */
// Input, basic_vector& swerp: Another vector to swap contents with.
// Returns: None
// Description: Exchanges the contents of the vector with those of another vector.
// Implementation: Swaps the data, size, and capacity members with those of the other vector.
template<typename T>
void basic_vector<T>::swap(basic_vector& swerp) {
    std::swap(data_, swerp.data_);
    std::swap(size_, swerp.size_);
    std::swap(capacity_, swerp.capacity_);
}

// Helper functions

/* destroy_elements (private) */
// Input, T* start: Pointer to the first element to destroy.
// Input, size_t n: Number of elements to destroy.
// Returns: None
// Description: Destroys elements in the specified range, calling destructors if necessary.
// Implementation: Calls the destructor for each element in the range if the type is not fundamental.
template<typename T>
void basic_vector<T>::destroy_elements(T* start, size_t n) {
    // Conditional destruction based on type traits
    if (!std::is_fundamental<T>::value) {
        for (size_t i = 0; i < n; ++i) {
            (start + i)->~T();
        }
    }
}

/* reallocate (private) */
// Input, size_t new_capacity: The new capacity for the vector.
// Returns: None
// Description: Allocates new memory for the vector and moves existing elements to the new memory block.
// Implementation: Creates a new dynamic array of the specified capacity, moves existing elements, and deallocates old memory.
template<typename T>
void basic_vector<T>::reallocate(size_t new_capacity) {
    T* new_data = new T[new_capacity];
    for (size_t i = 0; i < size_; ++i) {
        new_data[i] = std::move(data_[i]);
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
}