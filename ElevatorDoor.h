#ifndef ELEVATORDOOR_H
#define ELEVATORDOOR_H

#include <iostream>

#include "DoorSensor.h"

class ElevatorDoor {

    public:
        ElevatorDoor(int id);
        ~ElevatorDoor();

        void open();
        bool close();

    private:
        DoorSensor* dS;
        
        int ElevatorID;
        bool isOpen;
};

#endif // ELEVATORDOOR_H