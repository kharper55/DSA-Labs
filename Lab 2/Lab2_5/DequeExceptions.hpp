#ifndef DEQUE_EXCEPTIONS_HPP
#define DEQUE_EXCEPTIONS_HPP

#include <string>                 
#include <stdexcept>

using namespace std;

// Exception thrown on empty linked lists.
class DequeEmpty : public std::runtime_error {  
    public:
        DequeEmpty(const string& err) : runtime_error(err) { }
};

#endif // DEQUE_EXCEPTIONS_HPP