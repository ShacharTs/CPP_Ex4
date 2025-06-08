#pragma once
#include <iostream>
using namespace std;
namespace PeopleClass {
    class People {
        string name;
        size_t age;
    public:
        People(string name, int age);
        People();

        ~People();
        People(const People& other);
        People& operator=(const People& other);
        int getAge() const;
        string getName() const;
        bool operator==(const People& other) const;
        bool operator!=(const People& other) const;
        bool operator<(const People& other) const;
        bool operator>(const People& other) const;
        bool operator<=(const People& other) const;
        bool operator>=(const People& other) const;

        friend std::ostream& operator<<(std::ostream& os, const People& p) {
            os << "Name: " << p.name << ", Age: " << p.age;
            return os;
        }


    };
}



