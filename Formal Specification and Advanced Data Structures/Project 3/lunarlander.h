//
//  lunarlander.hpp
//  David Taylor
//  COEN70L Lab 3
//
//
//

#ifndef lunarlander_h
#define lunarlander_h

#include <stdio.h>

class lunarlander {
    double flowRate; //in kilograms/sec
    double vert_velocity; //in meters/sec
    double altitude;  //in meters
    double fuel; //in kilograms
    
    static const int MASS = 900; //in kg
    static const int MAX_FUEL_RATE = 10; // in kg/sec
    static const int MAX_THRUST = 5000; //in newtons
    
public:
    /*
     Precondition: None
     Postcondition: All variables are initialized
     Big O: O(1)
     */
    lunarlander();
    
    /*
     Precondition: flowRate variable must be initialized to a positive value
     Postcondition: Current fuel flow rate is returned
     Big O: O(1)
     */
    double getFlowRate() const {return flowRate;}
    
    /*
     Precondition: vert_velocity variable must be initialized to a valid value
     Postcondition: Current vertical velocity is returned
     Big O: O(1)
     */
    double getVelocity() const {return vert_velocity;}
    
    /*
     Precondition: altitude variable must be initialized to a positive value
     Postcondition: Current altitude is returned
     Big O: O(1)
     */
    double getAltitude() const {return altitude;}
    
    /*
     Precondition: fuel variable must be initialized to a positive varibale
     Postcondition: current fuel is returned
     Big O: O(1)
     */
    double getFuel() const {return fuel;}
    
    /*
     Precondition: None
     Postcondition: Mass is returned
     Big O: O(1)
     */
    int getMass() const {return MASS;}
    
    /*
     Precondition: None
     Postcondition: Max fuel consumption rate is returned
     Big O: O(1)
     */
    int getMaxFuelRate() const {return MAX_FUEL_RATE;}
    
    /*
     Precondition: None
     Postcondition: Maximum thrust of the lander is returned
     Big O: O(1)
     */
    int getMaxThrust() const {return MAX_THRUST;}
    
    /*
     Precondition: Must be given a double between 0 and 1 as a paramater
     Postcondition: The flowRate variable is updated to a new value
     Big O: O(1)
     */
    void setFlowRate(double newRate);
    
    /*
     Precondition: Must be given a positive double as a parameter
     Postcondition: Updates variables to new values to simulate the passage of time
     Big O: O(1)
     */
    void timePassage(double seconds);
    
};

#endif /* lunarlander_hpp */
