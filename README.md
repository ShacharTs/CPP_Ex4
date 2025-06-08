### Shachar Tsrafati 318790169
# MyContainer<T>

## Overview
A custom, template-based container class in C++ that supports dynamic resizing, element access, and multiple ordering strategies for iteration.

## Project Structure
- **MyContainer.hpp**: Template class declaration and method definitions.
- **MyContainerExceptions.hpp**: Custom exceptions for safe container usage.
- **main.cpp**: Example usage of the container.
- **test.cpp**: Doctest-based unit tests.
- **makefile**: Build instructions.

## MyContainer Class

### Features
- Add, remove, and access elements
- Dynamic resizing of internal array
- Contains check, size query, and empty state
- Multiple iterator orders:
    - Ascending
    - Descending
    - Reverse
    - Side-cross (min, max, next-min...)
    - Middle-out (from center outward)
- Copy constructor and assignment
- Safe iterator operations with bounds checking

### Supported Types

Works with:
- **Built-in types**: `int`, `unsigned int`, `size_t`, etc.
- **Custom classes**: e.g., `People` (as long as they support):
    - Copy/move constructors
    - Comparison operators (`<`, `>`, `==`)
    - `operator<<` for printing (optional but useful)

## Build

```bash
make        # build and run the demo (main)
make test   # build and run tests WITH Valgrind
