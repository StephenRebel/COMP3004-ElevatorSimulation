#ifndef FLOORPANEL_H
#define FLOORPANEL_H

#include <iostream>

class FloorPanel {

    public:
        FloorPanel(int id);

        void pressUp();
        void pressDown();

    private:
        int floorID; //aka floor number

};

#endif // FLOORPANEL_H