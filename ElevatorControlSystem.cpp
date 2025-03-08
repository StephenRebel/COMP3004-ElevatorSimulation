#include "ElevatorControlSystem.h"
#include "SimulationController.h"

ElevatorControlSystem::ElevatorControlSystem(SimulationController& sC): elevators(nullptr), simController(sC), safetyEventOccuring(false) {}

void ElevatorControlSystem::assignElevator(int floor, int direction) {
    Elevator* bestElevator = nullptr;
    int minDistance = INT_MAX;

    for (Elevator* elev: *elevators) {
        if (elev->isAvailable()) {
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
    }

    if (!bestElevator) {
        for (Elevator* e: *elevators) {
            if (e->isAvailable()) {
                bestElevator = e; // Assign first default one available.
                break;
            }
        }
    }

    if (!bestElevator) {
        Logger::log("CRITICAL ERROR: No Elevator was available, system unable to continue");
        simController.stopSimulation();
    } else {
        Logger::log("Elevator Control System deemed elevator " + std::to_string(bestElevator->getID()) + " for request to floor " + std::to_string(floor));
        bestElevator->addDestination(floor);
    }
}

void ElevatorControlSystem::elevatorArrived(int elevatorID, int floor, int direction) {
    simController.notifyPassengers(elevatorID, floor, direction);
    simController.getBuilding().getFloorPanel(floor).deIlluminate(direction);
}

void ElevatorControlSystem::overloadNotify(int elevatorID) {
    simController.requestWeightDrop(elevatorID);
}

void ElevatorControlSystem::handleSafetyEvent(const std::string& code, int safeFloor) {
    Logger::log("Elevator control sysetem handling " + code + " safety event.");
    safetyEventOccuring = true;

    for (Elevator* e: *elevators) {
        e->triggerAlarm(code, safeFloor);
    }
}

void ElevatorControlSystem::handleHelpEvent(int elevatorID) {
    Logger::log("Elevator control sysetem handling help unresponsive safety event.");
    safetyEventOccuring = true;

    simController.notifyHelpEvent(elevatorID);
}

void ElevatorControlSystem::connectToOperator(int elevatorId, int code) {
    Logger::log("Elevator Control System connecting elevator " + std::to_string(elevatorId) + " to safety operator.");
    simController.getBuilding().connectBuildingSafety(code);
}

void ElevatorControlSystem::updateElevators() {
    for (Elevator* e: *elevators) {
        e->checkFloorArrival();
        e->checkWeight();
        e->updateState();

        if (e->isMoving()) {
            e->move(); // Perhaps moving isn't the right name but oh well
            e->updateDisplays();
        }
    }
}

void ElevatorControlSystem::setElevators(std::vector<Elevator *> &e) {
    elevators = &e;
}

int ElevatorControlSystem::getSafeFloor() {
    return simController.getBuilding().getSafeFloor();
}

std::string ElevatorControlSystem::reportState() const {
    if (safetyEventOccuring) {
        return "Elevator Control System handling safey condition";
    } else {
        return "Elevator Control System operating normally";
    }
}
