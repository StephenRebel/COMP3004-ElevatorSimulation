#include "SimulationController.h"

// Private constructor
SimulationController::SimulationController(int numFloors, int numElevators, int numPassengers):
    numFloors(numFloors), numElevators(numElevators), numPassengers(numPassengers), currentTimestep(0), isPaused(false) {
        building = new Building("Stephen", numFloors, numElevators, *this);

        // Simulator looping setup
        simulationTimer = new QTimer(this);
        connect(simulationTimer, &QTimer::timeout, this, &SimulationController::onTimerTick);

        simulationTimer->setInterval(2000); // 2 seconds per timestep tick
    }

SimulationController::~SimulationController() {
    delete building;

    for (Passenger* p: passengers) {
        delete p;
    }
}

// Create a controller and parse incoming data to make sure it is at least somewhat valid.
// Might still need to do bounds checking on passed in floors and such for actions.
SimulationController* SimulationController::createController(int numFloors, int numElevators, int numPassengers, const std::vector<std::string>& passengersJson) {
    SimulationController* controller = new SimulationController(numFloors, numElevators, numPassengers);
    
    // Valid actions to parse in
    std::vector<std::string> validActions{"press_up", "press_down", "press_help", "press_open_door", "press_close_door"};

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
                    std::cout << "Error: Supplied invalid action (" << actionJson["action"] << "). Must be one of ('press_up', 'press_down', 'press_help', 'press_open_door', 'press_close_door').\n";
                    delete controller;
                    return nullptr;
                }

                int floor = actionJson.value("destination", -1);
                Action actionEntry = Action(passengerID, actionJson["action"], floor);
                
                int timestep = actionJson["timestep"];
                controller->eventQueue[timestep].push_back(actionEntry);

                if (floor != -1) {
                    p->setFinalFloor(floor);
                }
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
        if (!p->isInElevator()) {
            if (p->getCurrentFloor() == floor && p->getDesiredDirection() == direction) {
                p->notifyElevatorArrival(elevatorID);
            }
        } else {
            if (p->getElevatorID() == elevatorID && p->getDesiredFloor() == floor) {
                p->disembarkElevator(floor);
            }
        }
    }
}

void SimulationController::onTimerTick() {
    if (isPaused) return;

    simulationStep();
}

void SimulationController::simulationStep() {
    logToConsole("---------- Timestep: " + std::to_string(currentTimestep) + " ----------");

    // Might want try catch for any errors.
    processPassengerActions();

    processElevatorSystemUpdates();

    checkAndTriggerEvents();

    reportSystemState();

    checkSimulationCompletion();
}

void SimulationController::processPassengerActions() {
    auto events = eventQueue.find(currentTimestep);

    if (events != eventQueue.end()) { // Events exist for this timestep
        for (const Action& action: events->second) {
            auto passengerIt = std::find_if(passengers.begin(), passengers.end(), [&action](Passenger* p) { return p->getID() == action.passengerID; });
            if (passengerIt == passengers.end()) {
                logToConsole("Error: No passenger found with ID " + std::to_string(action.passengerID));
                continue;
            }

            Passenger* passenger = *passengerIt;

            // can't swtich case on strings...
            if (action.action == "press_up") {
                passenger->requestElevator(1, action.destination);
            } else if (action.action == "press_down") {
                passenger->requestElevator(-1, action.destination);
            } else if (action.action == "press_open_door") {
                passenger->holdDoor();
            } else if (action.action == "press_close_door") {
                passenger->closeDoor();
            } else if (action.action == "press_help") {
                passenger->pressHelp();
            } else {
                logToConsole("Passenger: " + std::to_string(passenger->getID()) + " attemtped invalid action: " + action.action);
            }
        }
    }
}

void SimulationController::processElevatorSystemUpdates() {
    building->updateECS();
}

void SimulationController::checkAndTriggerEvents() {
    // Function to be implemented for safety conditions.
}

void SimulationController::reportSystemState() {
    logToConsole(building->reportECS());

    for (Passenger* p: passengers) {
        logToConsole(p->reportState());
    }

    for (Elevator* e: building->getElevators()) {
        logToConsole(e->reportState());
    }
}

void SimulationController::checkSimulationCompletion() {
    bool processedAllEvents = eventQueue.empty() || (currentTimestep > eventQueue.rbegin()->first);

    bool allElevatorsIdle = std::all_of(building->getElevators().begin(), building->getElevators().end(), [](Elevator* e) { return not(e->isMoving()); });

    bool passengersAtFinalFloor = std::all_of(passengers.begin(), passengers.end(), [](Passenger* p) { return p->isAtFinalFloor(); });

    if (processedAllEvents && allElevatorsIdle && passengersAtFinalFloor) {
        logToConsole("Simulation ran to completion");
        stopSimulation();
    }
}

// Logging function
void SimulationController::logToConsole(const std::string& message) {
    emit logToConsoleSignal(message);
}

// Simulation Controls (does nothing for now)
void SimulationController::startSimulation() {
    /* //Might be useful in resetting simulation and ensuring values.
    currentTimestep = 0;
    isPaused = false;

    logToConsole("Simulation started"); // Can cahnge detail of message here might want to include basic satrt parameters like num of things expected time idk.

    simulationTimer->start();
     */

    logToConsole("Simulation started with " + std::to_string(numFloors) + " floors, " + std::to_string(numElevators) + " elevators, and " + std::to_string(numPassengers) + " passengers.");

    // View event list for now
    for (auto it = eventQueue.begin(); it != eventQueue.end(); ++it) {
        int eventTime = it->first;
        const std::vector<Action>& actions = it->second;

        logToConsole("Event Time: " + std::to_string(eventTime));
        for (const auto& action : actions) {
            logToConsole("  Passenger ID: " + std::to_string(action.passengerID) + ", Action: " + action.action + ", Destination: " + std::to_string(action.destination));
        }
        logToConsole("------------------------");
    }
}

void SimulationController::pauseSimulation() {
    isPaused = true;
    simulationTimer->stop();

    logToConsole("Pausing Simulation at timestep: " + std::to_string(currentTimestep));
}

void SimulationController::resumeSimulation() {
    isPaused = false;
    simulationTimer->start();

    logToConsole("Resumed");
}

void SimulationController::stopSimulation() {
    simulationTimer->stop();
    logToConsole("Simulation stopped at timestep: " + std::to_string(currentTimestep));

    emit simulationEndedSignal();
}
