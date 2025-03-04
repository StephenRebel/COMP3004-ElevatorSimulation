#include "FloorSensor.h"
#include "Elevator.h"

FloorSensor::FloorSensor(int id): elevatorID(id) {}

bool FloorSensor::detectFloor(Elevator& e, int floor) {
    std::vector<int>& floors = e->getFloorQueue();

    return (std::find(floors.begin(), floors.end(), floor) != floors.end());
}
