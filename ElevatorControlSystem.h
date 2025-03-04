#ifndef ELEVATORCONTROLSYSTEM_H
#define ELEVATORCONTROLSYSTEM_H

#include <string>
#include <vector>
#include <limits.h>

#include "SimulationController.h"
#include "Elevator.h"

class ElevatorControlSystem {

    public:
        ElevatorControlSystem(std::vector<Elevator*>& e, SimulationController& sC);

        Elevator* assignElevator(int floor, int direction); // int direction to reflect slight refinement. This is call from floor panel.
        void elevatorArrived(int elevatorID, int floor, int direction);
        void updateElevators();

        void handleSafetyEvent(const std::string& code);

    private:
        std::vector<Elevator*>& elevators;
        SimulationController& simController;
};

#endif // ELEVATORCONTROLSYSTEM_H
