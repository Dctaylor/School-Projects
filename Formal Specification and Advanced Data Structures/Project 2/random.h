//
//  random.h
//  David Taylor
//  COEN70L Lab 2
//
//
//

#ifndef random_h
#define random_h

#include <stdio.h>


class RandGen {
    int seed;
    int multiplier;
    int increment;
    int modulus;
    
public:
    /*
     Precondition: Must be given valid positive integers as the parameters
     Postcondition: Sets all private variables of the class
     Big O Complexity: O(1)
     */
    RandGen(int initial_seed, int initial_multiplier, int initial_increment, int initial_modulus);
    
    /*
     Precondition: The variable "seed" must be initialized to some value
     Postcondition: The "seed" variable is updated with a new value
     Big O Complexity: O(1)
     */
    void setSeed(int num);
    
    /*
     Precondition: Variables seed, multiplier, increment, and modulus must be initialized
     Postcondition: Returns a newly generated Pseudorandom number
     Big O Complexity: O(1)
    */
    int next();
    
};


#endif /* random_hpp */
