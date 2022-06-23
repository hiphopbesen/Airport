#include <iostream>
#include "zeit.h"
#include "plane.h"
#include <cstdlib>


using namespace std;

int main() {
    cout << "Hello, World!" << endl;
    zeit x = zeit();
    //loop durch den Tag
    for (int i = 1; i <= 1200; ++i) {
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
            plane rdmplane = plane(y, rand() % 1200 + 1200);
            rdmplane.request();
            x.printtime();
        }

        x++;

    }
    return 0;
}
