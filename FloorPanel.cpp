#include "FloorPanel.h"
#include "ElevatorControlSystem.h"

FloorPanel::FloorPanel(int id, ElevatorControlSystem& ecs): floorID(id), isIlluminatedUp(false), isIlluminatedDown(false), ECS(ecs) {}

void FloorPanel::pressUp() {
    Logger::log("Floor " + std::to_string(floorID) + ": Up button pressed. Button remains illuminated.");
    isIlluminatedUp = true;
    ECS.assignElevator(floorID, 1);
}

void FloorPanel::pressDown() {
    Logger::log("Floor " + std::to_string(floorID) + ": Down button pressed. Button remains illuminated.");
    isIlluminatedDown = true;
    ECS.assignElevator(floorID, -1);
}

void FloorPanel::deIlluminate(int direction) {
    if (direction > 0) {
        isIlluminatedUp = false;
    } else {
        isIlluminatedDown = false;
    }
    Logger::log("Floor " + std::to_string(floorID) + ": Illuminated " + (direction > 0 ? "UP" : "DOWN") + " button turns off.");
}
