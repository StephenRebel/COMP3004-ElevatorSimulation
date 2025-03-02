#ifndef FLOORSENSOR_H
#define FLOORSENSOR_H

#include "Elevator.h"

class FloorSensor {

    public:
        FloorSensor(int id);

        bool detectFloor(Elevator& e);

    private:
        int elevatorID;
};

#endif