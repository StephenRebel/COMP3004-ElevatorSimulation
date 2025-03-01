#include "DisplaySystem.h"

DisplaySystem::DisplaySystem(int id): elevatorID(id) {}

void DisplaySystem::updateFloor(int floor) const {
    std::cout << "Elevator " << elevatorID << ": Update floor display to: " << floor << std::endl;
}

void DisplaySystem::warningMessage(const std::string& message) const {
    std::cout << "Elevator " << elevatorID << ": Display system displayed message: " << message << std::endl;
}