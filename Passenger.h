#ifndef PASSENGER_H
#define PASSENGER_H

#include "Elevator.h"
#include "FloorPanel.h"
#include "Building.h"
#include "Logger.h"

class Passenger {

    public:
        static int LastestID;

        Passenger(int initial_floor, int init_wight, Building& building);

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
        int getCurrentWeight() const { return currentWeight; }
        int getDesiredDirection() const { return desiredDirection; }
        bool isInElevator() const { return inElevator; }
        int getElevatorID() const { return currentElevator->getID(); }
        int getDesiredFloor() const { return desiredFloor; }
        bool isAtFinalFloor() { return (currentFloorNum == finalFloor) && (totalRequests == 0); } // Final floor meaning they are at the final location and don't have anymore floor requests to make.
        bool hasRequest() { return desiredFloor != -1; } // If they don't want to go anywhere right now they are listed as -1.

        void dropWeight(int amount);
        void setFinalFloor(int floor) { finalFloor = floor; }
        void setNumRequests(int reqs) { totalRequests = reqs; }

        std::string reportState() const;

    private:
        int id;
        int currentFloorNum;
        int currentWeight;
        int desiredDirection;
        int desiredFloor;
        bool inElevator;
        int finalFloor;
        int totalRequests; // Total floor requests left a Passenger wants to make.

        Elevator* currentElevator;
        Building& building;
};

#endif // PASSENGER_H
