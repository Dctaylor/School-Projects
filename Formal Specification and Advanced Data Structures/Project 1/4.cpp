//
//  4.cpp
//  David Taylor
//  COEN70L Lab 1
//
//
//

#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <fstream>



using namespace std;

/*
 Precondition: None
 Postcondition: Outputs "Hello World" and "Goodbye"
 Big O Complexity: O(1)
 */
int main(int argc, char * argv[]) {
    struct object {
    
        string* s;
    };

    object A, B;
    A.s = new string;
    B.s = new string;
    *A.s = "Hello World"; // A has "Hello World"
    *B.s = *A.s;          // B has "Hello World"
    *A.s = "Goodbye";     // A has "Goodbye"
    cout << *A.s << endl;
    cout << *B.s << endl;

    return 0;
}