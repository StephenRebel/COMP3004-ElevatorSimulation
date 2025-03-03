#ifndef DOORSENSOR_H
#define DOORSENSOR_H

#include <random>

class DoorSensor {

    public:
        DoorSensor(int id);

        bool detectObstacle();

    private:
        int elevatorID;
};

#endif // DOORSENSOR_H