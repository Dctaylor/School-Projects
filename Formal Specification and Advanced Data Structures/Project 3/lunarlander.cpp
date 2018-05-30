//
//  lunarlander.cpp
//  David Taylor
//  COEN70L Lab 3
//
//
//

#include "lunarlander.h"
#include <cassert>

lunarlander::lunarlander() {
    flowRate = 0; //in kilograms/sec
    vert_velocity = 0; //in meters/sec
    altitude = 1000; //in meters
    fuel = 1700;  //in kilograms
}

void lunarlander::setFlowRate(double newRate) {
    assert(newRate >= 0.0 && newRate <= 1.0);
    flowRate = newRate;
}

void lunarlander::timePassage(double seconds) {
    assert(seconds >= 0);
    
    //Checking if Fuel is empty
    if(flowRate > 0 && fuel == 0)
        flowRate = 0;
    
    //velocity change
    double thrust = flowRate * MAX_THRUST;
    double vel_change = seconds * ((thrust/(MASS+fuel)) - 1.62);
    vert_velocity += vel_change;
    
    //Altitude change
    double alt_change = vert_velocity * seconds;
    altitude += alt_change;
    
    //Fuel amount change
    double fuel_change = seconds * flowRate * MAX_FUEL_RATE;
    fuel -= fuel_change;
    
    //Check if ship has landed
    if(altitude < 0) {
        altitude = 0;
        vert_velocity = 0;
    }
    
    //Check if out of fuel
    if(fuel < 0)
        fuel = 0;
}


