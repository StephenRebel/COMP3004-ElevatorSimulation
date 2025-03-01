#include "ElevatorDoor.h"

ElevatorDoor::ElevatorDoor(int id): ElevatorID(id), isOpen(false) {
    dS = new DoorSensor(id);
}

ElevatorDoor::~ElevatorDoor() {
    delete dS;
}

void ElevatorDoor::open() {
    std::cout << "Elevator " << ElevatorID << ": opening doors." << std::endl;
}

bool ElevatorDoor::close() {
    std::cout << "Elevator " << ElevatorID << ": closing doors." << std::endl;
    return dS->detectObstacle();
}