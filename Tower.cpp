//
// Created by Luca on 23.06.22.
//
#include "colormod.h" // namespace Color
#include "Tower.h"
#include <iostream>
#include "zeit.h"

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
        int prio = (1/(3600-absturz)) + wartezeit;
        //ausgleichen der warteschlangen
        int ausgleich = 0;
        if(landelaenge-startlaenge>0){
            ausgleich = landelaenge-startlaenge*10;
        }
        landung[i][4] = prio + ausgleich;
    }
    for (int i = 0; i <= startlaenge-1; ++i) {
        int wartezeit;
        wartezeit = zeit - start[i][3];
        int ausgleich = 0;
        if(startlaenge-landelaenge>0){
            ausgleich = startlaenge-landelaenge*10;
        }
        start[i][4] = wartezeit+ausgleich;
    }
    //gesamtlänge des kombinierten arrrays
    ges = 0;
    for (int i = 0; i <= startlaenge-1; ++i){
            final[ges][0] = start[i][0];
            final[ges][1] = start[i][1];
            final[ges][2] = start[i][2];
            final[ges][3] = start[i][3];
            final[ges][4] = start[i][4];
            ges++;
    }
    //dann landung
    for (int i = 0; i <= landelaenge-1; ++i) {
        final[ges][0] = landung[i][0];
        final[ges][1] = landung[i][1];
        final[ges][2] = landung[i][2];
        final[ges][3] = landung[i][3];
        final[ges][4] = landung[i][4];
        ges++;
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
        kannlanden();
        if(currentwait < treibstoff){
            if(landelaenge < 50){
                landung[landelaenge][0]=absicht;
                landung[landelaenge][1]=treibstoff;
                landung[landelaenge][2]=flugnummer;
                landung[landelaenge][3]=anfragezeit;
                landelaenge++;
            }else{
                Color::Modifier blue(Color::FG_BLUE);
                Color::Modifier def(Color::FG_DEFAULT);
                cout <<blue<< "abgelehnt, Landewarteschlange voll" << def<<endl;
            }
        } else{
            Color::Modifier blue(Color::FG_BLUE);
            Color::Modifier def(Color::FG_DEFAULT);
            cout <<blue<< "abgelehnt, zu wenig Treibstoff"  << def<<endl;
        }
    }
}

void Tower::abfertigen(int ts) {
    //checken ob rollfeld frei und rollfeld
    if(rollfeld == 1){
        if(rfvorgang == 0){
            if(rfbstart+landezeit <= ts){
                rollfeld = 0;
            }
        }
        if(rfvorgang == 1){
            if(rfbstart+startzeit <= ts){
                rollfeld = 0;
            }
        }
    }
    if(rollfeld == 0){
        zeit k = zeit();
        if(startlaenge > 0){
            //vorgang starten, und aus warteschlange löschen.
            if(final[0][0] == 1){
                //start
                k.printnow(ts);
                Color::Modifier green(Color::FG_GREEN);
                Color::Modifier def(Color::FG_DEFAULT);
                cout << green<< " Flug NR:" << final[0][2] << " Startet" << def <<endl;
                popstart();
                rfvorgang = 1;
                rfbstart = ts;
            }
        }
        if(landelaenge > 0){
            if(final[0][0] == 0){
                //LANDUNG
                k.printnow(ts);
                Color::Modifier green(Color::FG_GREEN);
                Color::Modifier def(Color::FG_DEFAULT);
                cout <<green<< " Flug NR:" << final[0][2] << " Landet" << def << endl;
                poplandung();
                rfvorgang = 0;
                rfbstart = ts;
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
        for (int i = 0; i < startlaenge; ++i) {
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
        landung[0][0] = 0;
        landung[0][1] = 0;
        landung[0][2] = 0;
        landung[0][3] = 0;
        landung[0][4] = 0;
    }
}

void Tower::kannlanden() {
    //3 vorgänge muss ein flugzeug mindestens warten können.
    int depth = 3;
    currentwait = 0;
    //wartezeiten der ersten x wartenden analysieren oder wie viele wartenden es gibt,
    if(ges < depth){
        depth = ges;
    }
    //start und landezeiten werden zur sicherheit verdoppelt
    for (int i = 0; i < depth; ++i) {
        if(final[i][0] == 1){
            currentwait = currentwait + startzeit*2;
        }
        if(final[i][0] == 0){
            currentwait = currentwait + landezeit*2;
        }
    }
}

void Tower::checkcrash(int ts) {
    for(int i = 0;i < landelaenge;i++){
        if(landung[i][1]+landung[i][3] < ts){
            crash(i,ts);
        }
    }
}

void Tower::crash(int id, int ts) {
    zeit k = zeit();
    k.printnow(ts);
    Color::Modifier red(Color::FG_RED);
    Color::Modifier def(Color::FG_DEFAULT);
    cout <<red<< " Flug NR:" << landung[id][2] << " ist abgestürzt" << def << endl;
    //während id <= länge austauschen, dann enfernen
    int fid = id;
    landelaenge--;
    do{
        landung[fid][0] = landung[fid+1][0];
        landung[fid][1] = landung[fid+1][1];
        landung[fid][2] = landung[fid+1][2];
        landung[fid][3] = landung[fid+1][3];
        landung[fid][4] = landung[fid+1][4];
        fid++;
    } while (fid < landelaenge);
}




