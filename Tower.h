//
// Created by Luca on 23.06.22.
//

#ifndef AIRPORT_TOWER_H
#define AIRPORT_TOWER_H
using namespace std;

class Tower {
private:
    int start[50][5] = {0};
    int startlaenge = 0;
    int landelaenge = 0;
    int landung[50][5] = {0};
    int final[100][5] = {0};
    int finallaenge = 0;
    int rollfeld = 0;  // 0= frei 1 = belegt
    int rfvorgang; //1 = start 0 = landung
    int rfbstart = 0; //rollfeld vorgang startzeit in sek nach öffnung des flughafens
    int ges = 0;
    int landezeit = 0;
    int startzeit = 0;

public:
    Tower();

    void anfrage(int absicht, int treibstoff, int flugnummer, int anfragezeit);
    void order(int zeit);
    void nestedsort();
    void abfertigen(int zeit);
    void popstart();
    void poplandung();
    void debug();
};


#endif //AIRPORT_TOWER_H
