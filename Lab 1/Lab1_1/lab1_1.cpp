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

// Header includes

using namespace std;

bool isPalindrome(const string& str, int left, int right);

/* ============================================================================
main()
============================================================================ */
int main() {
    
    string myStr = "racecar";
    string myStr2 = "123321";
    string myStr3 = "soos";
    string myStr4 = "61916";
    string myStr5 = "HG6AGH";
    string myStr6 = "12341";
    string myStr7 = "";
    string myStr8 = " ";
    string myStr9 = "c";
    string myStr10 = "Able was I, I saw Elba";
    string myStr11 = "A man, a plan, a canal, Panama!";
    string myStr12 = "amanaplanacanalpanama";

    cout << "\nWelcome to recursive palindrome demo!\n\n";

    cout << myStr << (isPalindrome(myStr, 0, myStr.length() - 1) ? " is " : " is not ") << "a palindrome\n";
    cout << myStr2 << (isPalindrome(myStr2, 0, myStr2.length() - 1) ? " is " : " is not ") << "a palindrome\n";
    cout << myStr3 << (isPalindrome(myStr3, 0, myStr3.length() - 1) ? " is " : " is not ") << "a palindrome\n";
    cout << myStr4 << (isPalindrome(myStr4, 0, myStr4.length() - 1) ? " is " : " is not ") << "a palindrome\n";
    cout << myStr5 << (isPalindrome(myStr5, 0, myStr5.length() - 1) ? " is " : " is not ") << "a palindrome\n";
    cout << myStr6 << (isPalindrome(myStr6, 0, myStr6.length() - 1) ? " is " : " is not ") << "a palindrome\n";
    cout << myStr7 << (isPalindrome(myStr7, 0, myStr7.length() - 1) ? " is " : " is not ") << "a palindrome\n";
    cout << myStr8 << (isPalindrome(myStr8, 0, myStr8.length() - 1) ? " is " : " is not ") << "a palindrome\n";
    cout << myStr9 << (isPalindrome(myStr9, 0, myStr9.length() - 1) ? " is " : " is not ") << "a palindrome\n";
    cout << myStr10 << (isPalindrome(myStr10, 0, myStr10.length() - 1) ? " is " : " is not ") << "a palindrome\n";
    cout << myStr11 << (isPalindrome(myStr11, 0, myStr11.length() - 1) ? " is " : " is not ") << "a palindrome\n";
    cout << myStr12 << (isPalindrome(myStr12, 0, myStr12.length() - 1) ? " is " : " is not ") << "a palindrome\n";

    cout << "\n";

	return 0;
}

/* ============================================================================
isPalindrome()

Simple recursive function to determine with a string is a palindrome
Does not handle special characters and considers an uppercase letter
not equal to its equivalent lowercase.

These issues can be rectified by modifying a copy of the string prior to executing 
the algorithm
============================================================================ */
bool isPalindrome(const string& str, int left, int right) {
    while (left < right) { // base case is left >= right
        if (str[left] == str[right]) {
            isPalindrome(str, ++left, --right);
        }
        else {
            left = right; // ensure quick termination
            return false;
        }
    }
    return true;
}

/* ============================================================================
                                  END FILE
============================================================================ */