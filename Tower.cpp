//
// Created by Luca on 23.06.22.
//
#include <algorithm>
#include "Tower.h"
#include <iostream>
using namespace std;

Tower::Tower() {
    //0 = LEER 1 = Voll
    rollfeld = 0;
}



void Tower::order(int zeit) {
    for (int i = 0; i <= landelaenge-1; ++i) {
        int wartezeit = zeit - landung[i][3];
        //große zahl = hohe prio, absturzzeit muss je niedriger die ist mehr prio geben.
        int absturz = landung[i][1] - wartezeit;
        int prio = (3600-absturz) + wartezeit;
        landung[i][4] = prio;
    }
    for (int i = 0; i <= startlaenge-1; ++i) {
        int wartezeit;
        wartezeit = zeit - start[i][3];
        start[i][4] = wartezeit;
    }
    //gesamtlänge des kombinierten arrrays
    ges = 0;
    for (int i = 0; i <= startlaenge-1; ++i){
        if (ges < startlaenge+landelaenge)
        {
            final[ges][0] = start[i][0];
            final[ges][1] = start[i][1];
            final[ges][2] = start[i][2];
            final[ges][3] = start[i][3];
            final[ges][4] = start[i][4];
            ges++;
        }
    }




        //dann landung
    for (int i = 0; i < landelaenge-1; ++i) {
        if (ges < startlaenge+landelaenge)
        {
        final[ges][0] = landung[i][0];
        final[ges][1] = landung[i][1];
        final[ges][2] = landung[i][2];
        final[ges][3] = landung[i][3];
        final[ges][4] = landung[i][4];
        ges++;
        }
    }
    // sortieren nach priorität gespeichert in final[..][4]
    if(ges > 1){
        nestedsort();
    }
}

void Tower::anfrage(int absicht, int treibstoff, int flugnummer, int anfragezeit) {
    //absicht 1 = Starten
    if(absicht == 1){
        if(startlaenge < 50){
            start[startlaenge][0]=absicht;
            start[startlaenge][1]=treibstoff;
            start[startlaenge][2]=flugnummer;
            start[startlaenge][3]=anfragezeit;
            startlaenge++;
        }else{
            cout << "abgelehnt, startwarteschlange voll" <<endl;
        }

    }
    //absicht 0 = Landen
    if(absicht == 0){
        if(landelaenge < 50){
            landung[landelaenge][0]=absicht;
            landung[landelaenge][1]=treibstoff;
            landung[landelaenge][2]=flugnummer;
            landung[landelaenge][3]=anfragezeit;
            landelaenge++;
        }else{
            cout << "abgelehnt, Landewarteschlange voll" <<endl;
        }
    }
}

void Tower::abfertigen(int zeit) {
    //checken ob rollfeld frei und rollfeld
    if(rollfeld == 1){
        if(rfvorgang == 0){
            if(rfbstart+landezeit <= zeit){
                rollfeld = 0;
            }
        }
        if(rfvorgang == 1){
            if(rfbstart+startzeit <= zeit){
                rollfeld = 0;
            }
        }
    }
    if(rollfeld == 0){
        if(startlaenge > 0){
            //vorgang starten, und aus warteschlange löschen.
            if(final[0][0] == 1){
                //start
                cout << "Flug " << final[0][2] << " Startet" <<endl;
                popstart();
                rfvorgang = 1;
            }
        }
        if(landelaenge > 0){
            if(final[0][0] == 0){
                //LANDUNG
                cout << "Flug " << final[0][2] << " Landet" << endl;
                poplandung();
                rfvorgang = 0;
            }
        }
        rollfeld = 1;
    }
}

void Tower::nestedsort() {
    bool sorted = false;
    int temp[] = {0,0,0,0,0};
    do {
        sorted = true;
        for (int i = 0; i < startlaenge+landelaenge-1; ++i) {
            if(final[i][4] < final[i+1][4]){
                sorted = false;
                //umschlichten
                temp[0] = final[i][0];
                temp[1] = final[i][1];
                temp[2] = final[i][2];
                temp[3] = final[i][3];
                temp[4] = final[i][4];

                final[i][0] = final[i+1][0];
                final[i][1] = final[i+1][1];
                final[i][2] = final[i+1][2];
                final[i][3] = final[i+1][3];
                final[i][4] = final[i+1][4];

                final[i+1][0] = temp[0];
                final[i+1][1] = temp[1];
                final[i+1][2] = temp[2];
                final[i+1][3] = temp[3];
                final[i+1][4] = temp[4];
            }
        }
    }
    while(!sorted);
}

void Tower::debug() {
    cout << "liste" << endl;
    for (int i = 0; i < ges; ++i) {
        cout << final[i][4] << "prio" << endl;
    }
}

void Tower::popstart() {
    startlaenge--;
    if(startlaenge >0){
        for (int i = 0; i < startlaenge-1; ++i) {
            start[i][0] = start[i+1][0];
            start[i][1] = start[i+1][1];
            start[i][2] = start[i+1][2];
            start[i][3] = start[i+1][3];
            start[i][4] = start[i+1][4];
        }
    }else{
        start[0][0] = 5;
        start[0][1] = 5;
        start[0][2] = 5;
        start[0][3] = 5;
        start[0][4] = 5;
    }
}

void Tower::poplandung() {
    landelaenge--;
    if(landelaenge > 0){
        for (int i = 0; i < landelaenge; ++i) {
            landung[i][0] = landung[i+1][0];
            landung[i][1] = landung[i+1][1];
            landung[i][2] = landung[i+1][2];
            landung[i][3] = landung[i+1][3];
            landung[i][4] = landung[i+1][4];
        }
    } else{
        landung[0][0] = 5;
        landung[0][1] = 5;
        landung[0][2] = 5;
        landung[0][3] = 5;
        landung[0][4] = 5;
    }
}




