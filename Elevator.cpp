#include "Elevator.h"
#include "ElevatorControlSystem.h"

Elevator::Elevator(int id, ElevatorControlSystem& ecs): id(id), currentFloor(1), activeState(false), movingDirection(0), ECS(ecs) {
    eD = new ElevatorDoor(id);
    fS = new FloorSensor(id);
    dS = new DisplaySystem(id); // Initialize all the elevator components
    aS = new AudioSystem(id);
}

Elevator::~Elevator() {
    delete eD;
    delete fS;
    delete dS;
    delete aS;
}

void Elevator::move() {
    currentFloor += (movingDirection > 0) ? 1 : -1;
    std::cout << "Elevator: " << id << " moved to floor " << currentFloor << std::endl;

    if (fS->detectFloor(*this, currentFloor)) {
        std::cout << "Elevator " << id << " arrived at floor destination " << currentFloor << std::endl;
        eD->open();
        ECS.elevatorArrived(id, currentFloor, movingDirection);
        closeDoor();

        // Remove floor as a destination
        auto it = std::find(destinations.begin(), destinations.end(), currentFloor);
        if (it != destinations.end()) {
            destinations.erase(it);
        }
    }
}

void Elevator::updateState() {
    if (destinations.empty()) {
        movingDirection = 0;
        activeState = false;
        return;
    }

    bool requestsAbove = false;
    bool requestsBelow = false;

    for (int floor: destinations) {
        if (floor > currentFloor) requestsAbove = true;
        if (floor < currentFloor) requestsBelow = true;
    }

    // Positive means up, negative down
    if (movingDirection > 0) {
        if (requestsAbove) return; // Do not change any state keep moving
        if (requestsBelow) movingDirection = -1; // No requests upwards but some downwards
    } else if (movingDirection < 0) {
        if (requestsBelow) return; // Similar logic
        if (requestsAbove) movingDirection = 1;
    } else {
        movingDirection = (destinations.front() > currentFloor) ? 1 : -1; // We aren't moving but have requests so start
        activeState = true;
    }
}

void Elevator::pressOpenDoor() {
    eD->open();
}

void Elevator::closeDoor() {
    int failures = 0;

    while (!eD->close()) {
        std::cout << "Elevator " << id << " door sensor blocked. Retrying..." << std::endl;
        eD->open();
        failures++;

        if (failures == 5) {
            dS->warningMessage("Clear doors.");
            aS->playMessage("Clear doors.");
            failures = 0;
        }
    }
}

void Elevator::pressCloseDoor() {
    closeDoor();
}

void Elevator::pressFloor(int floor) {
    addDestination(floor);
    updateState();
}

void Elevator::pressHelp() {
    std::cout << "Elevator " << id << " help button pressed. Conecting to operator... Conversation terminated." << std::endl;
}

void Elevator::updateDisplays() {
    dS->updateFloor(currentFloor);
}

void Elevator::triggerAlarm(const std::string& code) {
    // handle different allarms, like fire etc.
}

void Elevator::addDestination(int dest) {
    if(std::find(destinations.begin(), destinations.end(), dest) == destinations.end()) {
        destinations.push_back(dest);
        std::cout << "Elevator " << id << " added floor " << dest << " to destination list" << std::endl;
    }
}

int Elevator::getCurrentFloor() {
    return currentFloor;
}

bool Elevator::isMoving() {
    return activeState;
}

int Elevator::getDirection() {
    return movingDirection;
}

std::vector<int>& Elevator::getFloorQueue() {
    return destinations;
}

std::string Elevator::reportState() const {
    std::string report = "Elevator: " + std::to_string(id) + ", Elevator state: ";

    if (activeState) {
        report += "moving, Direction: " + std::string(movingDirection > 0 ? "up" : "down");
    } else {
        report += "idle";
    }

    report += ", Current floor: " + std::to_string(currentFloor);

    return report;
}
