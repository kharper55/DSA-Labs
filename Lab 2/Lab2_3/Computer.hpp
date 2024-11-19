#ifndef COMPUTER_HPP
#define COMPUTER_HPP

#include <string>   // For string class
#include <cstdint>  // For unsigned integers

using namespace std;

class Computer {
    public:
        Computer() : name(DEFAULT_NAME), network(DEFAULT_NETWORK) {}           // Default constructor
        Computer(const string& name, const string& network) : 
            name(name), network(network) {} // Parametrized constructors
        const string& getName() const;
        const string& getNetwork() const;
        void changeNetwork(const string& newNetwork);

        friend ostream& operator<<(ostream& os, const Computer& computer);
    
    private:
        string name;
        string network;
        const static string DEFAULT_NAME;
        const static string DEFAULT_NETWORK;
};

const string Computer::DEFAULT_NAME = "DEFAULT NAME"; // Initialize static string member
const string Computer::DEFAULT_NETWORK = "DEFAULT NETWORK"; // Initialize static string member

const string& Computer::getName() const {
    return name;
}

const string& Computer::getNetwork() const {
    return network;
}

void Computer::changeNetwork(const string& newNetwork) {
    network = newNetwork;
}

// Define the << operator overload
ostream& operator<<(ostream& os, const Computer& computer) {
    os << "Computer Name: " << computer.getName() 
       << ", Network: " << computer.getNetwork();
    return os;
}

#endif // COMPUTER_HPP