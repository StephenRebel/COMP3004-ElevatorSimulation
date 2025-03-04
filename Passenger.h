#ifndef PASSENGER_H
#define PASSENGER_H

#include "Elevator.h"
#include "FloorPanel.h"
#include "Building.h"

class Passenger {

    public:
        static int LastestID;

        Passenger(int initial_floor, Building& building);

        void requestElevator(int direction, int floor);
        void enterElevator(Elevator* elevator);
        void disembarkElevator(int floor);
        void requestDestination(int floor);
        void holdDoor();
        void closeDoor();
        void pressHelp();
        void notifyElevatorArrival(int elevatorID);

        int getID() const { return id; }
        int getCurrentFloor() const { return currentFloorNum; }
        int getDesiredDirection() const { return desiredDirection; }
        bool isInElevator() const { return inElevator; }
        int getElevatorID() const { return currentElevator->getID(); }
        int getDesiredFloor() const { return desiredFloor; }

    private:
        int id;
        int currentFloorNum;
        int desiredDirection;
        int desiredFloor;
        bool inElevator;

        Elevator* currentElevator;
        Building& building;
};

#endif // PASSENGER_H
