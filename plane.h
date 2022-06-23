//
// Created by Luca on 23.06.22.
//

#ifndef AIRPORT_PLANE_H
#define AIRPORT_PLANE_H
using namespace std;


class plane {
public:
    //absicht 0 = Landen, 1 = Starten
    int absicht;
    string textabsicht;
    //treibstoff, wie lange reicht er in sekunden
    int treibstoff;

    plane(int sol, int stoff);
    void request();
};


#endif //AIRPORT_PLANE_H
