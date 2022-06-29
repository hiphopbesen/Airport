//
// Created by Luca on 23.06.22.
//
#include <iostream>
#include "plane.h"
#include "zeit.h"
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

void plane::request(int time) {
    zeit k = zeit();

    if(absicht == 1){
        k.printnow(time);
        cout << " Flug NR:" << flugnummer << " mit absicht "<< textabsicht <<" meldet sich beim Tower"<< endl;
        return;
    }
    k.printnow(time);
    cout << " Flug NR:" << flugnummer << " mit absicht "<< textabsicht <<" meldet sich beim Tower und hat noch Treibstoff für "<< treibstoff << endl;
}
