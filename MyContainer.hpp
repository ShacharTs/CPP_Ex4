#pragma once
#include <iostream>
#include <stdexcept>

using namespace std;
namespace MyContainer {
    template<typename T>
    class MyContainer {
    private:
        T *elements; // pointer to the array of elements
        size_t capacity;
        size_t _size;
        void resize(size_t new_capacity);

    public:
        // default constructor
        MyContainer<T>();

        // destructor
        ~MyContainer<T>();

        // copy constructor
        MyContainer<T>(const MyContainer<T> &other);

        // copy assignment operator
        MyContainer<T> &operator=(const MyContainer<T> &other);

        // add element needs to add throw when full, if there are multi of the same val, add all of them
        void add(const T &element);

        // remove element, if not found, throw exception
        void remove(const T &element);

        T &at(size_t index);

        // return the size of the container
        size_t size() const;

        // check if the container is empty
        bool isEmpty() const;

        // check if a element is inside the container
        bool contains(const T &element) const;

        // friend function to print the container
        friend ostream &operator<<(ostream &os, const MyContainer<T> &container) {

        }

        /**
         * Class Iterator
         * This class provides an iterator for the MyContainer class.
         * It allows iteration over the elements of the container
         * in various orders.
         */
        class Iterator {
        public:
            // constructor and destructor
            Iterator();
            ~Iterator();
            // copy constructor
            Iterator(const Iterator &other);
            // operators for assignment
            Iterator operator++();
            Iterator operator--();
            Iterator operator++(int);
            Iterator operator--(int);
            // assignment operator
            Iterator &operator=(const Iterator &other);
            // operator to access the element
            T &operator*() const;
            // operator to check if two iterators are equal
            bool operator==(const Iterator &other) const;
            // operator to check if two iterators are not equal
            bool operator!=(const Iterator &other) const;
            // operator to access the element by index
            T &operator[](size_t index) const;
        };

    public:
        Iterator begin();

        Iterator end();

        Iterator AscendingOrder();

        Iterator DescendingOrder();

        Iterator SideCrossOrder();

        Iterator ReverseOrder();

        Iterator Order();

        Iterator MiddleOutOrder();
    };

    /**
     * Change the capacity of the container
     * @param new_capacity the new capacity of the container
     */
    template<typename T>
    void MyContainer<T>::resize(size_t new_capacity) {
        if (capacity == new_capacity) {
            return; // No need to resize if the capacity is the same
        }
        T* new_elements = new T[new_capacity];
        if (elements != nullptr) {
            for (size_t i = 0; i < _size && i < new_capacity; ++i) {
                new_elements[i] = elements[i];
            }
            delete[] elements;
        }
        elements = new_elements;
        capacity = new_capacity;
        // Adjust size if it exceeds new capacity
        if (_size > new_capacity) {
            _size = new_capacity;
        }
    }

    /**
     * Constructor for MyContainer
     */
    template<typename T>
    MyContainer<T>::MyContainer() : elements(nullptr), capacity(0), _size(0) {
    }

    /**
     * Destructor for MyContainer
     */
    template<typename T>
    MyContainer<T>::~MyContainer() {
        delete[] elements;
    }

    /**
     * Copy constructor for MyContainer
     * @param other myContainer to copy from
     */
    template<typename T>
    MyContainer<T>::MyContainer(const MyContainer<T> &other) {
        this->_size = other._size;
        this->capacity = other.capacity;
        this->elements = new T[other.capacity];
        // Copy elements from the other container
        for (size_t i = 0; i < other._size; ++i) {
            this->elements[i] = other.elements[i];
        }
    }

    /**
     * Copy assignment operator for MyContainer
     * @param other myContainer to copy from
     * @return reference to this container
     */
    template<typename T>
    MyContainer<T> & MyContainer<T>::operator=(const MyContainer<T> &other) {
        if (this != &other) {
            delete[] this->elements; // free existing elements
            // overwrite with other's elements
            this->_size = other._size;
            this->capacity = other.capacity;
            this->elements = new T[other.capacity];
            // Copy elements from the other container
            for (size_t i = 0; i < other._size; ++i) {
                this->elements[i] = other.elements[i];
            }
        }
        return *this;
    }

    /**
     * Add an element to the container.
     * @param element the element to add
     */
    template<typename T>
    void MyContainer<T>::add(const T &element) {
        if (_size == capacity) {
            // If the container is full, resize it to double the current \n
            // capacity, faster runtime when adding elements
            size_t new_capacity = (capacity == 0) ? 1 : capacity * 2;
            resize(new_capacity);
        }
        this->elements[this->_size++] = element;
    }

    /**
     * Remove an element from the container.
     * If there are multiple instances of the element, remove all of them.
     * If the element is not found, throw an exception.
     * @param element the element to remove
     */
    template<typename T>
void MyContainer<T>::remove(const T& element) {
        size_t new_size = 0;
        bool found = false;

        for (size_t i = 0; i < _size; ++i) {
            if (elements[i] != element) {
                elements[new_size++] = elements[i];  // Keep the element
            } else {
                found = true;  // Element found at least once
            }
        }

        if (!found) {
            throw std::runtime_error("Element not found in the container.");
        }

        _size = new_size;

        // Shrink if too much unused space
        if (_size < capacity / 4 && capacity > 1) {
            resize(capacity / 2);
        }
        // If the size is zero, free the memory and reset capacity
        if (_size == 0) {
            delete[] elements;
            elements = nullptr;
            capacity = 0;
        }
    }


    /**
     * Provides access to the element at the specified index.
     * If the index is out of bounds, throw an exception.
     * @param index the index of the element to access
     * @return a reference to the element at the specified index
     */
    template<typename T>
    T& MyContainer<T>::at(size_t index) {
    }

    /**
     * Returns the number of elements in the container.
     */
    template<typename T>
    size_t MyContainer<T>::size() const {
    }

    /**
     * Checks if the container is empty.
     * @return true if the container is empty, false otherwise
     */
    template<typename T>
    bool MyContainer<T>::isEmpty() const {
    }

    /**
     * Checks if the container contains a specific element.
     * @param element  the element to check for
     * @return true if the element is found, false otherwise
     */
    template<typename T>
    bool MyContainer<T>::contains(const T &element) const {
    }

    template<typename T>
    MyContainer<T>::Iterator::Iterator() {
    }

    template<typename T>
    MyContainer<T>::Iterator::~Iterator() {
    }

    template<typename T>
    MyContainer<T>::Iterator::Iterator(const Iterator &other) {
    }

    template<typename T>
    typename MyContainer<T>::Iterator MyContainer<T>::Iterator::operator++() {
    }

    template<typename T>
    typename MyContainer<T>::Iterator MyContainer<T>::Iterator::operator--() {
    }

    template<typename T>
    typename MyContainer<T>::Iterator MyContainer<T>::Iterator::operator++(int) {
    }

    template<typename T>
    typename MyContainer<T>::Iterator MyContainer<T>::Iterator::operator--(int) {
    }

    template<typename T>
    typename MyContainer<T>::Iterator & MyContainer<T>::Iterator::operator=(const Iterator &other) {
    }

    template<typename T>
    T & MyContainer<T>::Iterator::operator*() const {
    }

    template<typename T>
    bool MyContainer<T>::Iterator::operator==(const Iterator &other) const {
    }

    template<typename T>
    bool MyContainer<T>::Iterator::operator!=(const Iterator &other) const {
    }

    template<typename T>
    T& MyContainer<T>::Iterator::operator[](size_t index) const {
    }

    template<typename T>
    typename MyContainer<T>::Iterator MyContainer<T>::begin() {
    }

    template<typename T>
    typename MyContainer<T>::Iterator MyContainer<T>::end() {
    }

    template<typename T>
    typename MyContainer<T>::Iterator MyContainer<T>::AscendingOrder() {
    }

    template<typename T>
    typename MyContainer<T>::Iterator MyContainer<T>::DescendingOrder() {
    }

    template<typename T>
    typename MyContainer<T>::Iterator MyContainer<T>::SideCrossOrder() {
    }

    template<typename T>
    typename MyContainer<T>::Iterator MyContainer<T>::ReverseOrder() {
    }

    template<typename T>
    typename MyContainer<T>::Iterator MyContainer<T>::Order() {
    }

    template<typename T>
    typename MyContainer<T>::Iterator MyContainer<T>::MiddleOutOrder() {
    }


}
