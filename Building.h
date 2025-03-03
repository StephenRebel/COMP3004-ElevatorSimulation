#ifndef BUILDING_H
#define BUILDING_H

#include <string>
#include <vector>

#include "Elevator.h"
#include "Floor.h"
#include "ElevatorControlSystem.h"
#include "SafetySystem.h"

class Building {

    public:
        Building(const std::string& owner, int nF, int nE);
        ~Building();

        void pullFireAlarm();

    private:
        std::string owner;
        int numFloors;
        int numElevators;

        std::vector<Elevator*> elevators;
        std::vector<Floor*> floors;
        ElevatorControlSystem* ECS;
        SafetySystem* safetySys;
};

#endif // BUILDING_H
