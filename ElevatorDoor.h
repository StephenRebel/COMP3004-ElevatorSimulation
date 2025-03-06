#ifndef ELEVATORDOOR_H
#define ELEVATORDOOR_H

#include <iostream>

#include "DoorSensor.h"
#include "Logger.h"

class ElevatorDoor {

    public:
        ElevatorDoor(int id);
        ~ElevatorDoor();

        void open();
        bool close();

    private:
        DoorSensor* dS;
        
        int elevatorID;
        bool isOpen;
};

#endif // ELEVATORDOOR_H
