//
//  statistician.cpp
//  David Taylor
//  COEN70L Lab 2
//
//
//

#include "statistician.h"
#include <cassert>


statistician::statistician() {
    stat_length = 0;
    stat_last = 0;
    stat_smallest = 0;
    stat_largest = 0;
    stat_sum = 0;
}

void statistician::next_number(double num) {
    if(num > stat_largest)
        stat_largest = num;
    
    if(stat_smallest == 0)
        stat_smallest = num;
    else if(num < stat_smallest)
        stat_smallest = num;
    
    stat_sum = stat_sum + num;
    stat_last = num;
    stat_length = stat_length + 1;
}

int statistician::length() {
    assert(stat_length >= 0);
    return stat_length;
}

double statistician::last() {
    assert(stat_last >= 0);
    return stat_last;
}

double statistician::sum() {
    assert(stat_sum >= 0);
    return stat_sum;
}

double statistician::mean() {
    assert(stat_sum && stat_length >=0);
    return (stat_sum/stat_length);
}

double statistician::smallest() {
    assert(stat_smallest >= 0);
    return stat_smallest;
}

double statistician::largest() {
    assert(stat_largest >= 0);
    return stat_largest;
}

void statistician::erase() {
    stat_length = 0;
    stat_last = 0;
    stat_smallest = 0;
    stat_largest = 0;
    stat_sum = 0;
}

statistician statistician::operator =(const statistician&s2) {
    stat_length = s2.stat_length;
    stat_sum = s2.stat_sum;
    stat_last = s2.stat_last;
    stat_smallest = s2.stat_smallest;
    stat_largest = s2.stat_largest;
    return *this;
}

statistician statistician::operator +(const statistician&s2) {
    statistician newStat;
    newStat.stat_length = stat_length + s2.stat_length;
    newStat.stat_sum = stat_sum + s2.stat_sum;
    newStat.stat_last = s2.stat_last;
    
    //checks which of the two given statistician objects has a smaller "smallest" variable
    if(stat_smallest < s2.stat_smallest)
        newStat.stat_smallest = stat_smallest;
    else
        newStat.stat_smallest = s2.stat_smallest;
    
    //checks which of the two given statistician objects has a bigger "largest" variable
    if(stat_largest > s2.stat_largest)
        newStat.stat_largest = stat_largest;
    else
        newStat.stat_largest = s2.stat_largest;
    
    return newStat;
}

