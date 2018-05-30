//
//  lunar_main.cpp
//  
//
//  Created by david cameron taylor on 1/26/17.
//
//

#include "lunarlander.h"
#include <iostream>
#include <iomanip>

using namespace std;

int main(void) {
    lunarlander apollo;
    
    apollo.setFlowRate(0);
    cout<<"Flow Rate set to: "<<apollo.getFlowRate()<<endl;
    
    apollo.timePassage(10);
    cout<<"10 seconds of time passing"<<endl;
    cout<<"Afterwards... Speed: "<<apollo.getVelocity()<<", Altitude: "<<apollo.getAltitude()<<", and Fuel: "<<apollo.getFuel()<<endl;
    
}
