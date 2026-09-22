// Part 1 - Strings in C++

#include <iostream>
#include <string>
#include <cctype>   // needed for isalnum() and tolower()
using namespace std;

bool isPalindrome(string str) {

    
    string cleanStr = "";
    int len = str.length();
    for (int i = 0; i < len; i++) {
        char currentChar = str[i];
        if (isalnum(currentChar)) {          // keep only letters/digits
            cleanStr += tolower(currentChar); // and make them lowercase
        }
    }

    int left = 0;
    int right = cleanStr.length() - 1;

    while (left < right) {
        if (cleanStr[left] != cleanStr[right]) {
            return false;   // as soon as one pair doesn't match, we're done
        }
        left++;
        right--;
    }
    return true;
}
int main() {
    string userInput;

    cout << "Enter a string, and I'll tell you if it's a palindrome: ";
    getline(cin, userInput);

    if (isPalindrome(userInput)) {
        cout << "\"" << userInput << "\" IS a palindrome." << endl;
    } else {
        cout << "\"" << userInput << "\" is NOT a palindrome." << endl;
    }
    return 0;
}