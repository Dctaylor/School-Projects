//
//  statistician.h
//  David Taylor
//  COEN70L Lab 2
//
//
//

#ifndef statistician_h
#define statistician_h

#include <stdio.h>



class statistician {
    //class variables here
    int stat_length;
    double stat_last;
    double stat_smallest;
    double stat_largest;
    double stat_sum;
    
public:
    /*
     Constructor
     Precondition: An object of this class must be declared
     Postcondition: All private variables are initialized
     Big O Complexity: O(1)
     */
    statistician();
    
    /*
     Precondition: Must be given a valid double value as a parameter
     Postcondition: The private variables of the class will be updated due to the inclusion of a new value
     Big O Complexity: O(1)
     */
    void next_number(double num);
    
    /*
     Precondition: The variable "length" of the class must be initialized to be greater than or equal to 0
     Postcondition: Length is returned
     Big O Complexity: O(1)
     */
    int length();
    
    /*
     Precondition: The variable "last" of the class must be initialized to be greater than or equal to 0
     Postcondition: The last variable added by next_number is returned
     Big O Complexity: O(1)
     */
    double last();
    
    /*
     Precondition: The variable "sum" must be initialized to be greater than or equal to 0
     Postcondition: The sum of all numbers added by next_number will be returned
     Big O Complexity: O(1)
     */
    double sum();
    
    /*
     Precondition: The variables "sum" and "length" must be initialized to be greater than or equal to 0
     Postcondition: The mean of all numbers added by next_number will be returned
     Big O Complexity: O(1)
     */
    double mean();
    
    /*
     Precondition: The variable "smallest" must be initialized to be greater than or equal to 0
     Postcondition: The smallest number added by next_number will be returned
     Big O Complexity: O(1)
     */
    double smallest();
    
    /*
     Precondition: The variable "largest" must be initialized to be greater than or equal to 0
     Postcondition: The largest number added by next_number will be returned
     Big O Complexity: O(1)
     */
    double largest();
    
    /*
     Precondition: All private variables must be initialized to be greater than or equal to 0
     Postcondition: All private variables are reset to 0
     Big O Complexity: O(1)
     */
    void erase();
    
    /*
     Precondition: The given parameter must be an object of the statistician class, and both the parameter and the original statistician object must be initialized.
     Postcondition: The original statistician object is returned with new values
     Big O Complexity: O(1)
     */
    statistician operator =(const statistician & s2);
    
    /*
     Precondition: The given parameter must be an object of the statistician class, and both the parameter and the original statistician object must be initialized.
     Postcondition: A new statistician object is returned with values taken from both of the original objects
     Big O Complexity: O(1)
     */
    statistician operator +(const statistician & s2);
};

#endif /* statistician_h */
