#include "ElevatorControlSystem.h"

ElevatorControlSystem::ElevatorControlSystem() {}

Elevator& assignElevator(int floor, int direction) {
    // Do elevator allocation strategy and report which one is coming.
    static Elevator dummyElevator(-1);
    return  dummyElevator;
}

void elevatorRequest(const Elevator& e, int floor) {
    // This call is a click on elevator internal buttons
}

void handleSafetyEvent(const std::string& code) {
    // Method for handling safety events being processed.
}
