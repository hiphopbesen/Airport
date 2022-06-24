//
// Created by Luca on 23.06.22.
//
#include <iostream>
#include "plane.h"
using namespace std;

plane::plane(int sol, int stoff) {
    absicht = sol;
    if(absicht == 1){
        stoff = 0;
        textabsicht = "Starten";
    } else{
        textabsicht = "Landen";
    }
    treibstoff = stoff;
}

void plane::request() {
    if(absicht == 1){
        cout << " Flugzeug xxx Will "<< textabsicht << endl;
        return;
    }
    cout << " Flugzeug xxx mit absicht "<< textabsicht <<" hat noch Treibstoff für "<< treibstoff << endl;
}
