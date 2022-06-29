//
// Created by Luca on 23.06.22.
//

#ifndef AIRPORT_TOWER_H
#define AIRPORT_TOWER_H
using namespace std;

class Tower {
private:
    //werte zum anpassen
        //zeitspanne start und landung in sekunden
        int landezeit = 300;
        int startzeit = 300;
        //maximale schlangenlänge
        int landung[50][5] = {0};
        int final[100][5] = {0};
        int start[50][5] = {0};

    //variablen die zur berechnung benötigt werden
    int startlaenge = 0;
    int landelaenge = 0;
    int ges = 0;

    //rollfeld
    int rollfeld = 0;  // 0= frei 1 = belegt
    int rfvorgang; //1 = start 0 = landung
    int rfbstart = 0; //rollfeld vorgang startzeit in sek nach öffnung des flughafens
    int currentwait = 0; //wartezeit

public:
    Tower();

    void anfrage(int absicht, int treibstoff, int flugnummer, int anfragezeit);
    void order(int zeit);
    void nestedsort();
    void abfertigen(int zeit);
    void popstart();
    void poplandung();
    void kannlanden();
    void checkcrash(int ts);
    void crash(int id,int ts);
    void debug();
};


#endif //AIRPORT_TOWER_H
