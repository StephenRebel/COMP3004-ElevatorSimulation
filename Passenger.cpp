#include "Passenger.h"

int Passenger::LastestID = 0;

Passenger::Passenger(int initial_floor_num, Building& building):
    id(++LastestID), currentFloorNum(initial_floor_num), inElevator(false), currentElevator(nullptr), building(building) {}

void Passenger::requestElevator(int direction) {
    FloorPanel& fP = building.getFloorPanel(currentFloorNum - 1);
    
    if (direction > 0) {
        fP.pressUp();
        std::cout << "Passenger has pressed up button on floor " << currentFloorNum;
    } else {
        fP.pressDown();
        std::cout << "Passenger has pressed dwon button on floor " << currentFloorNum;
    }
}

void Passenger::enterElevator(Elevator* elevator) {
    if (!inElevator) {
        inElevator = true;
        currentElevator = &elevator;
    }
}

void Passenger::requestDestination(int floor) {
    if (inElevator) {
        currentElevator->pressFloor(floor);
    }
}

void Passenger::pressHelp() {
    if (inElevator) {
        currentElevator->pressHelp();
    }
}

void Passenger::holdDoor() {
    if (inElevator) {
        currentElevator->pressOpenDoor();
    }
}

void Passenger::closeDoor() {
    if (inElevator) {
        currentElevator->pressCloseDoor();
    }
}

// Might be redundant I'll think
void Passenger::notifyElevatorArrival(int elevatorID) {
    enterElevator(building.getElevator(elevatorID));
}