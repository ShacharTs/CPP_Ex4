#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../container/MyContainer.hpp"
#include "People.hpp"
#include <sstream>

using namespace PeopleClass;

using namespace MyContainerNamespace;

//////// INT CONTAINER TESTS //////////
TEST_CASE("MyContainer<int>") {
    MyContainer<int> c;

    SUBCASE("Default constructor") {
        CHECK(c.size() == 0);
        CHECK(c.isEmpty());
    }

    SUBCASE("Add with duplicates") {
        c.add(1);
        c.add(1);
        c.add(2);
        CHECK(c.size() == 3);
    }

    SUBCASE("Remove existing and non-existing") {
        c.add(10);
        c.add(20);
        CHECK_NOTHROW(c.remove(10));
        CHECK_THROWS_AS(c.remove(99), ElementNotFound);
    }

    SUBCASE("Access elements via at()") {
        c.add(7);
        CHECK(c.at(0) == 7);
        CHECK_THROWS_AS(c.at(10), OutOfRange);
    }

    SUBCASE("Contains check") {
        c.add(5);
        CHECK(c.contains(5));
        CHECK_FALSE(c.contains(100));
    }

    SUBCASE("Copy constructor and assignment") {
        c.add(1);
        c.add(2);
        MyContainer<int> copy(c);
        CHECK(copy.size() == 2);
        CHECK(copy.contains(1));

        MyContainer<int> assign;
        assign = c;
        CHECK(assign.size() == 2);
        CHECK(assign.contains(2));
    }

    SUBCASE("Operator <<") {
        c.add(4);
        c.add(5);
        std::ostringstream oss;
        oss << c;
        CHECK(oss.str() == "[4, 5]");
    }

    SUBCASE("Iterators: generic usage") {
        c.add(1);
        c.add(2);
        c.add(3);

        int count = 0;
        for (auto it = c.begin(); it != c.end(); ++it)
            ++count;
        CHECK(count == 3);
    }

    SUBCASE("All iterators produce expected order") {
        c.add(1);
        c.add(2);
        c.add(3);
        c.add(4);
        c.add(5);

        std::vector<int> expected;

        SUBCASE("Order") {
            expected = {1, 2, 3, 4, 5};
            int i = 0;
            for (auto it = c.beginOrder(); it != c.endOrder(); ++it)
                CHECK(*it == expected[i++]);
        }

        SUBCASE("Reverse") {
            expected = {5, 4, 3, 2, 1};
            int i = 0;
            for (auto it = c.beginReverseOrder(); it != c.endReverseOrder(); ++it)
                CHECK(*it == expected[i++]);
        }

        SUBCASE("Ascending") {
            expected = {1, 2, 3, 4, 5};
            int i = 0;
            for (auto it = c.beginAscendingOrder(); it != c.endAscendingOrder(); ++it)
                CHECK(*it == expected[i++]);
        }

        SUBCASE("Descending") {
            expected = {5, 4, 3, 2, 1};
            int i = 0;
            for (auto it = c.beginDescendingOrder(); it != c.endDescendingOrder(); ++it)
                CHECK(*it == expected[i++]);
        }

        SUBCASE("SideCross") {
            expected = {1, 5, 2, 4, 3};
            int i = 0;
            for (auto it = c.beginSideCrossOrder(); it != c.endSideCrossOrder(); ++it)
                CHECK(*it == expected[i++]);
        }

        SUBCASE("MiddleOut") {
            expected = {3, 4, 2, 5, 1};
            int i = 0;
            for (auto it = c.beginMiddleOutOrder(); it != c.endMiddleOutOrder(); ++it)
                CHECK(*it == expected[i++]);
        }
    }

    SUBCASE("Iterator operations: ++, --, ==, !=, *") {
        c.add(10);
        c.add(20);
        c.add(30);

        auto it1 = c.beginOrder();
        auto it2 = it1;
        ++it2;
        CHECK(it1 != it2);
        CHECK(*it2 == 20);
        --it2;
        CHECK(it1 == it2);
    }

    SUBCASE("Iterator operator[] and ->") {
        c.add(100);
        c.add(200);
        auto it = c.beginOrder();
        CHECK(it[1] == 200);
        CHECK(*it == 100);
    }
    // Remove all duplicates test
    SUBCASE("Remove all duplicates") {
        c.add(5);
        c.add(5);
        c.add(5);
        CHECK(c.size() == 3);
        c.remove(5);
        CHECK(c.isEmpty());
        CHECK_THROWS_AS(c.remove(5), ElementNotFound);
    }

    // Remove from empty container throws
    SUBCASE("Remove from empty container") {
        CHECK_THROWS_AS(c.remove(10), ElementNotFound);
    }

    // at() throws if container empty
    SUBCASE("at() throws when container empty") {
        CHECK_THROWS_AS(c.at(0), ContainerEmpty);
    }

    // at() throws for out-of-range index
    SUBCASE("at() throws for out-of-range") {
        c.add(1);
        CHECK_THROWS_AS(c.at(5), OutOfRange);
    }

    // Iterator increment past end throws
    SUBCASE("Iterator increment past end throws") {
        c.add(1);
        auto it = c.begin();
        ++it; // now at the end
        CHECK_THROWS_AS(++it, OutOfRange);
    }

    // Iterator decrement before begin throws
    SUBCASE("Iterator decrement before begin throws") {
        c.add(1);
        auto it = c.begin();
        CHECK_THROWS_AS(--it, OutOfRange);
    }

    // Dereferencing end iterator throws
    SUBCASE("Iterator dereference end throws") {
        c.add(1);
        auto it = c.end();
        CHECK_THROWS_AS(*it, OutOfRange);
    }

    // Self-assignment does not break container
    SUBCASE("Self-assignment") {
        c.add(10);
        c.add(20);
        c = c;
        CHECK(c.size() == 2);
        CHECK(c.contains(10));
        CHECK(c.contains(20));
    }

    // Assign empty container to non-empty container
    SUBCASE("Assign empty to non-empty") {
        MyContainer<int> c2;
        c.add(1);
        c2 = c;
        c = MyContainer<int>(); // assign empty
        CHECK(c.isEmpty());
    }

    // Add and remove large number of elements to test resizing
    SUBCASE("Large add and remove") {
        const int large_size = 10000;
        for (int i = 0; i < large_size; ++i) {
            c.add(i);
        }
        CHECK(c.size() == large_size);
        for (int i = 0; i < large_size; ++i) {
            c.remove(i);
        }
        CHECK(c.isEmpty());
    }

    // Const correctness checks
    SUBCASE("Const correctness") {
        c.add(1);
        const MyContainer<int> &cc = c;
        CHECK(cc.size() == 1);
        CHECK_FALSE(cc.isEmpty());
        CHECK(cc.contains(1));
    }

    // Iterator on empty container returns begin == end
    SUBCASE("Iterator on empty container") {
        CHECK(c.begin() == c.end());
    }
}

 //////// UNSIGNED INT CONTAINER TESTS //////////
TEST_CASE("MyContainer<unsigned int>") {
    MyContainer<unsigned int> c;

    SUBCASE("Default constructor") {
        CHECK(c.size() == 0);
        CHECK(c.isEmpty());
    }

    SUBCASE("Add with duplicates") {
        c.add(1);
        c.add(1);
        c.add(2);
        CHECK(c.size() == 3);
    }

    SUBCASE("Remove existing and non-existing") {
        c.add(10);
        c.add(20);
        CHECK_NOTHROW(c.remove(10));
        CHECK_THROWS_AS(c.remove(99), ElementNotFound);
    }

    SUBCASE("Access elements via at()") {
        c.add(7);
        CHECK(c.at(0) == 7);
        CHECK_THROWS_AS(c.at(10), OutOfRange);
    }

    SUBCASE("Contains check") {
        c.add(5);
        CHECK(c.contains(5));
        CHECK_FALSE(c.contains(100));
    }

    SUBCASE("Copy constructor and assignment") {
        c.add(1);
        c.add(2);
        MyContainer<unsigned int> copy(c);
        CHECK(copy.size() == 2);
        CHECK(copy.contains(1));

        MyContainer<unsigned int> assign;
        assign = c;
        CHECK(assign.size() == 2);
        CHECK(assign.contains(2));
    }

    SUBCASE("Operator <<") {
        c.add(4);
        c.add(5);
        std::ostringstream oss;
        oss << c;
        CHECK(oss.str() == "[4, 5]");
    }

    SUBCASE("Iterators: generic usage") {
        c.add(1);
        c.add(2);
        c.add(3);

        int count = 0;
        for (auto it = c.begin(); it != c.end(); ++it)
            ++count;
        CHECK(count == 3);
    }

    SUBCASE("All iterators produce expected order") {
        c.add(1);
        c.add(2);
        c.add(3);
        c.add(4);
        c.add(5);

        std::vector<int> expected;

        SUBCASE("Order") {
            expected = {1, 2, 3, 4, 5};
            int i = 0;
            for (auto it = c.beginOrder(); it != c.endOrder(); ++it)
                CHECK(*it == expected[i++]);
        }

        SUBCASE("Reverse") {
            expected = {5, 4, 3, 2, 1};
            int i = 0;
            for (auto it = c.beginReverseOrder(); it != c.endReverseOrder(); ++it)
                CHECK(*it == expected[i++]);
        }

        SUBCASE("Ascending") {
            expected = {1, 2, 3, 4, 5};
            int i = 0;
            for (auto it = c.beginAscendingOrder(); it != c.endAscendingOrder(); ++it)
                CHECK(*it == expected[i++]);
        }

        SUBCASE("Descending") {
            expected = {5, 4, 3, 2, 1};
            int i = 0;
            for (auto it = c.beginDescendingOrder(); it != c.endDescendingOrder(); ++it)
                CHECK(*it == expected[i++]);
        }

        SUBCASE("SideCross") {
            expected = {1, 5, 2, 4, 3};
            int i = 0;
            for (auto it = c.beginSideCrossOrder(); it != c.endSideCrossOrder(); ++it)
                CHECK(*it == expected[i++]);
        }

        SUBCASE("MiddleOut") {
            expected = {3, 4, 2, 5, 1};
            int i = 0;
            for (auto it = c.beginMiddleOutOrder(); it != c.endMiddleOutOrder(); ++it)
                CHECK(*it == expected[i++]);
        }
    }

    SUBCASE("Iterator operations: ++, --, ==, !=, *") {
        c.add(10);
        c.add(20);
        c.add(30);

        auto it1 = c.beginOrder();
        auto it2 = it1;
        ++it2;
        CHECK(it1 != it2);
        CHECK(*it2 == 20);
        --it2;
        CHECK(it1 == it2);
    }

    SUBCASE("Iterator operator[] and ->") {
        c.add(100);
        c.add(200);
        auto it = c.beginOrder();
        CHECK(it[1] == 200);
        CHECK(*it == 100);
    }
    // Remove all duplicates test
    SUBCASE("Remove all duplicates") {
        c.add(5);
        c.add(5);
        c.add(5);
        CHECK(c.size() == 3);
        c.remove(5);
        CHECK(c.isEmpty());
        CHECK_THROWS_AS(c.remove(5), ElementNotFound);
    }

    // Remove from empty container throws
    SUBCASE("Remove from empty container") {
        CHECK_THROWS_AS(c.remove(10), ElementNotFound);
    }

    // at() throws if container empty
    SUBCASE("at() throws when container empty") {
        CHECK_THROWS_AS(c.at(0), ContainerEmpty);
    }

    // at() throws for out-of-range index
    SUBCASE("at() throws for out-of-range") {
        c.add(1);
        CHECK_THROWS_AS(c.at(5), OutOfRange);
    }

    // Iterator increment past end throws
    SUBCASE("Iterator increment past end throws") {
        c.add(1);
        auto it = c.begin();
        ++it; // now at the end
        CHECK_THROWS_AS(++it, OutOfRange);
    }

    // Iterator decrement before begin throws
    SUBCASE("Iterator decrement before begin throws") {
        c.add(1);
        auto it = c.begin();
        CHECK_THROWS_AS(--it, OutOfRange);
    }

    // Dereferencing end iterator throws
    SUBCASE("Iterator dereference end throws") {
        c.add(1);
        auto it = c.end();
        CHECK_THROWS_AS(*it, OutOfRange);
    }

    // Self-assignment does not break container
    SUBCASE("Self-assignment") {
        c.add(10);
        c.add(20);
        c = c;
        CHECK(c.size() == 2);
        CHECK(c.contains(10));
        CHECK(c.contains(20));
    }

    // Assign empty container to non-empty container
    SUBCASE("Assign empty to non-empty") {
        MyContainer<unsigned int> c2;
        c.add(1);
        c2 = c;
        c = MyContainer<unsigned int>(); // assign empty
        CHECK(c.isEmpty());
    }

    // Add and remove large number of elements to test resizing
    SUBCASE("Large add and remove") {
        const int large_size = 10000;
        for (int i = 0; i < large_size; ++i) {
            c.add(i);
        }
        CHECK(c.size() == large_size);
        for (int i = 0; i < large_size; ++i) {
            c.remove(i);
        }
        CHECK(c.isEmpty());
    }

    // Const correctness checks
    SUBCASE("Const correctness") {
        c.add(1);
        const MyContainer<unsigned int> &cc = c;
        CHECK(cc.size() == 1);
        CHECK_FALSE(cc.isEmpty());
        CHECK(cc.contains(1));
    }

    // Iterator on empty container returns begin == end
    SUBCASE("Iterator on empty container") {
        CHECK(c.begin() == c.end());
    }
}

//////// SIZE_T CONTAINER TESTS //////////
TEST_CASE("MyContainer<size_t>") {
    MyContainer<size_t> c;

    SUBCASE("Default constructor") {
        CHECK(c.size() == 0);
        CHECK(c.isEmpty());
    }

    SUBCASE("Add with duplicates") {
        c.add(1);
        c.add(1);
        c.add(2);
        CHECK(c.size() == 3);
    }

    SUBCASE("Remove existing and non-existing") {
        c.add(10);
        c.add(20);
        CHECK_NOTHROW(c.remove(10));
        CHECK_THROWS_AS(c.remove(99), ElementNotFound);
    }

    SUBCASE("Access elements via at()") {
        c.add(7);
        CHECK(c.at(0) == 7);
        CHECK_THROWS_AS(c.at(10), OutOfRange);
    }

    SUBCASE("Contains check") {
        c.add(5);
        CHECK(c.contains(5));
        CHECK_FALSE(c.contains(100));
    }

    SUBCASE("Copy constructor and assignment") {
        c.add(1);
        c.add(2);
        MyContainer<size_t> copy(c);
        CHECK(copy.size() == 2);
        CHECK(copy.contains(1));

        MyContainer<size_t> assign;
        assign = c;
        CHECK(assign.size() == 2);
        CHECK(assign.contains(2));
    }

    SUBCASE("Operator <<") {
        c.add(4);
        c.add(5);
        std::ostringstream oss;
        oss << c;
        CHECK(oss.str() == "[4, 5]");
    }

    SUBCASE("Iterators: generic usage") {
        c.add(1);
        c.add(2);
        c.add(3);

        int count = 0;
        for (auto it = c.begin(); it != c.end(); ++it)
            ++count;
        CHECK(count == 3);
    }

    SUBCASE("All iterators produce expected order") {
        c.add(1);
        c.add(2);
        c.add(3);
        c.add(4);
        c.add(5);

        std::vector<int> expected;

        SUBCASE("Order") {
            expected = {1, 2, 3, 4, 5};
            int i = 0;
            for (auto it = c.beginOrder(); it != c.endOrder(); ++it)
                CHECK(*it == expected[i++]);
        }

        SUBCASE("Reverse") {
            expected = {5, 4, 3, 2, 1};
            int i = 0;
            for (auto it = c.beginReverseOrder(); it != c.endReverseOrder(); ++it)
                CHECK(*it == expected[i++]);
        }

        SUBCASE("Ascending") {
            expected = {1, 2, 3, 4, 5};
            int i = 0;
            for (auto it = c.beginAscendingOrder(); it != c.endAscendingOrder(); ++it)
                CHECK(*it == expected[i++]);
        }

        SUBCASE("Descending") {
            expected = {5, 4, 3, 2, 1};
            int i = 0;
            for (auto it = c.beginDescendingOrder(); it != c.endDescendingOrder(); ++it)
                CHECK(*it == expected[i++]);
        }

        SUBCASE("SideCross") {
            expected = {1, 5, 2, 4, 3};
            int i = 0;
            for (auto it = c.beginSideCrossOrder(); it != c.endSideCrossOrder(); ++it)
                CHECK(*it == expected[i++]);
        }

        SUBCASE("MiddleOut") {
            expected = {3, 4, 2, 5, 1};
            int i = 0;
            for (auto it = c.beginMiddleOutOrder(); it != c.endMiddleOutOrder(); ++it)
                CHECK(*it == expected[i++]);
        }
    }

    SUBCASE("Iterator operations: ++, --, ==, !=, *") {
        c.add(10);
        c.add(20);
        c.add(30);

        auto it1 = c.beginOrder();
        auto it2 = it1;
        ++it2;
        CHECK(it1 != it2);
        CHECK(*it2 == 20);
        --it2;
        CHECK(it1 == it2);
    }

    SUBCASE("Iterator operator[] and ->") {
        c.add(100);
        c.add(200);
        auto it = c.beginOrder();
        CHECK(it[1] == 200);
        CHECK(*it == 100);
    }
    // Remove all duplicates test
    SUBCASE("Remove all duplicates") {
        c.add(5);
        c.add(5);
        c.add(5);
        CHECK(c.size() == 3);
        c.remove(5);
        CHECK(c.isEmpty());
        CHECK_THROWS_AS(c.remove(5), ElementNotFound);
    }

    // Remove from empty container throws
    SUBCASE("Remove from empty container") {
        CHECK_THROWS_AS(c.remove(10), ElementNotFound);
    }

    // at() throws if container empty
    SUBCASE("at() throws when container empty") {
        CHECK_THROWS_AS(c.at(0), ContainerEmpty);
    }

    // at() throws for out-of-range index
    SUBCASE("at() throws for out-of-range") {
        c.add(1);
        CHECK_THROWS_AS(c.at(5), OutOfRange);
    }

    // Iterator increment past end throws
    SUBCASE("Iterator increment past end throws") {
        c.add(1);
        auto it = c.begin();
        ++it; // now at the end
        CHECK_THROWS_AS(++it, OutOfRange);
    }

    // Iterator decrement before begin throws
    SUBCASE("Iterator decrement before begin throws") {
        c.add(1);
        auto it = c.begin();
        CHECK_THROWS_AS(--it, OutOfRange);
    }

    // Dereferencing end iterator throws
    SUBCASE("Iterator dereference end throws") {
        c.add(1);
        auto it = c.end();
        CHECK_THROWS_AS(*it, OutOfRange);
    }

    // Self-assignment does not break container
    SUBCASE("Self-assignment") {
        c.add(10);
        c.add(20);
        c = c;
        CHECK(c.size() == 2);
        CHECK(c.contains(10));
        CHECK(c.contains(20));
    }

    // Assign empty container to non-empty container
    SUBCASE("Assign empty to non-empty") {
        MyContainer<size_t> c2;
        c.add(1);
        c2 = c;
        c = MyContainer<size_t>(); // assign empty
        CHECK(c.isEmpty());
    }

    // Add and remove large number of elements to test resizing
    SUBCASE("Large add and remove") {
        const int large_size = 10000;
        for (int i = 0; i < large_size; ++i) {
            c.add(i);
        }
        CHECK(c.size() == large_size);
        for (int i = 0; i < large_size; ++i) {
            c.remove(i);
        }
        CHECK(c.isEmpty());
    }

    // Const correctness checks
    SUBCASE("Const correctness") {
        c.add(1);
        const MyContainer<size_t> &cc = c;
        CHECK(cc.size() == 1);
        CHECK_FALSE(cc.isEmpty());
        CHECK(cc.contains(1));
    }

    // Iterator on empty container returns begin == end
    SUBCASE("Iterator on empty container") {
        CHECK(c.begin() == c.end());
    }
}

//////// FLOAT CONTAINER TESTS //////////
TEST_CASE("MyContainer<float>") {
    MyContainer<float> c;

    SUBCASE("Default constructor") {
        CHECK(c.size() == 0);
        CHECK(c.isEmpty());
    }

    SUBCASE("Add with duplicates") {
        c.add(1.0f);
        c.add(1.0f);
        c.add(2.0f);
        CHECK(c.size() == 3);
    }

    SUBCASE("Remove existing and non-existing") {
        c.add(10.0f);
        c.add(20.0f);
        CHECK_NOTHROW(c.remove(10.0f));
        CHECK_THROWS_AS(c.remove(99.0f), ElementNotFound);
    }

    SUBCASE("Access elements via at()") {
        c.add(7.0f);
        CHECK(c.at(0) == doctest::Approx(7.0f));
        CHECK_THROWS_AS(c.at(10), OutOfRange);
    }

    SUBCASE("Contains check") {
        c.add(5.0f);
        CHECK(c.contains(5.0f));
        CHECK_FALSE(c.contains(100.0f));
    }

    SUBCASE("Copy constructor and assignment") {
        c.add(1.0f);
        c.add(2.0f);
        MyContainer<float> copy(c);
        CHECK(copy.size() == 2);
        CHECK(copy.contains(1.0f));

        MyContainer<float> assign;
        assign = c;
        CHECK(assign.size() == 2);
        CHECK(assign.contains(2.0f));
    }

    SUBCASE("Operator <<") {
        c.add(4.0f);
        c.add(5.0f);
        std::ostringstream oss;
        oss << c;
        CHECK(oss.str().find("[") == 0); // output check, exact float formatting may vary
    }

    SUBCASE("Iterators: generic usage") {
        c.add(1.0f);
        c.add(2.0f);
        c.add(3.0f);

        int count = 0;
        for (auto it = c.begin(); it != c.end(); ++it)
            ++count;
        CHECK(count == 3);
    }

    SUBCASE("All iterators produce expected order") {
        c.add(1.0f);
        c.add(2.0f);
        c.add(3.0f);
        c.add(4.0f);
        c.add(5.0f);

        std::vector<float> expected;

        SUBCASE("Order") {
            expected = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
            int i = 0;
            for (auto it = c.beginOrder(); it != c.endOrder(); ++it)
                CHECK(*it == doctest::Approx(expected[i++]));
        }

        SUBCASE("Reverse") {
            expected = {5.0f, 4.0f, 3.0f, 2.0f, 1.0f};
            int i = 0;
            for (auto it = c.beginReverseOrder(); it != c.endReverseOrder(); ++it)
                CHECK(*it == doctest::Approx(expected[i++]));
        }

        SUBCASE("Ascending") {
            expected = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
            int i = 0;
            for (auto it = c.beginAscendingOrder(); it != c.endAscendingOrder(); ++it)
                CHECK(*it == doctest::Approx(expected[i++]));
        }

        SUBCASE("Descending") {
            expected = {5.0f, 4.0f, 3.0f, 2.0f, 1.0f};
            int i = 0;
            for (auto it = c.beginDescendingOrder(); it != c.endDescendingOrder(); ++it)
                CHECK(*it == doctest::Approx(expected[i++]));
        }

        SUBCASE("SideCross") {
            expected = {1.0f, 5.0f, 2.0f, 4.0f, 3.0f};
            int i = 0;
            for (auto it = c.beginSideCrossOrder(); it != c.endSideCrossOrder(); ++it)
                CHECK(*it == doctest::Approx(expected[i++]));
        }

        SUBCASE("MiddleOut") {
            expected = {3.0f, 4.0f, 2.0f, 5.0f, 1.0f};
            int i = 0;
            for (auto it = c.beginMiddleOutOrder(); it != c.endMiddleOutOrder(); ++it)
                CHECK(*it == doctest::Approx(expected[i++]));
        }
    }

    SUBCASE("Iterator operations: ++, --, ==, !=, *") {
        c.add(10.0f);
        c.add(20.0f);
        c.add(30.0f);

        auto it1 = c.beginOrder();
        auto it2 = it1;
        ++it2;
        CHECK(it1 != it2);
        CHECK(*it2 == doctest::Approx(20.0f));
        --it2;
        CHECK(it1 == it2);
    }

    SUBCASE("Iterator operator[] and ->") {
        c.add(100.0f);
        c.add(200.0f);
        auto it = c.beginOrder();
        CHECK(it[1] == doctest::Approx(200.0f));
        CHECK(*it == doctest::Approx(100.0f));
    }

    SUBCASE("Remove all duplicates") {
        c.add(5.0f);
        c.add(5.0f);
        c.add(5.0f);
        CHECK(c.size() == 3);
        c.remove(5.0f);
        CHECK(c.isEmpty());
        CHECK_THROWS_AS(c.remove(5.0f), ElementNotFound);
    }

    SUBCASE("Remove from empty container") {
        CHECK_THROWS_AS(c.remove(10.0f), ElementNotFound);
    }

    SUBCASE("at() throws when container empty") {
        CHECK_THROWS_AS(c.at(0), ContainerEmpty);
    }

    SUBCASE("at() throws for out-of-range") {
        c.add(1.0f);
        CHECK_THROWS_AS(c.at(5), OutOfRange);
    }

    SUBCASE("Iterator increment past end throws") {
        c.add(1.0f);
        auto it = c.begin();
        ++it; // now at the end
        CHECK_THROWS_AS(++it, OutOfRange);
    }

    SUBCASE("Iterator decrement before begin throws") {
        c.add(1.0f);
        auto it = c.begin();
        CHECK_THROWS_AS(--it, OutOfRange);
    }

    SUBCASE("Iterator dereference end throws") {
        c.add(1.0f);
        auto it = c.end();
        CHECK_THROWS_AS(*it, OutOfRange);
    }

    SUBCASE("Self-assignment") {
        c.add(10.0f);
        c.add(20.0f);
        c = c;
        CHECK(c.size() == 2);
        CHECK(c.contains(10.0f));
        CHECK(c.contains(20.0f));
    }

    SUBCASE("Assign empty to non-empty") {
        MyContainer<float> c2;
        c.add(1.0f);
        c2 = c;
        c = MyContainer<float>(); // assign empty
        CHECK(c.isEmpty());
    }

    SUBCASE("Large add and remove") {
        const int large_size = 10000;
        for (int i = 0; i < large_size; ++i) {
            c.add(static_cast<float>(i));
        }
        CHECK(c.size() == large_size);
        for (int i = 0; i < large_size; ++i) {
            c.remove(static_cast<float>(i));
        }
        CHECK(c.isEmpty());
    }

    SUBCASE("Const correctness") {
        c.add(1.0f);
        const MyContainer<float> &cc = c;
        CHECK(cc.size() == 1);
        CHECK_FALSE(cc.isEmpty());
        CHECK(cc.contains(1.0f));
    }

    SUBCASE("Iterator on empty container") {
        CHECK(c.begin() == c.end());
    }
}
//////// DOUBLE CONTAINER TESTS //////////
TEST_CASE("MyContainer<double>") {
    MyContainer<double> c;

    SUBCASE("Default constructor") {
        CHECK(c.size() == 0);
        CHECK(c.isEmpty());
    }

    SUBCASE("Add with duplicates") {
        c.add(1.0);
        c.add(1.0);
        c.add(2.0);
        CHECK(c.size() == 3);
    }

    SUBCASE("Remove existing and non-existing") {
        c.add(10.0);
        c.add(20.0);
        CHECK_NOTHROW(c.remove(10.0));
        CHECK_THROWS_AS(c.remove(99.0), ElementNotFound);
    }

    SUBCASE("Access elements via at()") {
        c.add(7.0);
        CHECK(c.at(0) == doctest::Approx(7.0));
        CHECK_THROWS_AS(c.at(10), OutOfRange);
    }

    SUBCASE("Contains check") {
        c.add(5.0);
        CHECK(c.contains(5.0));
        CHECK_FALSE(c.contains(100.0));
    }

    SUBCASE("Copy constructor and assignment") {
        c.add(1.0);
        c.add(2.0);
        MyContainer<double> copy(c);
        CHECK(copy.size() == 2);
        CHECK(copy.contains(1.0));

        MyContainer<double> assign;
        assign = c;
        CHECK(assign.size() == 2);
        CHECK(assign.contains(2.0));
    }

    SUBCASE("Operator <<") {
        c.add(4.0);
        c.add(5.0);
        std::ostringstream oss;
        oss << c;
        CHECK(oss.str().find("[") == 0);
    }

    SUBCASE("Iterators: generic usage") {
        c.add(1.0);
        c.add(2.0);
        c.add(3.0);

        int count = 0;
        for (auto it = c.begin(); it != c.end(); ++it)
            ++count;
        CHECK(count == 3);
    }

    SUBCASE("All iterators produce expected order") {
        c.add(1.0);
        c.add(2.0);
        c.add(3.0);
        c.add(4.0);
        c.add(5.0);

        std::vector<double> expected;

        SUBCASE("Order") {
            expected = {1.0, 2.0, 3.0, 4.0, 5.0};
            int i = 0;
            for (auto it = c.beginOrder(); it != c.endOrder(); ++it)
                CHECK(*it == doctest::Approx(expected[i++]));
        }

        SUBCASE("Reverse") {
            expected = {5.0, 4.0, 3.0, 2.0, 1.0};
            int i = 0;
            for (auto it = c.beginReverseOrder(); it != c.endReverseOrder(); ++it)
                CHECK(*it == doctest::Approx(expected[i++]));
        }

        SUBCASE("Ascending") {
            expected = {1.0, 2.0, 3.0, 4.0, 5.0};
            int i = 0;
            for (auto it = c.beginAscendingOrder(); it != c.endAscendingOrder(); ++it)
                CHECK(*it == doctest::Approx(expected[i++]));
        }

        SUBCASE("Descending") {
            expected = {5.0, 4.0, 3.0, 2.0, 1.0};
            int i = 0;
            for (auto it = c.beginDescendingOrder(); it != c.endDescendingOrder(); ++it)
                CHECK(*it == doctest::Approx(expected[i++]));
        }

        SUBCASE("SideCross") {
            expected = {1.0, 5.0, 2.0, 4.0, 3.0};
            int i = 0;
            for (auto it = c.beginSideCrossOrder(); it != c.endSideCrossOrder(); ++it)
                CHECK(*it == doctest::Approx(expected[i++]));
        }

        SUBCASE("MiddleOut") {
            expected = {3.0, 4.0, 2.0, 5.0, 1.0};
            int i = 0;
            for (auto it = c.beginMiddleOutOrder(); it != c.endMiddleOutOrder(); ++it)
                CHECK(*it == doctest::Approx(expected[i++]));
        }
    }

    SUBCASE("Iterator operations: ++, --, ==, !=, *") {
        c.add(10.0);
        c.add(20.0);
        c.add(30.0);

        auto it1 = c.beginOrder();
        auto it2 = it1;
        ++it2;
        CHECK(it1 != it2);
        CHECK(*it2 == doctest::Approx(20.0));
        --it2;
        CHECK(it1 == it2);
    }

    SUBCASE("Iterator operator[] and ->") {
        c.add(100.0);
        c.add(200.0);
        auto it = c.beginOrder();
        CHECK(it[1] == doctest::Approx(200.0));
        CHECK(*it == doctest::Approx(100.0));
    }

    SUBCASE("Remove all duplicates") {
        c.add(5.0);
        c.add(5.0);
        c.add(5.0);
        CHECK(c.size() == 3);
        c.remove(5.0);
        CHECK(c.isEmpty());
        CHECK_THROWS_AS(c.remove(5.0), ElementNotFound);
    }

    SUBCASE("Remove from empty container") {
        CHECK_THROWS_AS(c.remove(10.0), ElementNotFound);
    }

    SUBCASE("at() throws when container empty") {
        CHECK_THROWS_AS(c.at(0), ContainerEmpty);
    }

    SUBCASE("at() throws for out-of-range") {
        c.add(1.0);
        CHECK_THROWS_AS(c.at(5), OutOfRange);
    }

    SUBCASE("Iterator increment past end throws") {
        c.add(1.0);
        auto it = c.begin();
        ++it; // now at the end
        CHECK_THROWS_AS(++it, OutOfRange);
    }

    SUBCASE("Iterator decrement before begin throws") {
        c.add(1.0);
        auto it = c.begin();
        CHECK_THROWS_AS(--it, OutOfRange);
    }

    SUBCASE("Iterator dereference end throws") {
        c.add(1.0);
        auto it = c.end();
        CHECK_THROWS_AS(*it, OutOfRange);
    }

    SUBCASE("Self-assignment") {
        c.add(10.0);
        c.add(20.0);
        c = c;
        CHECK(c.size() == 2);
        CHECK(c.contains(10.0));
        CHECK(c.contains(20.0));
    }

    SUBCASE("Assign empty to non-empty") {
        MyContainer<double> c2;
        c.add(1.0);
        c2 = c;
        c = MyContainer<double>(); // assign empty
        CHECK(c.isEmpty());
    }

    SUBCASE("Large add and remove") {
        const int large_size = 10000;
        for (int i = 0; i < large_size; ++i) {
            c.add(static_cast<double>(i));
        }
        CHECK(c.size() == large_size);
        for (int i = 0; i < large_size; ++i) {
            c.remove(static_cast<double>(i));
        }
        CHECK(c.isEmpty());
    }

    SUBCASE("Const correctness") {
        c.add(1.0);
        const MyContainer<double> &cc = c;
        CHECK(cc.size() == 1);
        CHECK_FALSE(cc.isEmpty());
        CHECK(cc.contains(1.0));
    }

    SUBCASE("Iterator on empty container") {
        CHECK(c.begin() == c.end());
    }
}

//////// CHAR CONTAINER TESTS //////////
TEST_CASE("MyContainer<char>") {
    MyContainer<char> c;

    SUBCASE("Default constructor") {
        CHECK(c.size() == 0);
        CHECK(c.isEmpty());
    }

    SUBCASE("Add with duplicates") {
        c.add('a');
        c.add('a');
        c.add('b');
        CHECK(c.size() == 3);
    }

    SUBCASE("Remove existing and non-existing") {
        c.add('x');
        c.add('y');
        CHECK_NOTHROW(c.remove('x'));
        CHECK_THROWS_AS(c.remove('z'), ElementNotFound);
    }

    SUBCASE("Access elements via at()") {
        c.add('m');
        CHECK(c.at(0) == 'm');
        CHECK_THROWS_AS(c.at(10), OutOfRange);
    }

    SUBCASE("Contains check") {
        c.add('k');
        CHECK(c.contains('k'));
        CHECK_FALSE(c.contains('q'));
    }

    SUBCASE("Copy constructor and assignment") {
        c.add('p');
        c.add('q');
        MyContainer<char> copy(c);
        CHECK(copy.size() == 2);
        CHECK(copy.contains('p'));

        MyContainer<char> assign;
        assign = c;
        CHECK(assign.size() == 2);
        CHECK(assign.contains('q'));
    }

    SUBCASE("Operator <<") {
        c.add('d');
        c.add('e');
        std::ostringstream oss;
        oss << c;
        CHECK(oss.str() == "[d, e]");
    }

    SUBCASE("Iterators: generic usage") {
        c.add('a');
        c.add('b');
        c.add('c');

        int count = 0;
        for (auto it = c.begin(); it != c.end(); ++it)
            ++count;
        CHECK(count == 3);
    }

    SUBCASE("All iterators produce expected order") {
        c.add('a');
        c.add('b');
        c.add('c');
        c.add('d');
        c.add('e');

        std::vector<char> expected;

        SUBCASE("Order") {
            expected = {'a', 'b', 'c', 'd', 'e'};
            int i = 0;
            for (auto it = c.beginOrder(); it != c.endOrder(); ++it)
                CHECK(*it == expected[i++]);
        }

        SUBCASE("Reverse") {
            expected = {'e', 'd', 'c', 'b', 'a'};
            int i = 0;
            for (auto it = c.beginReverseOrder(); it != c.endReverseOrder(); ++it)
                CHECK(*it == expected[i++]);
        }

        SUBCASE("Ascending") {
            expected = {'a', 'b', 'c', 'd', 'e'};
            int i = 0;
            for (auto it = c.beginAscendingOrder(); it != c.endAscendingOrder(); ++it)
                CHECK(*it == expected[i++]);
        }

        SUBCASE("Descending") {
            expected = {'e', 'd', 'c', 'b', 'a'};
            int i = 0;
            for (auto it = c.beginDescendingOrder(); it != c.endDescendingOrder(); ++it)
                CHECK(*it == expected[i++]);
        }

        SUBCASE("SideCross") {
            expected = {'a', 'e', 'b', 'd', 'c'};
            int i = 0;
            for (auto it = c.beginSideCrossOrder(); it != c.endSideCrossOrder(); ++it)
                CHECK(*it == expected[i++]);
        }

        SUBCASE("MiddleOut") {
            expected = {'c', 'd', 'b', 'e', 'a'};
            int i = 0;
            for (auto it = c.beginMiddleOutOrder(); it != c.endMiddleOutOrder(); ++it)
                CHECK(*it == expected[i++]);
        }
    }

    SUBCASE("Iterator operations: ++, --, ==, !=, *") {
        c.add('x');
        c.add('y');
        c.add('z');

        auto it1 = c.beginOrder();
        auto it2 = it1;
        ++it2;
        CHECK(it1 != it2);
        CHECK(*it2 == 'y');
        --it2;
        CHECK(it1 == it2);
    }

    SUBCASE("Iterator operator[] and ->") {
        c.add('u');
        c.add('v');
        auto it = c.beginOrder();
        CHECK(it[1] == 'v');
        CHECK(*it == 'u');
    }

    SUBCASE("Remove all duplicates") {
        c.add('g');
        c.add('g');
        c.add('g');
        CHECK(c.size() == 3);
        c.remove('g');
        CHECK(c.isEmpty());
        CHECK_THROWS_AS(c.remove('g'), ElementNotFound);
    }

    SUBCASE("Remove from empty container") {
        CHECK_THROWS_AS(c.remove('a'), ElementNotFound);
    }

    SUBCASE("at() throws when container empty") {
        CHECK_THROWS_AS(c.at(0), ContainerEmpty);
    }

    SUBCASE("at() throws for out-of-range") {
        c.add('b');
        CHECK_THROWS_AS(c.at(5), OutOfRange);
    }

    SUBCASE("Iterator increment past end throws") {
        c.add('c');
        auto it = c.begin();
        ++it; // now at the end
        CHECK_THROWS_AS(++it, OutOfRange);
    }

    SUBCASE("Iterator decrement before begin throws") {
        c.add('d');
        auto it = c.begin();
        CHECK_THROWS_AS(--it, OutOfRange);
    }

    SUBCASE("Iterator dereference end throws") {
        c.add('e');
        auto it = c.end();
        CHECK_THROWS_AS(*it, OutOfRange);
    }

    SUBCASE("Self-assignment") {
        c.add('f');
        c.add('g');
        c = c;
        CHECK(c.size() == 2);
        CHECK(c.contains('f'));
        CHECK(c.contains('g'));
    }

    SUBCASE("Assign empty to non-empty") {
        MyContainer<char> c2;
        c.add('h');
        c2 = c;
        c = MyContainer<char>(); // assign empty
        CHECK(c.isEmpty());
    }

    SUBCASE("Large add and remove (small alphabet)") {
        // Add 10,000 chars (repeating 'a' through 'z')
        const int large_size = 10000;
        for (int i = 0; i < large_size; ++i) {
            c.add(static_cast<char>('a' + (i % 26)));
        }
        CHECK(c.size() == large_size);

        // Remove each letter exactly once:
        for (char ch = 'a'; ch <= 'z'; ++ch) {
            CHECK_NOTHROW(c.remove(ch));  // each remove wipes out all copies of that letter
        }
        CHECK(c.isEmpty());
    }


    SUBCASE("Const correctness") {
        c.add('j');
        const MyContainer<char> &cc = c;
        CHECK(cc.size() == 1);
        CHECK_FALSE(cc.isEmpty());
        CHECK(cc.contains('j'));
    }

    SUBCASE("Iterator on empty container") {
        CHECK(c.begin() == c.end());
    }
}


//////// STRING CONTAINER TESTS //////////
TEST_CASE("MyContainer<string>") {
    MyContainer<std::string> c;

    SUBCASE("Default constructor") {
        CHECK(c.size() == 0);
        CHECK(c.isEmpty());
    }

    SUBCASE("Add with duplicates") {
        c.add("apple");
        c.add("apple");
        c.add("banana");
        CHECK(c.size() == 3);
    }

    SUBCASE("Remove existing and non-existing") {
        c.add("x");
        c.add("y");
        CHECK_NOTHROW(c.remove("x"));
        CHECK_THROWS_AS(c.remove("z"), ElementNotFound);
    }

    SUBCASE("Access elements via at()") {
        c.add("hello");
        CHECK(c.at(0) == "hello");
        CHECK_THROWS_AS(c.at(10), OutOfRange);
    }

    SUBCASE("Contains check") {
        c.add("foo");
        CHECK(c.contains("foo"));
        CHECK_FALSE(c.contains("bar"));
    }

    SUBCASE("Copy constructor and assignment") {
        c.add("one");
        c.add("two");
        MyContainer<std::string> copy(c);
        CHECK(copy.size() == 2);
        CHECK(copy.contains("one"));

        MyContainer<std::string> assign;
        assign = c;
        CHECK(assign.size() == 2);
        CHECK(assign.contains("two"));
    }

    SUBCASE("Operator <<") {
        c.add("dog");
        c.add("cat");
        std::ostringstream oss;
        oss << c;
        CHECK(oss.str() == "[dog, cat]");
    }

    SUBCASE("Iterators: generic usage") {
        c.add("a");
        c.add("b");
        c.add("c");

        int count = 0;
        for (auto it = c.begin(); it != c.end(); ++it)
            ++count;
        CHECK(count == 3);
    }

    SUBCASE("All iterators produce expected order") {
        c.add("apple");   // insertion order index 0
        c.add("banana");  // index 1
        c.add("cherry");  // index 2
        c.add("date");    // index 3
        c.add("fig");     // index 4

        std::vector<std::string> expected;

        SUBCASE("Order") {
            expected = {"apple", "banana", "cherry", "date", "fig"};
            int i = 0;
            for (auto it = c.beginOrder(); it != c.endOrder(); ++it)
                CHECK(*it == expected[i++]);
        }

        SUBCASE("Reverse") {
            expected = {"fig", "date", "cherry", "banana", "apple"};
            int i = 0;
            for (auto it = c.beginReverseOrder(); it != c.endReverseOrder(); ++it)
                CHECK(*it == expected[i++]);
        }

        SUBCASE("Ascending") {
            // Lexicographically sorted: "apple", "banana", "cherry", "date", "fig"
            expected = {"apple", "banana", "cherry", "date", "fig"};
            int i = 0;
            for (auto it = c.beginAscendingOrder(); it != c.endAscendingOrder(); ++it)
                CHECK(*it == expected[i++]);
        }

        SUBCASE("Descending") {
            // Reverse lex order: "fig", "date", "cherry", "banana", "apple"
            expected = {"fig", "date", "cherry", "banana", "apple"};
            int i = 0;
            for (auto it = c.beginDescendingOrder(); it != c.endDescendingOrder(); ++it)
                CHECK(*it == expected[i++]);
        }

        SUBCASE("SideCross") {
            // Sorted ascending = ["apple","banana","cherry","date","fig"]
            // side-cross pick: "apple", "fig", "banana", "date", "cherry"
            expected = {"apple", "fig", "banana", "date", "cherry"};
            int i = 0;
            for (auto it = c.beginSideCrossOrder(); it != c.endSideCrossOrder(); ++it)
                CHECK(*it == expected[i++]);
        }

        SUBCASE("MiddleOut") {
            // Original insertion = ["apple","banana","cherry","date","fig"]
            // middle index = 2 ("cherry"), then right ("date"), left ("banana"), right ("fig"), left ("apple")
            expected = {"cherry", "date", "banana", "fig", "apple"};
            int i = 0;
            for (auto it = c.beginMiddleOutOrder(); it != c.endMiddleOutOrder(); ++it)
                CHECK(*it == expected[i++]);
        }
    }

    SUBCASE("Iterator operations: ++, --, ==, !=, *") {
        c.add("x");
        c.add("y");
        c.add("z");

        auto it1 = c.beginOrder();
        auto it2 = it1;
        ++it2;
        CHECK(it1 != it2);
        CHECK(*it2 == "y");
        --it2;
        CHECK(it1 == it2);
    }

    SUBCASE("Iterator operator[] and ->") {
        c.add("foo");
        c.add("bar");
        auto it = c.beginOrder();
        CHECK(it[1] == "bar");
        CHECK(*it == "foo");
    }

    SUBCASE("Remove all duplicates") {
        c.add("dup");
        c.add("dup");
        c.add("dup");
        CHECK(c.size() == 3);
        c.remove("dup");
        CHECK(c.isEmpty());
        CHECK_THROWS_AS(c.remove("dup"), ElementNotFound);
    }

    SUBCASE("Remove from empty container") {
        CHECK_THROWS_AS(c.remove("nothing"), ElementNotFound);
    }

    SUBCASE("at() throws when container empty") {
        CHECK_THROWS_AS(c.at(0), ContainerEmpty);
    }

    SUBCASE("at() throws for out-of-range") {
        c.add("hello");
        CHECK_THROWS_AS(c.at(5), OutOfRange);
    }

    SUBCASE("Iterator increment past end throws") {
        c.add("a");
        auto it = c.begin();
        ++it; // now at the end
        CHECK_THROWS_AS(++it, OutOfRange);
    }

    SUBCASE("Iterator decrement before begin throws") {
        c.add("b");
        auto it = c.begin();
        CHECK_THROWS_AS(--it, OutOfRange);
    }

    SUBCASE("Iterator dereference end throws") {
        c.add("c");
        auto it = c.end();
        CHECK_THROWS_AS(*it, OutOfRange);
    }

    SUBCASE("Self-assignment") {
        c.add("p");
        c.add("q");
        c = c;
        CHECK(c.size() == 2);
        CHECK(c.contains("p"));
        CHECK(c.contains("q"));
    }

    SUBCASE("Assign empty to non-empty") {
        MyContainer<std::string> c2;
        c.add("alpha");
        c2 = c;
        c = MyContainer<std::string>(); // assign empty
        CHECK(c.isEmpty());
    }

    SUBCASE("Large add and remove (distinct strings)") {
        const int distinct = 100;
        for (int i = 0; i < distinct; ++i) {
            c.add(std::to_string(i));
        }
        CHECK(c.size() == distinct);
        for (int i = 0; i < distinct; ++i) {
            CHECK_NOTHROW(c.remove(std::to_string(i)));
        }
        CHECK(c.isEmpty());
    }

    SUBCASE("Const correctness") {
        c.add("const_test");
        const MyContainer<std::string>& cc = c;
        CHECK(cc.size() == 1);
        CHECK_FALSE(cc.isEmpty());
        CHECK(cc.contains("const_test"));
    }

    SUBCASE("Iterator on empty container") {
        CHECK(c.begin() == c.end());
    }
}

/// //////// PEOPLE CONTAINER TESTS //////////
TEST_CASE("MyContainer<People>") {
    //
    // Original subtests you already had:
    //
    MyContainer<People> c;  // a fresh container for each SUBCASE

    SUBCASE("Add & contains") {
        People a("Alice", 30), b("Bob", 25);
        c.add(a);
        c.add(b);
        CHECK(c.size() == 2);
        CHECK(c.contains(People("Alice", 30)));
        CHECK_FALSE(c.contains(People("Charlie", 40)));
    }

    SUBCASE("Remove & exceptions") {
        c.add({ "X", 50 });
        CHECK_NOTHROW(c.remove({ "X", 50 }));
        // now empty:
        CHECK_THROWS_AS(c.remove({ "X", 50 }), ElementNotFound);
    }

    SUBCASE("at() and OutOfRange") {
        c.add({ "Solo", 99 });
        CHECK(c.at(0).getName() == "Solo");
        CHECK_THROWS_AS(c.at(1), OutOfRange);
    }

    SUBCASE("Iterator orders") {
        c.add({ "A", 10 });
        c.add({ "B", 20 });
        c.add({ "C", 30 });
        // insertion order = A,B,C
        std::vector<People> ins = { { "A",10 },{ "B",20 },{ "C",30 } };
        int idx = 0;
        for (auto it = c.beginOrder(); it != c.endOrder(); ++it)
            CHECK(*it == ins[idx++]);

        // reverse = C,B,A
        idx = 0;
        std::vector<People> rev = { { "C",30 },{ "B",20 },{ "A",10 } };
        for (auto it = c.beginReverseOrder(); it != c.endReverseOrder(); ++it)
            CHECK(*it == rev[idx++]);

        // ascending (by age→name): A(10), B(20), C(30)
        idx = 0;
        std::vector<People> asc = { { "A",10 },{ "B",20 },{ "C",30 } };
        for (auto it = c.beginAscendingOrder(); it != c.endAscendingOrder(); ++it)
            CHECK(*it == asc[idx++]);

        // descending: C(30), B(20), A(10)
        idx = 0;
        std::vector<People> desc = { { "C",30 },{ "B",20 },{ "A",10 } };
        for (auto it = c.beginDescendingOrder(); it != c.endDescendingOrder(); ++it)
            CHECK(*it == desc[idx++]);
    }

    SUBCASE("Operator<< prints them") {
        c.add({ "Dave", 45 });
        c.add({ "Eve", 35 });
        std::ostringstream oss;
        oss << c;
        // We only check substrings; exact formatting might include commas/spaces.
        std::string out = oss.str();
        CHECK(out.find("Name: Dave, Age: 45") != std::string::npos);
        CHECK(out.find("Name: Eve, Age: 35")  != std::string::npos);
    }


    //
    // Additional subtests as requested:
    //

    SUBCASE("People class: equality, inequality, and operator<") {
        People p1("Ann", 20);
        People p2("Ben", 20);
        People p3("Ann", 25);

        // same name and age => equal
        CHECK(p1 == People("Ann", 20));
        CHECK_FALSE(p1 != People("Ann", 20));


        CHECK_FALSE(p1 < p2);
        CHECK(p1 <= p2);
        CHECK_FALSE(p2 < p1);
        CHECK(p2 <= p1);


        // different age => younger < older
        CHECK(p2 < p3);
        CHECK_FALSE(p3 < p2);

        // inequality checks
        CHECK(p1 != p2);
        CHECK(p1 != p3);
    }

    SUBCASE("Copy‐and‐assignment semantics of MyContainer<People>") {
        MyContainer<People> original;
        original.add({ "Alex", 30 });

        // Copy-construct
        MyContainer<People> copyConstructed = original;
        CHECK(copyConstructed.size() == 1);
        CHECK(copyConstructed.contains({ "Alex", 30 }));

        // Mutate the copy → original remains unchanged
        copyConstructed.add({ "Blake", 40 });
        CHECK(copyConstructed.size() == 2);
        CHECK(original.size() == 1);

        // Assignment operator
        MyContainer<People> assigned;
        assigned.add({ "Carl", 50 });
        assigned = original;
        CHECK(assigned.size() == 1);
        CHECK(assigned.contains({ "Alex", 30 }));
        // Mutate 'assigned' should not affect 'original'
        assigned.remove({ "Alex", 30 });
        CHECK(assigned.size() == 0);
        CHECK(original.size() == 1);
    }

    SUBCASE("Empty‐container behavior") {
        MyContainer<People> emptyContainer;
        // size() should be 0
        CHECK(emptyContainer.size() == 0);

        // contains() on any People returns false
        CHECK_FALSE(emptyContainer.contains({ "Nobody", 0 }));


        CHECK_THROWS(emptyContainer.at(0));

        // Instead of checking begin()==end(), verify that iterating visits zero elements:
        {
            int count = 0;
            for (auto it = emptyContainer.beginOrder(); it != emptyContainer.endOrder(); ++it) {
                ++count;
            }
            CHECK(count == 0);
        }
        {
            int count = 0;
            for (auto it = emptyContainer.beginAscendingOrder(); it != emptyContainer.endAscendingOrder(); ++it) {
                ++count;
            }
            CHECK(count == 0);
        }
        {
            int count = 0;
            for (auto it = emptyContainer.beginReverseOrder(); it != emptyContainer.endReverseOrder(); ++it) {
                ++count;
            }
            CHECK(count == 0);
        }
        {
            int count = 0;
            for (auto it = emptyContainer.beginDescendingOrder(); it != emptyContainer.endDescendingOrder(); ++it) {
                ++count;
            }
            CHECK(count == 0);
        }

        // operator<< on an empty container should produce exactly "[]"
        std::ostringstream oss;
        oss << emptyContainer;
        CHECK(oss.str() == "[]");
    }


    SUBCASE("Ascending‐order tie‐breaking: same age → insertion order") {
        MyContainer<People> tieTest;
        tieTest.add({ "Zoe", 25 });
        tieTest.add({ "Amy", 25 });
        tieTest.add({ "Mike", 20 });
        tieTest.add({ "Ben", 25 });

        // Expected ascending order:
        //   1) Mike(20)
        //   2) Zoe(25)   (because Zoe was added first among age=25)
        //   3) Amy(25)
        //   4) Ben(25)
        std::vector<People> expected = {
            { "Mike", 20 },
            { "Zoe", 25 },
            { "Amy", 25 },
            { "Ben", 25 }
        };

        int idx = 0;
        for (auto it = tieTest.beginAscendingOrder(); it != tieTest.endAscendingOrder(); ++it) {
            CHECK(*it == expected[idx++]);
        }
        CHECK(idx == static_cast<int>(expected.size()));
    }


    SUBCASE("Removal shifts indices and at() changes") {
        MyContainer<People> removeTest;
        removeTest.add({ "A", 10 });
        removeTest.add({ "B", 20 });
        removeTest.add({ "C", 30 });
        removeTest.add({ "D", 40 });

        // initial insertion order: A, B, C, D
        CHECK(removeTest.at(0).getName() == "A");
        CHECK(removeTest.at(1).getName() == "B");
        CHECK(removeTest.at(2).getName() == "C");
        CHECK(removeTest.at(3).getName() == "D");

        // remove middle element ("B")
        CHECK_NOTHROW(removeTest.remove({ "B", 20 }));
        // now order should be A, C, D
        CHECK(removeTest.size() == 3);
        CHECK(removeTest.at(0).getName() == "A");
        CHECK(removeTest.at(1).getName() == "C");
        CHECK(removeTest.at(2).getName() == "D");

        // remove first element ("A")
        CHECK_NOTHROW(removeTest.remove({ "A", 10 }));
        // now order: C, D
        CHECK(removeTest.size() == 2);
        CHECK(removeTest.at(0).getName() == "C");
        CHECK(removeTest.at(1).getName() == "D");

        // Removing something that doesn’t exist now throws ElementNotFound
        CHECK_THROWS_AS(removeTest.remove({ "B", 20 }), ElementNotFound);
        CHECK_THROWS_AS(removeTest.remove({ "X", 99 }), ElementNotFound);

        // at(2) should throw OutOfRange
        CHECK_THROWS_AS(removeTest.at(2), OutOfRange);
    }

    SUBCASE("Operator<< prints multiple elements in insertion order") {
        MyContainer<People> streamTest;
        streamTest.add({ "Dave", 45 });
        streamTest.add({ "Eve", 35 });
        streamTest.add({ "Frank", 50 });

        std::ostringstream oss;
        oss << streamTest;
        std::string out = oss.str();

        // It must start with "[" and end with "]"
        CHECK(!out.empty());
        CHECK(out.front() == '[');
        CHECK(out.back() == ']');

        // Must contain each "Name: <X>, Age: <Y>" in insertion order
        auto posDave  = out.find("Name: Dave, Age: 45");
        auto posEve   = out.find("Name: Eve, Age: 35");
        auto posFrank = out.find("Name: Frank, Age: 50");

        CHECK(posDave  != std::string::npos);
        CHECK(posEve   != std::string::npos);
        CHECK(posFrank != std::string::npos);

        // Dave must appear before Eve, and Eve before Frank
        CHECK(posDave < posEve);
        CHECK(posEve < posFrank);
    }
}