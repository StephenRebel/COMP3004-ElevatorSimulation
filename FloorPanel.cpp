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
    // Not sure how to get floor 1 to turn off right now.
    if (direction > 0 && isIlluminatedUp) {
        Logger::log("Floor " + std::to_string(floorID) + ": Illuminated up button turns off.");
        isIlluminatedUp = false;
    } else if (direction < 0 && isIlluminatedDown){
        Logger::log("Floor " + std::to_string(floorID) + ": Illuminated down button turns off.");
        isIlluminatedDown = false;
    } else { // handle case where elevator is idle on a floor and passenger on same floor enters request and gets in idle elevator.
        if (isIlluminatedUp) {
            Logger::log("Floor " + std::to_string(floorID) + ": Illuminated up button turns off.");
            isIlluminatedUp = false;
        }

        if (isIlluminatedDown) {
            Logger::log("Floor " + std::to_string(floorID) + ": Illuminated down button turns off.");
            isIlluminatedDown = false;
        }
    }
}
