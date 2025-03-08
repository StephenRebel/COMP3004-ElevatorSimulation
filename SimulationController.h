#ifndef SIMULATIONCONTROLLER_H
#define SIMULATIONCONTROLLER_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <QObject>
#include <QTimer>
#include <QElapsedTimer>
#include <QDebug>

#include <nlohmann/json.hpp> // Quick google to find best c++ json parsing library, find the git repo

using json = nlohmann::json;

#include "Passenger.h"
#include "Action.h"
#include "Logger.h"

class SimulationController : public QObject {
        Q_OBJECT

    public:
        // Static function to create a SimulationController
        static SimulationController* createController(int numFloors, int numElevators, int numPassengers, const std::vector<std::string>& passengersJson, const std::string& safetyStr = "none", int safetyTime = -1);
        ~SimulationController();

        void startSimulation();
        void pauseSimulation();
        void resumeSimulation();
        void stopSimulation();

        void logToConsole(const std::string& message);
        void notifyPassengers(int elevatorID, int floor, int direction);
        void requestWeightDrop(int elevatorID);

        int getNumFloors() { return numFloors; }
        int getNumElevators() { return numElevators; }
        int getNumPassengers() { return numPassengers; }
        Building& getBuilding() { return *building; }

    private:
        // Private constructor to enforce the use of the static function
        SimulationController(int numFloors, int numElevators, int numPassengers, const std::string& safetyStr = "none", int safetyTime = -1);

        // Simulation loop variables
        QTimer* simulationTimer;
        int currentTimestep;
        bool isPaused;

        std::vector<Passenger*> passengers;  // Store Passenger objects directly
        std::map<int, std::vector<Action>> eventQueue; // Store datastructure of all timesteps and actions taken
        Building* building;

        int numFloors;
        int numElevators;
        int numPassengers;

        std::string safetyEventCode;
        int safetyEventTimestep;
        bool safetyActive;

        // Simulation loop functions and helpers
        void simulationStep();

        void processPassengerActions();
        void processElevatorSystemUpdates();
        void checkAndTriggerEvents();
        void updatePassengerDestination(int safeFloor);
        void reportSystemState();
        void checkSimulationCompletion();

    private slots:
        void onTimerTick();

    signals:
        void logToConsoleSignal(const std::string& message);
        void simulationEndedSignal();
        // may want signals for when the simulation ends/stops.
};

#endif // SIMULATIONCONTROLLER_H

// Have to write the main simulation looping event loop now. Think of order of things to call think elevators move first then passenger calls.
