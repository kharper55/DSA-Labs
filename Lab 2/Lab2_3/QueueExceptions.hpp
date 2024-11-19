#ifndef QUEUE_EXCEPTIONS_HPP
#define QUEUE_EXCEPTIONS_HPP

#include <string>                 
#include <stdexcept>

using namespace std;

// Exception thrown on empty linked lists.
class QueueEmpty : public std::runtime_error {  
    public:
        QueueEmpty(const string& err) : runtime_error(err) { }
};

#endif // QUEUE_EXCEPTIONS_HPP