//
// Created by Luca on 23.06.22.
//
#include <iostream>
#include "plane.h"
using namespace std;

plane::plane(int sol, int stoff, int start, int fnum) {
    absicht = sol;
    startzeit = start;
    if(absicht == 1){
        stoff = 0;
        textabsicht = "Starten";
    } else{
        textabsicht = "Landen";
    }
    treibstoff = stoff;
    flugnummer = fnum;
}

void plane::request() {
    if(absicht == 1){
        cout << " Flug NR:" << flugnummer << " mit absicht "<< textabsicht << endl;
        return;
    }
    cout << " Flug NR:" << flugnummer << " mit absicht "<< textabsicht <<" hat noch Treibstoff für "<< treibstoff << endl;
}
