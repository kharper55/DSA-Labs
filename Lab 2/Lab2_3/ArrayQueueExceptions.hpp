#ifndef ARRAY_QUEUE_EXCEPTIONS_HPP
#define ARRAY_QUEUE_EXCEPTIONS_HPP

#include <string>                 
#include <stdexcept>

using namespace std;

class QueueFull : public std::runtime_error {  
    public:
        QueueFull(const string& err) : runtime_error(err) {}
};

#endif // ARRAY_QUEUE_EXCEPTIONS_HPP