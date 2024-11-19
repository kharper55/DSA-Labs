#ifndef TEAM_MEMBER_HPP
#define TEAM_MEMBER_HPP

#include <string>   // For string class
#include <cstdint>  // For unsigned integers

using namespace std;

class TeamMember {
    public:
        TeamMember() : name(DEFAULT_NAME), number(DEFAULT_NUM) {}           // Default constructor
        TeamMember(const string& name, const int num = DEFAULT_NUM) : name(name), number(num) {} // Parametrized constructors
        const string& getName() const;
        const uint8_t getNumber() const;
    private:
        const string name;
        const uint8_t number;
        const static string DEFAULT_NAME;
        const static int DEFAULT_NUM = 0;
};

const string TeamMember::DEFAULT_NAME = ""; // Initialize static string member

const string& TeamMember::getName() const {
    return name;
}

const uint8_t TeamMember::getNumber() const {
    return number;
}

#endif // TEAM_MEMBER_HPP