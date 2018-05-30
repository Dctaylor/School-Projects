//
//  main_random.cpp
//  
//
//  Created by david cameron taylor on 1/19/17.
//
//

#include "random.h"
#include <iostream>
#include <iomanip>

using namespace std;

int main(void) {
    RandGen rand(1, 40, 725, 729);
    
    cout<<rand.next()<<endl;
    cout<<"new seed"<<endl;
    cout<<rand.next()<<endl;
    
    return 0;
}
