//
//  random.cpp
//  David Taylor
//  COEN70L Lab 2
//
//
//

#include "random.h"
#include <cassert>
#include <iostream>
#include <iomanip>

RandGen::RandGen(int initial_seed, int initial_multiplier, int initial_increment, int initial_modulus) {
    seed = initial_seed;
    multiplier = initial_multiplier;
    increment = initial_increment;
    modulus = initial_modulus;
}

void RandGen::setSeed(int num) {
    seed = num;
}

int RandGen::next() {
    int val = (multiplier * seed + increment) % modulus;
    seed = val;
    return val;
}



