#include "SimulationController.h"

// Private constructor
SimulationController::SimulationController(int numFloors, int numElevators, int numPassengers):
    numFloors(numFloors), numElevators(numElevators), numPassengers(numPassengers) {
        building = new Building("Stephen", numFloors, numElevators, );
    }

// Create a controller and parse incoming data to make sure it is at least somewhat valid.
SimulationController* SimulationController::createController(int numFloors, int numElevators, int numPassengers, const std::vector<std::string>& passengersJson) {
    SimulationController* controller = new SimulationController(numFloors, numElevators, numPassengers);
    
    // Valid actions to parse in
    std::vector<std::string> validActions{"press_up", "press_help", "press_open_door", "press_close_door"};

    try {
        for(const std::string& jsonStr : passengersJson) {
            json parsedJson = json::parse(jsonStr);

            // Check for minimal passenger info fields
            if (!parsedJson.contains("initial_floor") || !parsedJson.contains("actions")) {
                std::cout << "Error: Missing passenger initialization information.\n";
                delete controller;
                return nullptr;
            }

            int initialFloor = parsedJson["initial_floor"];
            Passenger* p = new Passenger(initialFloor, controller->getBuilding());
            controller->passengers.push_back(p);
            int passengerID = p->getID();

            // Parse out passenger actions
            for (const json& actionJson : parsedJson["actions"]) {
                if (!actionJson.contains("timestep") || !actionJson.contains("action")) {
                    std::cout << "Error: Missing minimal passenger action information.\n";
                    delete controller;
                    return nullptr;
                }

                if (std::find(std::begin(validActions), std::end(validActions), actionJson["action"]) == std::end(validActions)) {
                    std::cout << "Error: Supplied invalid action (" << actionJson["action"] << "). Must be one of ('press_up', 'press_help', 'press_open_door', 'press_close_door').\n";
                    delete controller;
                    return nullptr;
                }

                Action actionEntry = Action(passengerID, actionJson["action"], actionJson.value("destination", -1));
                
                int timestep = actionJson["timestep"];
                controller->eventQueue[timestep].push_back(actionEntry);
            }
        }
    } catch (const std::exception& e) { // Catch any general error during parsing.
        std::cout << "JSON parsing error: " << e.what() << '\n';
        delete controller;
        return nullptr;
    }

    return controller;
}

void SimulationController::notifyPassengers(int elevatorID, int floor, int direction) {
    for (Passenger* p: passengers) {
        if (p->getCurrentFloor == floor && p->getDesiredDirection() == direction) {
            p->notifyElevatorArrival(int elevatorID);
        }
    }
}

// Logging function
void SimulationController::logToConsole(const std::string& message) {
    emit logToConsoleSignal(message);
}

// Simulation Controls (does nothing for now)
void SimulationController::startSimulation() {
    logToConsole("Simulation started with " + std::to_string(numFloors) + " floors, " + std::to_string(numElevators) + " elevators, and " + std::to_string(numPassengers) + " passengers.");
}

void SimulationController::pauseSimulation() {
    logToConsole("Paused");
}

void SimulationController::resumeSimulation() {
    logToConsole("Resumed");
}
