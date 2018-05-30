//
//  3.cpp
//  David Taylor
//  COEN70L Lab 1
//
//
//

#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cctype>

using namespace std;

/*
 Precondition: An existing filename must be provided by the user
 Postcondition: The program will output all words with a length greater than 10 in all uppercase
 Big O complexity: O(n)
 */
int main(int argc, char * argv[]) {
    if(argc != 2) {
        cout<<"Cannot Open File"<<endl;
        return 0;
    }
    
    ifstream in_file;
    in_file.open(argv[1]);
    string string1;
    
    //Loops until end of file is reached
    while(in_file.peek() != EOF) {
        in_file>>string1;
        
        //Ignores words shorter than 10 chars
        if(string1.length() < 10) {
            continue;
        }
        
        //Loops through and deletes any non-alphanumerical characters
        for(int i = 0; i < string1.length(); i++) {
            if(isalnum(string1.at(i)) == false) {
               string1.erase(i,1);
            }
        }
        //Checks if the word is longer than 10 and capitalizes all chars if so
        if(string1.length() >= 10) {
            for(int j = 0; j < string1.length(); j++) {
                putchar(toupper(string1.at(j)));
            }
            cout<<endl;
        }
    }
    in_file.close();
    
    return 0;
}