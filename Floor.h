#ifndef FLOOR_H
#define FLOOR_H

#include "FloorPanel.h"

class Floor {

    public:
        Floor(int id);
        ~Floor();

        void pressUpButton();
        void pressDownButton();

    private:
        int id;

        FloorPanel* fP;

};

#endif