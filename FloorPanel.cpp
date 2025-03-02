#include "FloorPanel.h"

FloorPanel::FloorPanel(int id): floorID(id) {}

void FloorPanel::pressUp() {
    std::cout << "Floor " << floorID << ": Up button pressed. Button remains illuminated." << std::endl;
}

void FloorPanel::pressDown() {
    std::cout << "Floor " << floorID << ": Down button pressed. Button remains illuminated." << std::endl;
}