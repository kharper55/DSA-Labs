#ifndef LINKED_LIST_EXCEPTIONS_HPP
#define LINKED_LIST_EXCEPTIONS_HPP

#include <string>                 
#include <stdexcept>

using namespace std;

// Exception thrown on empty linked lists.
class LinkedListEmpty : public std::runtime_error {  
    public:
        LinkedListEmpty(const string& err) : runtime_error(err) {}
};

#endif // LINKED_LIST_EXCEPTIONS_HPP