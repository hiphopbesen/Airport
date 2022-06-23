//
// Created by Luca on 23.06.22.
//
#include <iostream>
#include "plane.h"
using namespace std;

plane::plane(int sol, int stoff) {
    if(absicht == 1){
        stoff = 0;
        textabsicht = "Starten";
    } else{
        textabsicht = "Landen";
    }
    absicht = sol;
    treibstoff = stoff;
}

void plane::request() {
    cout << "Flugzeug xxx mit absicht "<< textabsicht <<" hat noch treibstoff für "<< treibstoff << endl;
}
