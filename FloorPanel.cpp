#include "FloorPanel.h"
#include "ElevatorControlSystem.h"

FloorPanel::FloorPanel(int id, ElevatorControlSystem& ecs): floorID(id), ECS(ecs) {}

void FloorPanel::pressUp() {
    ECS.assignElevator(floorID, 1);
    Logger::log("Floor " + std::to_string(floorID) + ": Up button pressed. Button remains illuminated.");
}

void FloorPanel::pressDown() {
    ECS.assignElevator(floorID, -1);
    Logger::log("Floor " + std::to_string(floorID) + ": Down button pressed. Button remains illuminated.");
}

void FloorPanel::deIlluminate(int direction) {
    Logger::log("Floor " + std::to_string(floorID) + ": Illuminated " + (direction > 0 ? "UP" : "DOWN") + " button turns off.");
}
