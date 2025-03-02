#ifndef SIMULATIONCONTROLLER_H
#define SIMULATIONCONTROLLER_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <QObject>

#include <nlohmann/json.hpp> // Quick google to find best c++ json parsing library, find the git repo

using json = nlohmann::json;

#include "Passenger.h"
#include "Action.h"

class SimulationController : public QObject {
        Q_OBJECT

    public:
        // Static function to create a SimulationController
        static SimulationController* createController(int numFloors, int numElevators, int numPassengers, const std::vector<std::string>& passengersJson);

        void startSimulation();
        void pauseSimulation();
        void resumeSimulation();

        void logToConsole(const std::string& message);

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

    signals:
        void logToConsoleSignal(const std::string& message);
};

#endif // SIMULATIONCONTROLLER_H
