#pragma once
#include <stdexcept>

class OutOfRange : public std::out_of_range {
public:
    explicit OutOfRange(const std::string& msg) : std::out_of_range(msg) {}
};

class ElementNotFound : public std::runtime_error {
public:
    explicit ElementNotFound(const std::string& msg) : std::runtime_error (msg) {}
};


// class OutOfRange : public std::out_of_range {
// public:
//     explicit OutOfRange(const std::string& msg) : std::runtime_error (msg) {}
// };