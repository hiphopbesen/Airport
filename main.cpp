#include <iostream>
#include "zeit.h"
#include "plane.h"
#include "Tower.h"
#include <cstdlib>


using namespace std;

int main() {
    cout << "Hello, World!" << endl;
    zeit x = zeit();
    Tower tower = Tower();
    //loop durch den Tag 36000

    for (int i = 1; i <= 36000; ++i) {
        //zufällig ein Flugzeug erstellen
        float v1 = rand() % 1000;
        float absicht = rand() % 100;
        if(v1 > 994){
            cout<<v1;
            int y;
            if(absicht < 50){
                y = 0;
            }else{
                y=1;
            }
            //FLUGZEUG ERSTELLEN
            int fnum = rand() %  100000;
            plane rdmplane = plane(y, rand() % 1800 + 1800, i, fnum);
            rdmplane.request();


            //TOWER ANFRAGEN
            tower.anfrage(rdmplane.absicht,rdmplane.treibstoff,fnum, rdmplane.startzeit);
            x.printtime();
            tower.order(i);
            tower.abfertigen(i);
        }

        x++;
    }




    return 0;
}
