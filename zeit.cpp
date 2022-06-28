//
// Created by Luca on 23.06.22.
// Einfache Tageszeit nach UNIX Timestamp modell
//
#include <iostream>
#include "zeit.h"
using namespace std;

zeit::zeit() {
    stunde = 8;
    min = 0;
    sek = 0;
}

void zeit::printtime(){
    string ps;
    string ss;
    string ms;
    if (stunde < 10){
        ps = "0" + to_string(stunde);
    }else{
        ps = to_string(stunde);
    }
    if(min < 10){
        ms = "0" + to_string(min);
    }else{
        ms = to_string(min);
    }
    if(sek < 10){
        ss = "0" + to_string(sek);
    }else{
        ss = to_string(sek);
    }
    cout << ps << ":"<< ms <<":"<< ss << endl;
}

//suffix operator
zeit zeit::operator ++(int nil){
    sek++;
    if(sek == 60){
        sek = 0;
        min++;
        if(min == 60){
            min = 0;
            stunde++;
            if(stunde == 24){
                stunde = 0;
            }
        }
    }
}
