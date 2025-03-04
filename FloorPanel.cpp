#include "FloorPanel.h"

FloorPanel::FloorPanel(int id, ElevatorControlSystem& ecs): floorID(id) {
    ECS = ecs;
}

void FloorPanel::pressUp() { // need to make this call assign elevator.
    ECS->assignElevator(id, 1);
    std::cout << "Floor " << floorID << ": Up button pressed. Button remains illuminated." << std::endl;
}

void FloorPanel::pressDown() {
    ECS->assignElevator(id, -1); 
    std::cout << "Floor " << floorID << ": Down button pressed. Button remains illuminated." << std::endl;
}

void FloorPanel::deIlluminate(int direction) {
    std::cout << "Floor " << floorID << ": Illuminated " << (direction > 0) ? "UP" : "DOWN" << " button turns off." << std::endl;
}