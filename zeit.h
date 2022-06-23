//
// Created by Luca on 23.06.22.
//

#ifndef AIRPORT_ZEIT_H
#define AIRPORT_ZEIT_H


class zeit {
private:

public:
    int stunde;
    int min;
    int sek;
    zeit (); //konstruktor
    void printtime();
    zeit operator ++ (int nil); // suffix
};


#endif //AIRPORT_ZEIT_H
