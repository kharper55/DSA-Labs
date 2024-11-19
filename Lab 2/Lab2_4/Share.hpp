#ifndef SHARE_HPP
#define SHARE_HPP

#include <cstdint>
#include <ostream>

class Share {				// Shares of a particular stock
    public:
        Share() : numShares(0), pricePerShare(0) {}
        Share(const uint32_t num, const double price) : numShares(num), pricePerShare(price) {}
        const bool modifyNumShares(const uint32_t taken);// const;
        const uint32_t getNumShares() const { return numShares; }
        const double getPrice() const { return pricePerShare; }
        // Overload the << operator as a non-member function
        friend std::ostream& operator<<(std::ostream& os, const Share& share) {
            os << "Shares: " << share.numShares << ", Price per Share: $" << share.pricePerShare;
            return os;
        }
    
    private:					// member data
        uint32_t numShares;
        double pricePerShare;   
};

const bool Share::modifyNumShares(const uint32_t taken) {//const { 
    if (numShares - taken >= 0) {
        numShares -= taken; 
        return true;
    }
    else return false;
}

#endif // SHARE_HPP