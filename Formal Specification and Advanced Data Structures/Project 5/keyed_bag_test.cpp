//
//  keyed_bag_test.cpp
//  
//
//  Created by david cameron taylor on 2/9/17.
//
//

#include "keyed_bag.h"
#include <iostream>
#include <iomanip>
using namespace coen70_lab;

int main() {
    keyed_bag b1;
    keyed_bag b2;
    keyed_bag b3;
    b3.insert(11, "b");
    b1.insert(10, "a");
    cout << b1.get("a") << endl;
    b2+=b1;
    b2.erase("a");
    
    b2 = b3 + b1;
    b2.count(10);
    return 0;
}
