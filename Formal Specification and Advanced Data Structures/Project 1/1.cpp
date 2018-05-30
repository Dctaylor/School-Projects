//
//  1.cpp
//  David Taylor
//  COEN70L Lab 1
//
//
//

#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

/*
 Precondition: None
 Postcondition: None
 Big O Cpmplexity: O(1)
 */
int main(void) {
    string string1("0123456789");
    string string2("9876543210");
    
    
    for(int i = 0; i < 10; i++) { //Prints out string1 and string2 5 times each starting 1 ahead of the previous
        cout<<std::setw(i + 10);  //Sets the starting position of the output
        cout<<string1<<std::endl;
        i++;
        cout<<std::setw(i + 10);
        cout<<string2<<endl;
    }
    
    return 0;
}


