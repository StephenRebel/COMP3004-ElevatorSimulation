#include "Building.h"
#include "SimulationController.h"

Building::Building(const std::string& owner, int nF, int nE, SimulationController& sC):
    owner(owner), numFloors(nF), numElevators(nE), safeFloor(1), ECS(nullptr), safetySys(new SafetySystem()), simController(sC) {

    ECS = new ElevatorControlSystem(sC);

    for (int i = 1; i < numFloors + 1; i++) {
        floors.push_back(new FloorPanel(i, *ECS)); // Using 1 based ids for floors so floors will go 1...n
    }

    for (int i = 0; i < numElevators; i++) {
        elevators.push_back(new Elevator(i, 600, *ECS)); // For now just setting max weight to default 600 units say kg.
    }

    ECS->setElevators(elevators);
}

Building::~Building() {
    for (Elevator* e: elevators) {
        delete e;
    }

    for (FloorPanel* f: floors) {
        delete f;
    }

    delete ECS;
    delete safetySys;
}

void Building::pullFireAlarm() {
    Logger::log("Building: Fire alarm was pulled.");
    safetySys->triggerAlarm("fire");

    ECS->handleSafetyEvent("fire", safeFloor);
}

void Building::triggerPowerOut() {
    safetySys->triggerAlarm("powerout");
    Logger::log("Building: Power outage occured.");

    ECS->handleSafetyEvent("powerout", safeFloor);
}

void Building::updateECS() {
    ECS->updateElevators();
}

std::string Building::reportECS() const {
    return ECS->reportState();
}

void Building::connectBuildingSafety(int code) {
    safetySys->connectOperator(code);
}
