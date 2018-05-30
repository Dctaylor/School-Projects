//
//  main_stat.cpp
//  
//
//  Created by david cameron taylor on 1/19/17.
//
//

#include "statistician.h"
#include <iostream>
#include <iomanip>
using namespace std;
int main(void) {
    statistician s1, s2, s3;
    
    s1.next_number(1.5);
    s1.next_number(7.2);
    s1.next_number(3.3);
    
    s2.next_number(1.4);
    s2.next_number(5.5);
    s2.next_number(2.1);
    
    s3 = s1;
    cout<<"s3 set to s1"<<endl;
    cout<< "s3 length: "<<s3.length()<<endl;
    cout<< "s3 sum: "<<s3.sum()<<endl;
    cout<< "s3 last value: "<<s3.last()<<endl;
    cout<< "s3 largest value: "<<s3.largest()<<endl;
    cout<< "s3 smallest value: "<<s3.smallest()<<endl;
    
    s3 = s1 + s2;
    cout<<"s3 set to s1 + s2"<<endl;
    cout<< "s3 length: "<<s3.length()<<endl;
    cout<< "s3 sum: "<<s3.sum()<<endl;
    cout<< "s3 last value: "<<s3.last()<<endl;
    cout<< "s3 largest value: "<<s3.largest()<<endl;
    cout<< "s3 smallest value: "<<s3.smallest()<<endl;
    
    s3.erase();
    cout<<"s3 erased"<<endl;
    cout<< "s3 length: "<<s3.length()<<endl;
    cout<< "s3 sum: "<<s3.sum()<<endl;
    cout<< "s3 last value: "<<s3.last()<<endl;
    cout<< "s3 largest value: "<<s3.largest()<<endl;
    cout<< "s3 smallest value: "<<s3.smallest()<<endl;
    
    return 0;
}
