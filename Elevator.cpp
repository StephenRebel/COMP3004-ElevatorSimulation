#include "Elevator.h"
#include "ElevatorControlSystem.h"

Elevator::Elevator(int id, int maxWeight, ElevatorControlSystem& ecs): id(id), currentFloor(1), maxWeight(maxWeight), currentWeight(0), activeState(false), movingDirection(0), ECS(ecs) {
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
    Logger::log("Elevator " + std::to_string(id) + ": moved to floor " + std::to_string(currentFloor));
}

void Elevator::checkFloorArrival() {
    if (fS->detectFloor(*this, currentFloor)) {
        // Remove floor as a destination
        auto it = std::find(destinations.begin(), destinations.end(), currentFloor);
        if (it != destinations.end()) {
            destinations.erase(it);
        }
        updateState();

        Logger::log("Elevator " + std::to_string(id) + " arrived at floor destination " + std::to_string(currentFloor));
        aS->ringBell();
        eD->open();
        ECS.elevatorArrived(id, currentFloor, movingDirection);
        aS->ringBell();
        closeDoor();
    }
}

void Elevator::checkWeight() { // Perhaps could have stored passenger pointer in elevator or ecs and would make this all easier but that would also prompt a rework of entire system.
    if (currentWeight > maxWeight) {
        Logger::log("Elevator " + std::to_string(id) + " exceeded maximum weight " + std::to_string(currentWeight) + "/" + std::to_string(maxWeight));
        dS->warningMessage("Warning overloaded. Please decrease weight to begin moving.");
        aS->playMessage("Warning overloaded. Please decrease weight to begin moving.");

        while (currentWeight > maxWeight) {
            ECS.overloadNotify(id);
        }

        Logger::log("Elevator " + std::to_string(id) + " weight reduced " + std::to_string(currentWeight) + "/" + std::to_string(maxWeight));
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

    while (not eD->close()) {
        Logger::log("Elevator " + std::to_string(id) + " door sensor blocked. Retrying...");
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
    Logger::log("Elevator " + std::to_string(id) + ": help button pressed. Conecting to operator... Conversation terminated.");
}

void Elevator::updateDisplays() {
    dS->updateFloor(currentFloor);
    aS->playMessage("floor " + std::to_string(currentFloor));
}

void Elevator::triggerAlarm(const std::string& code, int safeFloor) {
    Logger::log("Elevator " + std::to_string(id) + ": handling " + code + " safety event.");
    std::string upper = code;
    std::transform(upper.begin(), upper.end(), upper.begin(), ::toupper);

    dS->warningMessage(upper + " ALARM: proceeding to safe floor " + std::to_string(safeFloor));
    aS->playMessage(upper + " ALARM: proceeding to safe floor " + std::to_string(safeFloor));

    destinations.clear();

    if (currentFloor != safeFloor) {
        destinations.push_back(safeFloor);
    }
}

void Elevator::addDestination(int dest) {
    if(std::find(destinations.begin(), destinations.end(), dest) == destinations.end()) {
        destinations.push_back(dest);
        updateState();
        Logger::log("Elevator " + std::to_string(id) + " added floor " + std::to_string(dest) + " to destination list");
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

void Elevator::addRemoveWeight(int weight) {
    currentWeight += weight;
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
