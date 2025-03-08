#include "Passenger.h"

int Passenger::LastestID = 0;

Passenger::Passenger(int initial_floor_num,int init_weight,  Building& building):
    id(++LastestID), currentFloorNum(initial_floor_num), currentWeight(init_weight),desiredDirection(0), desiredFloor(-1), inElevator(false), finalFloor(-1), totalRequests(-1), currentElevator(nullptr), building(building) {}

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

        elevator->addRemoveWeight(currentWeight); // Something like a sensor updating as the passenger walks in.
    }

    requestDestination(desiredFloor);
}

void Passenger::disembarkElevator(int floor) {
    Logger::log("Passenger " + std::to_string(id) + ": exiting elevator " + std::to_string(currentElevator->getID()) + " on floor " + std::to_string(floor));

    currentElevator->addRemoveWeight(-currentWeight);

    inElevator = false;
    currentElevator = nullptr;

    currentFloorNum = floor;
    desiredDirection = 0;
    desiredFloor = -1;
}

void Passenger::requestDestination(int floor) {
    if (inElevator) {
        Logger::log("Passenger " + std::to_string(id) + ": requesting floor " + std::to_string(floor));
        currentElevator->pressFloor(floor);
        totalRequests--;
    }
}

void Passenger::pressHelp(int emergencyCode) {
    if (inElevator) {
        currentElevator->pressHelp(emergencyCode);
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

void Passenger::dropWeight(int amount) {
    if (currentWeight - amount > 0) {
        currentWeight -= amount;
    }
}

void Passenger::safetyOverrideElev(int safeFloor) { // Overriding passenger intentions for safety event.
    finalFloor = safeFloor;
    desiredDirection = 0;
    desiredFloor = safeFloor;
    totalRequests = 0;
}

void Passenger::safetyOverrideFloor() { // Overriding passenger actions for on floor.
    finalFloor = currentFloorNum;
    desiredDirection = 0;
    desiredFloor = -1;
    totalRequests = 0;
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
