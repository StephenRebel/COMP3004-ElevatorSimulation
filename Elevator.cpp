#include "Elevator.h"

Elevator::Elevator(int id): id(id), currentFloor(1), activeState(false), movingDirection(-1) {
    eD = new ElevatorDoor();
    fS = new FloorSensor();
    dS = new DisplaySystem(); // Initialize all the elevator components
    aS = new AudioSystem();
    eP = new ElevatorPanel();
}

void Elevator::move() {
    // not sure right now
}

void Elevator::openDoor() {
    eD->open();
}

void Elevator::closeDoor() {
    int failures = 0;

    while (!eD->close()) {
        eD->open();
        failures++;

        if (failures == 5) {
            dS->warningMessage("Clear doors.");
            aS->playMessage("Clear doors.");
            failures = 0;
        }
    }
}

void Elevator::updateDisplays() {
    dS->updateFloor(currentFloor);
}

void Elevator::triggerAlarm(const std::string& code) {
    // handle different allarms, like fire etc.
}