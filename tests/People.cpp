#include "People.hpp"

PeopleClass::People::People(std::string name, int age)
  : name(std::move(name)), age(age)
{}

PeopleClass::People::People()
  : name(""), age(0)
{}

PeopleClass::People::~People() = default;

PeopleClass::People::People(const People& other)
  : name(other.name), age(other.age)
{}

PeopleClass::People& PeopleClass::People::operator=(const People& other) {
    if (this != &other) {
        name = other.name;
        age  = other.age;
    }
    return *this;
}

int PeopleClass::People::getAge() const {
    return static_cast<int>(age);
}

std::string PeopleClass::People::getName() const {
    return name;
}

bool PeopleClass::People::operator==(const PeopleClass::People& other) const {
    return name == other.name && age == other.age;
}

bool PeopleClass::People::operator!=(const PeopleClass::People& other) const {
    return !(*this == other);
}

bool PeopleClass::People::operator<(const PeopleClass::People& other) const {
    return age < other.age;
}

bool PeopleClass::People::operator>(const PeopleClass::People& other) const {
    return age > other.age;
}

bool PeopleClass::People::operator<=(const PeopleClass::People& other) const {
    return age <= other.age;
}

bool PeopleClass::People::operator>=(const PeopleClass::People& other) const {
    return age >= other.age;
}
