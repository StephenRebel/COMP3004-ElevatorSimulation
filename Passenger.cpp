#include "Passenger.h"

int Passenger::LastestID = 0;

Passenger::Passenger(int initial_floor_num, Building& building):
    id(++LastestID), currentFloorNum(initial_floor_num), desiredDirection(0), desiredFloor(-1), inElevator(false), finalFloor(-1), currentElevator(nullptr), building(building) {}

void Passenger::requestElevator(int direction, int floor) {
    if (!inElevator){
        FloorPanel& fP = building.getFloorPanel(currentFloorNum);

        if (direction > 0) {
            Logger::log("Passenger " + std::to_string(id) + ": has pressed up button on floor " + std::to_string(currentFloorNum));
            fP.pressUp();
        } else {
            Logger::log("Passenger " + std::to_string(id) + ": has pressed down button on floor " + std::to_string(currentFloorNum));
            fP.pressDown();
        }

        desiredDirection = direction;
        desiredFloor = floor;
    }
}

void Passenger::enterElevator(Elevator* elevator) {
    if (!inElevator) {
        Logger::log("Passenger " + std::to_string(id) + ": entering elevator " + std::to_string(elevator->getID()));
        inElevator = true;
        currentElevator = elevator;
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

void Passenger::notifyElevatorArrival(int elevatorID) {
    enterElevator(building.getElevator(elevatorID));
}

std::string Passenger::reportState() const {
    std::string report = "Passenger: " + std::to_string(id) + ", ";

    if (inElevator) {
        report += "In Elevator: " + std::to_string(getElevatorID()) + ", Destination: " + std::to_string(desiredFloor);
    } else {
        report += "On Floor: " + std::to_string(currentFloorNum);
        if (desiredFloor != -1) {
            report += ", Destination Floor: " + std::to_string(desiredFloor);
        }
    }

    return report;
}
