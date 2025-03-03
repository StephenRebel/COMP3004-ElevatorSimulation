#ifndef FLOORSENSOR_H
#define FLOORSENSOR_H

class Elevator;

class FloorSensor {

    public:
        FloorSensor(int id);

        bool detectFloor(Elevator& e);

    private:
        int elevatorID;
};

#endif // FLOORSENSOR_H
