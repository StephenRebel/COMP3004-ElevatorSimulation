#ifndef PASSENGER_H
#define PASSENGER_H

//#include "Elevator.h"
//#include "Floor.h"

class Passenger {

    public:
        static int LastestID;

        Passenger(int initial_floor);

        int getID() const { return id; }
        int getCurrentFloor() const { return currentFloorNum; }

    private:
        int id;
        int currentFloorNum;
        bool inElevator;

        // Think I will resolve the location attribute by storing two different pointers and a boolean.        
        //Elevator* currentElevator;
        //Floor* currentFloor;
};

#endif // PASSENGER_H
