#include "Passenger.h"

int Passenger::LastestID = 0;

Passenger::Passenger(int initial_floor_num, Building& building):
    id(++LastestID), currentFloorNum(initial_floor_num), desiredDirection(0), desiredFloor(-1), inElevator(false), currentElevator(nullptr), building(building) {}

void Passenger::requestElevator(int direction, int floor) {
    FloorPanel& fP = building.getFloorPanel(currentFloorNum - 1);
    
    if (direction > 0) {
        fP.pressUp();
        std::cout << "Passenger has pressed up button on floor " << currentFloorNum;
    } else {
        fP.pressDown();
        std::cout << "Passenger has pressed dwon button on floor " << currentFloorNum;
    }

    desiredDirection = direction;
    desiredFloor = floor;
}

void Passenger::enterElevator(Elevator* elevator) {
    if (!inElevator) {
        inElevator = true;
        currentElevator = &elevator;
    }

    requestDestination(desiredFloor);
}

void Passenger::disembarkElevator(int floor) {
    inElevator = false;
    currentElevator = nullptr;

    currentFloorNum = floor;
    desiredDirection = 0;
    desiredFloor = -1;
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

std::string Passenger::reportState() const {
    std::string report = "Passenger: " + std::to_string(id) + ", ";

    if (inElevator) {
        report += "In Elevator: " + std::tostring(getElevatorID()) + ", Destination: " + std::to_string(desiredFloor);
    } else {
        report += "On Floor: " + std::to_string(currentFloorNum);
        if (desiredFloor != -1) {
            report += ", Destination Floor: " + std::to_string(desiredFloor);
        }
    }

    return report;
}