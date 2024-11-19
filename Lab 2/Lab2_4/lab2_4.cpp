/* ============================================================================
lab1.cpp

Desc:   Lab 1 for datastructures and algorithms (CSCI2226)
Author: Kevin Harper
Date:   10/20/2024

NOTE: IN VSCODE, IF GDB IS THROWING ERROR 0xC0000139 DESPITE THE PROGRAM 
      SUCCESSFULLY BUILDING, YOU MUST GO TO SETTINGS AND CHANGE THE TERMINAL. 
      IN THE TERMINAL WINDOW, NAVIGATE TO THE "+" ICON WITH THE DROPDOWN ARROW,
      THEN SELECT CONFIGURE TERMINAL SETTINGS, NAVIGATE TO C:\msys64\ucrt64.exe 
      (FOR DEFAULT MSYS2 INSTALL SETTINGS) AND USE THIS EXECUTABLE PATH IN THE 
      SETTINGS WINDOW. THEN USE THE BUTTON ON THE BOTTOM OF THE VSCODE SCREEN
      "C/C++: g++.exe build and debug active file (PROJ_NAME)" TO BUILD AND
      DEBUG THE FILE IN THE NATIVE VSCODE TERMINAL.

============================================================================ */

// Library includes
#include <iostream>                 // For console interaction
#include <string>                   // For stoi
#include <cstring>                  // For strlen
#include <queue>                    // For STL queue
#include <random>                   // For random device and mersenne twister implementation
#include <cstdint>                  // for unsigned integers

// Header includes
#include "CircularQueue.hpp"
#include "ArrayQueue.hpp"
#include "Share.hpp"

using namespace std;

// Function prototypes
double capitalGainsSTL(queue<Share>& stockQueue, bool buySell, Share share);
double capitalGainsArray(ArrayQueue<Share>& stockQueue, bool buySell, Share share);
double capitalGainsLinked(CircularQueue<Share>& stockQueue, bool buySell, Share share);
void printCenteredTitle(const char * title, const int col_width);

// Constants
enum {
     SELL = 0,
     BUY
};

// Constants
const string DS_OPTIONS[3] = {
    "STL queue",
    "Array-based queue",
    "Circular linked list-based queue",
};

const char QUIT_CHAR = 'x';

enum {
    STL_QUEUE,
    ARRAY_QUEUE,
    LINKED_QUEUE
};

#define NUM_DAYS_BUY            5
#define COL_WIDTH               65
#define DEFAULT_NUM_SHARES_SELL 165
#define DEFAULT_SELL_PRICE      22.67

/* ============================================================================
main()
============================================================================ */
int main() {
      
     int numSharesSell = 500;
     double sellPrice = 30;

     queue<Share> stockQueueSTL;             // STL queue
     ArrayQueue<Share> stockQueueArray;      // Array-based queue
     CircularQueue<Share> stockQueueLinked;  // Circular linked list-based queue
     queue<Share> stockQueueSTLCopy;         // Copies of queue
     ArrayQueue<Share> stockQueueArrayCopy;     
     CircularQueue<Share> stockQueueLinkedCopy;

     random_device rd;
     mt19937 gen(rd());

     // Produces random integer/real values, uniformly distributed on the closed interval [a,b] (inclusive of endpoints)
     // https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
     uniform_int_distribution<uint32_t> numShares(15, 120);
     uniform_real_distribution<double> sharePrice(10, 35);

     char userChoice;    // Should make this a string and accept only the first char, discarding remainder
     bool userQuit = false;

     cout << "\nWelcome to capital gains demo!\n\n";

     // Buy stock and populate queues
     for (int i = 0; i < NUM_DAYS_BUY; i++) {
          Share randomShare(numShares(gen), sharePrice(gen));
          cout << "Day " << i + 1 << ": Buying " << randomShare.getNumShares() << " shares at $" << randomShare.getPrice() << " each.\n";
          capitalGainsSTL(stockQueueSTL, BUY, randomShare);
          capitalGainsArray(stockQueueArray, BUY, randomShare);
          capitalGainsLinked(stockQueueLinked, BUY, randomShare);
     }

     while(!userQuit) {
          printCenteredTitle(" Data structure selection ", COL_WIDTH);
          for (int i = 0; i < sizeof(DS_OPTIONS)/sizeof(DS_OPTIONS[0]); i++) {
               cout << static_cast<char>(0x61 + i) << ") " << DS_OPTIONS[i] << "\n";
          }
          printCenteredTitle(" Input ", COL_WIDTH);
          cout << "Select an implementation for capital gains (use '" << QUIT_CHAR << "' to quit): ";
          cin >> userChoice;
          if (userChoice != QUIT_CHAR) {
               int ds = static_cast<int>(userChoice - 0x61);
               switch(ds) {
                    case(STL_QUEUE): // STL queue 
                    {   
                         printCenteredTitle(" STL Queue ", COL_WIDTH);
                         // Populate queues with random shares (buy stock)
                         stockQueueSTLCopy = stockQueueSTL; // invoke copy constructor/operator overload
                         // Sell stock
                         //Share randomShare(numShares(gen), sharePrice(gen));
                         Share randomShare(DEFAULT_NUM_SHARES_SELL, DEFAULT_SELL_PRICE);
                         cout << "Selling " << randomShare.getNumShares() << " total shares at $" << randomShare.getPrice() << " each.\n";
                         double capitalGain = capitalGainsSTL(stockQueueSTLCopy, SELL, randomShare);
                         cout << "\nCapital Gains: " << ((capitalGain >= 0) ? "Gain of " : "Loss of ") << "$" << abs(capitalGain) << "\n";
                         break;
                    }
                    // Note: changed front() to return a modifiable node
                    case(ARRAY_QUEUE): // Array based queue
                    {   
                         printCenteredTitle(" Array-based Queue ", COL_WIDTH);
                         // Populate queues with random shares (buy stock)
                         stockQueueArrayCopy = stockQueueArray; // invoke copy constructor/operator overload
                         // Sell stock
                         //Share randomShare(numShares(gen), sharePrice(gen));
                         Share randomShare(DEFAULT_NUM_SHARES_SELL, DEFAULT_SELL_PRICE);
                         cout << "Selling " << randomShare.getNumShares() << " total shares at $" << randomShare.getPrice() << " each.\n";
                         double capitalGain = capitalGainsArray(stockQueueArrayCopy, SELL, randomShare);
                         cout << "\nCapital Gains: " << ((capitalGain >= 0) ? "Gain of " : "Loss of ") << "$" << abs(capitalGain) << "\n";
                         break;
                    }
                    // Note: changed front() to return a modifiable node
                    case(LINKED_QUEUE): // Circular linked list queue
                    {
                         printCenteredTitle(" Circular linked list-based Queue ", COL_WIDTH);
                         // Populate queues with random shares (buy stock)
                         stockQueueLinkedCopy = stockQueueLinked; // invoke copy constructor/operator overload
                         // Sell stock
                         //Share randomShare(numShares(gen), sharePrice(gen));
                         Share randomShare(DEFAULT_NUM_SHARES_SELL, DEFAULT_SELL_PRICE);
                         cout << "Selling " << randomShare.getNumShares() << " total shares at $" << randomShare.getPrice() << " each.\n";
                         double capitalGain = capitalGainsLinked(stockQueueLinkedCopy, SELL, randomShare);
                         cout << "\nCapital Gains: " << ((capitalGain >= 0) ? "Gain of " : "Loss of ") << "$" << abs(capitalGain) << "\n";
                         break;
                    }
                    default:
                         cout << "\n'" << static_cast<char>(ds + 0x61) << "' is not a valid option.\n";
                         break;
               }
          }
          else userQuit = true;
     }

	return 0;
}

/* ============================================================================
capitalGainsSTL()
============================================================================ */
double capitalGainsSTL(queue<Share>& stockQueue, bool buySell, Share share) {
     double gains = 0;
     double gain = 0;
     if (buySell == BUY) {
          stockQueue.push(share);
     }
     else { // buySell == SELL
          while(share.getNumShares() && !stockQueue.empty()) {
               Share currentDay = stockQueue.front();
               int numSharesBought = currentDay.getNumShares();
               double buyPrice = currentDay.getPrice();

               // Number of shares to be sold exceeds that in front queue element
               if (share.getNumShares() > numSharesBought) {
                    cout << "\nSelling " << numSharesBought << " shares at $" << share.getPrice() << " each.\n";
                    gain = (numSharesBought)*(share.getPrice()  - buyPrice);
                    cout << "Gains: " << ((gain >= 0) ? "Gain of " : "Loss of ") << "$" << abs(gain) << " dollars.\n";
                    gains += gain;
                    share.modifyNumShares(numSharesBought); // Subtract number of shares sold
                    stockQueue.pop(); // all shares were sold; remove day
               }
               // Number of shares in front queue element exceeds that to be sold
               else {
                    cout << "\nSelling " << share.getNumShares() << " shares at $" << share.getPrice() << " each.\n";
                    gain = (share.getNumShares())*(share.getPrice() - buyPrice);
                    cout << "Gains: " << ((gain >= 0) ? "Gain of " : "Loss of ") << "$" << abs(gain) << " dollars.\n";
                    gains += gain;
                    stockQueue.front().modifyNumShares(share.getNumShares()); // Subtract number of shares sold
                    share.modifyNumShares(share.getNumShares()); // set = 0
               }
          }
          if (share.getNumShares()) { // User requested to sell more than they own
               cout << "\nCould not sell all requested shares. Portfolio has been emptied.\n";
          }
     }
     return gains;
}

/* ============================================================================
capitalGainsArray()
============================================================================ */
double capitalGainsArray(ArrayQueue<Share>& stockQueue, bool buySell, Share share) {
     double gains = 0;
     double gain = 0;
     if (buySell == BUY) {
          stockQueue.enqueue(share);
     }
     else { // buySell == SELL
          while(share.getNumShares() && !stockQueue.empty()) {
               Share currentDay = stockQueue.front();
               int numSharesBought = currentDay.getNumShares();
               double buyPrice = currentDay.getPrice();

               // Number of shares to be sold exceeds that in front queue element
               if (share.getNumShares() > numSharesBought) {
                    cout << "\nSelling " << numSharesBought << " shares at $" << share.getPrice() << " each.\n";
                    gain = (numSharesBought)*(share.getPrice()  - buyPrice);
                    cout << "Gains: " << ((gain >= 0) ? "Gain of " : "Loss of ") << "$" << abs(gain) << " dollars.\n";
                    gains += gain;
                    share.modifyNumShares(numSharesBought); // Subtract number of shares sold
                    stockQueue.dequeue(); // all shares were sold; remove day
               }
               // Number of shares in front queue element exceeds that to be sold
               else {
                    cout << "\nSelling " << share.getNumShares() << " shares at $" << share.getPrice() << " each.\n";
                    gain = (share.getNumShares())*(share.getPrice() - buyPrice);
                    cout << "Gains: " << ((gain >= 0) ? "Gain of " : "Loss of ") << "$" << abs(gain) << " dollars.\n";
                    gains += gain;
                    stockQueue.front().modifyNumShares(share.getNumShares()); // Subtract number of shares sold
                    share.modifyNumShares(share.getNumShares()); // set = 0
               }
          }
          if (share.getNumShares()) { // User requested to sell more than they own
               cout << "\nCould not sell all requested shares. Portfolio has been emptied.\n";
          }
     }
     return gains;
}

/* ============================================================================
capitalGainsLinked()
============================================================================ */
double capitalGainsLinked(CircularQueue<Share>& stockQueue, bool buySell, Share share) {
     double gains = 0;
     double gain = 0;
     if (buySell == BUY) {
          stockQueue.enqueue(share);
     }
     else { // buySell == SELL
          while(share.getNumShares() && !stockQueue.empty()) {
               Share currentDay = stockQueue.front();
               int numSharesBought = currentDay.getNumShares();
               double buyPrice = currentDay.getPrice();

               // Number of shares to be sold exceeds that in front queue element
               if (share.getNumShares() > numSharesBought) {
                    cout << "\nSelling " << numSharesBought << " shares at $" << share.getPrice() << " each.\n";
                    gain = (numSharesBought)*(share.getPrice()  - buyPrice);
                    cout << "Gains: " << ((gain >= 0) ? "Gain of " : "Loss of ") << "$" << abs(gain) << " dollars.\n";
                    gains += gain;
                    share.modifyNumShares(numSharesBought); // Subtract number of shares sold
                    stockQueue.dequeue(); // all shares were sold; remove day
               }
               // Number of shares in front queue element exceeds that to be sold
               else {
                    cout << "\nSelling " << share.getNumShares() << " shares at $" << share.getPrice() << " each.\n";
                    gain = (share.getNumShares())*(share.getPrice() - buyPrice);
                    cout << "Gains: " << ((gain >= 0) ? "Gain of " : "Loss of ") << "$" << abs(gain) << " dollars.\n";
                    gains += gain;
                    stockQueue.front().modifyNumShares(share.getNumShares()); // Subtract number of shares sold
                    share.modifyNumShares(share.getNumShares()); // set = 0
               }
          }
          if (share.getNumShares()) { // User requested to sell more than they own
               cout << "\nCould not sell all requested shares. Portfolio has been emptied.\n";
          }
     }
     return gains;
}

/* ============================================================================
Print an indicative title for a console menu to the console and center the title
string.
============================================================================ */
void printCenteredTitle(const char * title, const int col_width) {
    const int size = strlen(title);

    // Calculate padding on both sides
    int total_padding = col_width - size;
    int left_padding = total_padding / 2;
    int right_padding = total_padding - left_padding; // Make sure right padding balances any leftover

    cout << "\n";

    for (int i = 0; i < left_padding; i++) {
        cout << "=";
    }

    cout << title;

    for (int i = 0; i < right_padding; i++) {
        cout << "=";
    }

    cout << "\n\n";
}

/* ============================================================================
                                  END FILE
============================================================================ */