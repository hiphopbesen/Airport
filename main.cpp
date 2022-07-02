#include <iostream>
#include "zeit.h"
#include "plane.h"
#include "Tower.h"
#include <cstdlib>


using namespace std;

int main() {
    cout << "Airport simulation!" << endl;
    zeit x = zeit();
    Tower tower = Tower();
    //loop durch den Tag 36000
    int fnum = 1;
    for (int i = 1; i <= 50000; ++i) {
        //zufällig ein Flugzeug erstellen
        float v1 = rand() % 1000;
        float absicht = rand() % 100;
        if(i <= 36000){
            if(v1 > 994){
                int y;
                if(absicht < 50){
                    y = 0;
                }else{
                    y=1;
                }
                //FLUGZEUG ERSTELLEN
                plane rdmplane = plane(y, rand() % 1800 + 1800, i, fnum);
                fnum++;
                rdmplane.request(i);
                //TOWER ANFRAGEN
                tower.anfrage(rdmplane.absicht,rdmplane.treibstoff,fnum, rdmplane.startzeit);
            }
            tower.order(i);
            tower.checkcrash(i);
            tower.abfertigen(i);
        } else{
            tower.order(i);
            tower.checkcrash(i);
            tower.abfertigen(i);
        }

        x++;
    }




    return 0;
}


int maindebug(){
    cout << "Airport simulation!" << endl;
    zeit x = zeit();
    Tower tower = Tower();
    //loop durch den Tag 36000
    tower.anfrage(0,100,1, 0);
    tower.anfrage(1,0,2, 0);
    tower.anfrage(0,3600,3, 200);
    tower.anfrage(0,1000,4, 500);
    for (int i = 1; i <= 50000; ++i) {
        tower.order(i);
        tower.checkcrash(i);
        tower.abfertigen(i);
        x++;
    }

    return 0;
}