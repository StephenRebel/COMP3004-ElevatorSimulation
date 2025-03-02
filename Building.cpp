#include "Building.h"

Building::Building(const std::string& owner, int nF, int nE):
    owner(owner), numFloors(nF), numElevators(nE), ECS(new ElevatorControlSystem()), safetySys(new SafetySystem()) {
    
    for (int i = 1; i < numFloors + 1; i++) {
        floors.push_back(new Floor(i)); // Using 1 based ids for floors so floors will go 1...n
    }

    for (int i = 0; i < numElevators; i++) {
        elevators.push_back(new Elevator(i));
    }
}

Building::~Building() {
    for (Elevator* e: elevators) {
        delete e;
    }

    for (Floor* f: floors) {
        delete f;
    }

    delete ECS;
    delete safetySys;
}

void Building::pullFireAlarm() {
    safetySys->triggerAlarm("fire");
}