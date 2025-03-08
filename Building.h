#ifndef BUILDING_H
#define BUILDING_H

#include <string>
#include <vector>

#include "Elevator.h"
#include "FloorPanel.h"
#include "ElevatorControlSystem.h"
#include "SafetySystem.h"
#include "Logger.h"

class SimulationController;

class Building {

    public:
        Building(const std::string& owner, int nF, int nE, SimulationController& sC);
        ~Building();

        void pullFireAlarm();
        void triggerPowerOut();
        void updateECS();
        std::string reportECS() const;
        void connectBuildingSafety(int code);

        FloorPanel& getFloorPanel(int floor) { return *(floors[floor - 1]); } // -1 for 1 based indexing of floors
        Elevator* getElevator(int elevatorID) { return elevators[elevatorID]; }
        int getSafeFloor() { return safeFloor; }
        std::vector<Elevator*>& getElevators() { return elevators; }

    private:
        std::string owner;
        int numFloors;
        int numElevators;

        int safeFloor; // Hardcoding safe floor, could pass it but makes no difference.

        std::vector<Elevator*> elevators;
        std::vector<FloorPanel*> floors;
        ElevatorControlSystem* ECS;
        SafetySystem* safetySys;

        SimulationController& simController;
};

#endif // BUILDING_H
