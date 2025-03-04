#ifndef BUILDING_H
#define BUILDING_H

#include <string>
#include <vector>

#include "SimulationController.h"
#include "Elevator.h"
#include "FloorPanel.h"
#include "ElevatorControlSystem.h"
#include "SafetySystem.h"

class Building {

    public:
        Building(const std::string& owner, int nF, int nE, SimulationController& sC);
        ~Building();

        void pullFireAlarm();
        FloorPanel& getFloorPanel(int floor) { return *(floors[floor]); }
        Elevator* getElevator(int elevatorID) { return elevators[elevatorID]; }

    private:
        std::string owner;
        int numFloors;
        int numElevators;

        std::vector<Elevator*> elevators;
        std::vector<FloorPanel*> floors;
        ElevatorControlSystem* ECS;
        SafetySystem* safetySys;

        SimulationController& simController;
};

#endif // BUILDING_H
