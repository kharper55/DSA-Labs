/* ============================================================================
lab1_5.cpp

This program demonstrates concatenation for various list data structures.

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
#include <iostream>      // For console interaction
#include <string>        // For string type
#include <cstring>       // For stringlen
#include <deque>         // STL deque
#include <random>        // For random device and mersenne twister implementation
#include <set>           // For checking uniqueness of random integers
#include <cstdint>       // For unsigned integers

// Header includes
#include "ArrayDeque.hpp"
#include "LinkedDeque.hpp"

// Prototypes
void dealCardsSTL(deque<string>& deck, const int NUM_CARDS);
void dealCardsArray(ArrayDeque<string>& deck, const int NUM_CARDS);
void dealCardsLinked(LinkedDeque<string>& deck, const int NUM_CARDS);
void printCenteredTitle(const char * title, const int col_width);

using namespace std;

// Constants
const string deck[] = {
    "2 of Hearts", "3 of Hearts", "4 of Hearts", "5 of Hearts", "6 of Hearts", "7 of Hearts", "8 of Hearts", "9 of Hearts", "10 of Hearts", "J of Hearts", "Q of Hearts", "K of Hearts", "A of Hearts",
    "2 of Diamonds", "3 of Diamonds", "4 of Diamonds", "5 of Diamonds", "6 of Diamonds", "7 of Diamonds", "8 of Diamonds", "9 of Diamonds", "10 of Diamonds", "J of Diamonds", "Q of Diamonds", "K of Diamonds", "A of Diamonds",
    "2 of Clubs", "3 of Clubs", "4 of Clubs", "5 of Clubs", "6 of Clubs", "7 of Clubs", "8 of Clubs", "9 of Clubs", "10 of Clubs", "J of Clubs", "Q of Clubs", "K of Clubs", "A of Clubs",
    "2 of Spades", "3 of Spades", "4 of Spades", "5 of Spades", "6 of Spades", "7 of Spades", "8 of Spades", "9 of Spades", "10 of Spades", "J of Spades", "Q of Spades", "K of Spades", "A of Spades"
};

#define STD_DECK_SIZE 52

const string DS_OPTIONS[3] = {
    "STL deque",
    "Array-based deque",
    "Doubly linked list-based deque",
};

const char QUIT_CHAR = 'x';

enum {
    STL_DEQUE,
    ARRAY_DEQUE,
    LINKED_DEQUE
};

#define COL_WIDTH       65
#define NUM_CARDS_DEALT 5

/* ============================================================================
main()
============================================================================ */
int main() {

    deque<string> cardsDequeSTL;                // STL deque
    ArrayDeque<string> cardsDequeArray;         // Array-based deque
    LinkedDeque<string> cardsDequeLinked;       // Doubly linked list-based deque
    deque<string> cardsDequeSTLCopy;            // Copies of deque
    ArrayDeque<string> cardsDequeArrayCopy;
    LinkedDeque<string> cardsDequeLinkedCopy;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<uint8_t> cardNum(0, 51); // for deck shuffling
    set<uint8_t> uniqueCards; // each unique card should occur once in the deck
    uint8_t count = 0;
    char userChoice;    // Should make this a string and accept only the first char, discarding remainder
    bool userQuit = false;

    while(count < STD_DECK_SIZE) {
        uint8_t card = cardNum(gen); // generate a random int in [0, 51]
        if (uniqueCards.find(card) == uniqueCards.end()) {
            uniqueCards.insert(card); // update the set
            cardsDequeSTL.push_front(deck[card]);
            cardsDequeArray.insertFront(deck[card]); // enqueue the card
            cardsDequeLinked.insertFront(deck[card]);
            count++;
        }
    }

    cout << "\nWelcome to card dealer demo!\n";

    printCenteredTitle(" Shuffled Deck ", COL_WIDTH);
    cardsDequeArray.printDeque();

    while(!userQuit) {
        printCenteredTitle(" Data structure selection ", COL_WIDTH);
        for (int i = 0; i < sizeof(DS_OPTIONS)/sizeof(DS_OPTIONS[0]); i++) {
            cout << static_cast<char>(0x61 + i) << ") " << DS_OPTIONS[i] << "\n";
        }
        printCenteredTitle(" Input ", COL_WIDTH);
        cout << "Select an implementation for card dealer (use '" << QUIT_CHAR << "' to quit): ";
        cin >> userChoice;
        if (userChoice != QUIT_CHAR) {
            int ds = static_cast<int>(userChoice - 0x61);
            switch(ds) {
                case(STL_DEQUE): // STL queue 
                {   
                    printCenteredTitle(" STL Deque ", COL_WIDTH);
                    cardsDequeSTLCopy = cardsDequeSTL;
                    dealCardsSTL(cardsDequeSTLCopy, NUM_CARDS_DEALT);
                    break;
                }
                case(ARRAY_DEQUE): // Array based queue
                {   
                    printCenteredTitle(" Array-based Deque ", COL_WIDTH);
                    cardsDequeArrayCopy = cardsDequeArray;
                    dealCardsArray(cardsDequeArrayCopy, NUM_CARDS_DEALT);
                    break;
                }
                case(LINKED_DEQUE): // Doubly linked list queue
                {
                    printCenteredTitle(" Doubly linked list-based Deque ", COL_WIDTH);
                    cardsDequeLinkedCopy = cardsDequeLinked;
                    dealCardsLinked(cardsDequeLinkedCopy, NUM_CARDS_DEALT);
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
dealCardsSTL() deals functions alternating from top/bottom of deck
============================================================================ */
void dealCardsSTL(deque<string>& deck, const int NUM_CARDS) {
    for (int i = 0; i < NUM_CARDS; i++) {
        if ((i % 2) == 0) { // number is even or 0
            cout << "Dealing " << deck.front() << " from top.\n";
            deck.pop_front();
        }
        else {  // number is odd
            cout << "Dealing " << deck.back() << " from bottom.\n";
            deck.pop_back();
        }

    }
}

/* ============================================================================
dealCardsArray() deals functions alternating from top/bottom of deck
============================================================================ */
void dealCardsArray(ArrayDeque<string>& deck, const int NUM_CARDS) {
    for (int i = 0; i < NUM_CARDS; i++) {
        if ((i % 2) == 0) { // number is even or 0
            cout << "Dealing " << deck.front() << " from top.\n";
            deck.removeFront();
        }
        else {  // number is odd
            cout << "Dealing " << deck.back() << " from bottom.\n";
            deck.removeBack();
        }
    }
}

/* ============================================================================
dealCardsLinked() deals functions alternating from top/bottom of deck
============================================================================ */
void dealCardsLinked(LinkedDeque<string>& deck, const int NUM_CARDS) {
    
    if (NUM_CARDS > deck.size()) {
        cout << "Can not deal more cards than are available.\n";
        return;
    }
    for (int i = 0; i < NUM_CARDS; i++) {
        if ((i % 2) == 0) { // number is even or 0
            cout << "Dealing " << deck.front() << " from top.\n";
            deck.removeFront();
        }
        else {  // number is odd
            cout << "Dealing " << deck.back() << " from bottom.\n";
            deck.removeBack();
        }

    }
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