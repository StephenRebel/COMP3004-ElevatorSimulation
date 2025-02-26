#ifndef SIMULATIONCONTROLLER_H
#define SIMULATIONCONTROLLER_H

#include <vector>
#include <map>
#include <string>
#include "Passenger.h"
#include "Action.h"

class SimulationController {
public:
    // Static function to create a SimulationController
    static SimulationController* createController(
        int numFloors, int numElevators, int numPassengers,
        const std::vector<std::string>& passengersJson);

    void startSimulation();
    void pauseSimulation();
    void resumeSimulation();

    int getNumFloors() { return numFloors; }
    int getNumElevators() { return numElevators; }
    int getNumPassengers() { return numPassengers; }

private:
    // Private constructor to enforce the use of the static function
    SimulationController(int numFloors, int numElevators, int numPassengers);

    std::vector<Passenger*> passengers;  // Store Passenger objects directly
    std::map<int, std::vector<Action>> eventQueue; // Store datastructure of all timesteps and actions taken

    int numFloors;
    int numElevators;
    int numPassengers;

};

#endif // SIMULATIONCONTROLLER_H
