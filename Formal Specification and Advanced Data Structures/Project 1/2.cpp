//
//  2.cpp
//  David Taylor
//  COEN70L Lab 1
//
//
//

#include <stdio.h>
#include <cctype>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

/*
 Precondition: None
 Postcondition: None
 Big O Complexity: O(n)
*/
int main(void) {
    string input;
    int numalchars;
    int numnonalchars;
    
    getline(cin, input); //Takes user input
    
    
    for(int i = 0; i < input.length(); i++) { //Cycles through each char of the input
        char c = input.at(i);
        if(isalnum(c)) { //checks if the current char is alphanumerical
            numalchars++;
        }
        else if(c != 32) { //32 is the numerical char value for a space
            numnonalchars++;
        }
    }
    
    cout<<"User Input: " <<input<< " has " << numalchars << " alphanumeric characters and " << numnonalchars << " non-alphanumeric characters."<<endl;
    
    return 0;
}