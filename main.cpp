#include <iostream>
#include "container/MyContainer.hpp"

using namespace MyContainerNamespace;
int main() {
    MyContainer <int> container;
    container.add(7);
    container.add(15);
    container.add(6);
    container.add(1);
    container.add(2);

    std::cout << "Size of container: " << container.size() << std::endl;

    for (auto it = container.beginAscendingOrder(); it != container.endAscendingOrder(); ++it) {
        std::cout << *it << ' ';   // 1 2 6 7 15
    }
    std::cout << std::endl;

    for (auto it = container.beginDescendingOrder(); it != container.endDescendingOrder(); ++it) {
        std::cout << *it << ' ';  // 15 7 6 2 1
    }
    std::cout << std::endl;

    for (auto it = container.beginSideCrossOrder(); it != container.endSideCrossOrder(); ++it) {
        std::cout << *it << ' ';  // 1 15 2 7 6
    }
    std::cout << std::endl;

    for (auto it = container.beginReverseOrder(); it != container.endReverseOrder(); ++it) {
        std::cout << *it << ' ';  // 2 1 6 15 7
    }
    std::cout << std::endl;

    for (auto it = container.beginOrder(); it != container.endOrder(); ++it) {
        std::cout << *it << ' ';  // 7 15 6 1 2
    }
    std::cout << std::endl;

    for (auto it = container.beginMiddleOutOrder(); it != container.endMiddleOutOrder(); ++it) {
        std::cout << *it << ' ';  // 6 15 1 7 2
    }
    std::cout << std::endl;

  

    return 0;
}
