#ifndef FLOOR_H
#define FLOOR_H

#include "FloorPanel.h"

class Floor {

    public:
        Floor(int id);
        ~Floor();

        void upButtonPressed();
        void downButtonPressed();

    private:
        int id;

        FloorPanel* fP;

};

#endif // FLOOR_H