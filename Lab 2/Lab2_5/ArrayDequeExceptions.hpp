#ifndef ARRAY_DEQUE_EXCEPTIONS_HPP
#define ARRAY_DEQUE_EXCEPTIONS_HPP

#include <string>                 
#include <stdexcept>

using namespace std;

class DequeFull : public std::runtime_error {  
    public:
        DequeFull(const string& err) : runtime_error(err) {}
};

#endif // ARRAY_DEQUE_EXCEPTIONS_HPP