#ifndef BINARY_TREE_EXCEPTIONS_HPP
#define BINARY_TREE_EXCEPTIONS_HPP

#include <string>                 
#include <stdexcept>

using namespace std;

// Exception thrown on nonexistent element.
class NonexistentElement : public std::runtime_error {  
    public:
        NonexistentElement(const string& err) : runtime_error(err) {}
};

class BoundaryViolation : public std::runtime_error {  
    public:
        BoundaryViolation(const string& err) : runtime_error(err) {}
};

#endif // BINARY_TREE_EXCEPTIONS_HPP