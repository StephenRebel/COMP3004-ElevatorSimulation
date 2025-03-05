#include "Building.h"

Building::Building(const std::string& owner, int nF, int nE, SimulationController& sC):
    owner(owner), numFloors(nF), numElevators(nE), safetySys(new SafetySystem()) {
    
    for (int i = 1; i < numFloors + 1; i++) {
        floors.push_back(new FloorPanel(i)); // Using 1 based ids for floors so floors will go 1...n
    }

    for (int i = 0; i < numElevators; i++) {
        elevators.push_back(new Elevator(i));
    }

    ECS = new ElevatorControlSystem(elevators);

    simController = sC;
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
    safetySys->triggerAlarm("fire");
    std::cout << "Fire alarm was pulled." << std::endl;
}
