#ifndef FLOORPANEL_H
#define FLOORPANEL_H

#include "Logger.h"

class ElevatorControlSystem;

class FloorPanel {

    public:
        FloorPanel(int id, ElevatorControlSystem& ecs);

        void pressUp();
        void pressDown();

        void deIlluminate(int direction);

    private:
        int floorID; //aka floor number starting 1 based indexing
        bool isIlluminatedUp;
        bool isIlluminatedDown;
        ElevatorControlSystem& ECS;

};

#endif // FLOORPANEL_H
