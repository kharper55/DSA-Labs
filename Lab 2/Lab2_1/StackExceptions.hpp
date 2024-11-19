#ifndef STACK_EXCEPTIONS_HPP
#define STACK_EXCEPTIONS_HPP

#include <string>                 
#include <stdexcept>

using namespace std;

// Exception thrown on performing top or pop of an empty stack.
class StackEmpty : public std::runtime_error {  
    public:
        StackEmpty(const string& err) : runtime_error(err) {}
};

#endif // STACK_EXCEPTIONS_HPP