#include "ElevatorControlSystem.h"
#include "SimulationController.h"

ElevatorControlSystem::ElevatorControlSystem(SimulationController& sC): elevators(nullptr), simController(sC) {}

Elevator* ElevatorControlSystem::assignElevator(int floor, int direction) {
    Elevator* bestElevator = nullptr;
    int minDistance = INT_MAX;

    for (Elevator* elev: *elevators) {
        int distance = abs(elev->getCurrentFloor() - floor);

        if (!elev->isMoving()) {
            bestElevator = elev;
            break;
        } else if (elev->getDirection() == direction) {
            if ((direction == 1 && elev->getCurrentFloor() < floor) || (direction == -1 && elev->getCurrentFloor() > floor)) {
                if (distance < minDistance) {
                    bestElevator = elev;
                    minDistance = distance;
                }
            }
        }
    }

    if (!bestElevator) {
        bestElevator = (*elevators)[0]; // If we can't assing a good one based on rules assign this default one.
    }

    bestElevator->addDestination(floor);
    std::cout << "Elevator Control System deemed elevator" << bestElevator->getID() << " for request to floor " << floor << std::endl;
    return bestElevator; // I don't actually use this instead I use a broadcasting sort of to let any passenger at that floor know an elevator arrived.
}

void ElevatorControlSystem::elevatorArrived(int elevatorID, int floor, int direction) {
    simController.notifyPassengers(elevatorID, floor, direction);
    simController.getBuilding().getFloorPanel(floor).deIlluminate(direction);
}

void ElevatorControlSystem::handleSafetyEvent(const std::string& code) {
    // Method for handling safety events being processed.
}

void ElevatorControlSystem::updateElevators() {
    for (Elevator* e: *elevators) {
        if (e->isMoving()) {
            e->move(); // Perhaps moving isn't the right name but oh well
            e->updateDisplays();
        }
        e->updateState();
    }
}

void ElevatorControlSystem::setElevators(std::vector<Elevator *> &e) {
    elevators = &e;
}
