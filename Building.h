#ifndef BUILDING_H
#define BUILDING_H

#include <vector>
#include <string>

#include "Elevator.h"
#include "Floor.h"
#include "ElevatorControlSystem.h"
#include "SafetySystem.h"

class Building {

    public:
        Building(const std::string& owner, int nF);
        ~Building();

        void pullFireAlarm();

    private:
        int numFloors;
        int numElevators;
        std::string owner;

        std::vector<Elevator*> elevators;
        std::vector<Floor*> floors;
        ElevatorControlSystem* ECS;
        SafetySystem* safetySys;
};

#endif