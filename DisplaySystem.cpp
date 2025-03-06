#include "DisplaySystem.h"

DisplaySystem::DisplaySystem(int id): elevatorID(id) {}

void DisplaySystem::updateFloor(int floor) const {
    Logger::log("Elevator " + std::to_string(elevatorID) + ": Update floor display to: " + std::to_string(floor));
}

void DisplaySystem::warningMessage(const std::string& message) const {
    Logger::log("Elevator " + std::to_string(elevatorID) + ": Display system displayed message: " + message);
}
