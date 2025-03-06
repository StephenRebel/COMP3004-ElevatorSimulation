#include "ElevatorDoor.h"

ElevatorDoor::ElevatorDoor(int id): elevatorID(id), isOpen(false) {
    dS = new DoorSensor(id);
}

ElevatorDoor::~ElevatorDoor() {
    delete dS;
}

void ElevatorDoor::open() {
    Logger::log("Elevator " + std::to_string(elevatorID) + ": opening door");
}

bool ElevatorDoor::close() {
    Logger::log("Elevator " + std::to_string(elevatorID) + ": closing doors");
    return dS->detectObstacle();
}
