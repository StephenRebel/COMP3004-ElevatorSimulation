#ifndef ELEVATORCONTROLSYSTEM_H
#define ELEVATORCONTROLSYSTEM_H

#include <string>

#include "Elevator.h"

class ElevatorControlSystem {

    public:
        ElevatorControlSystem();

        Elevator& assignElevator(int floor, int direction); // int direction to reflect slight refinement. This is call from floor panel.
        void elevatorRequest(const Elevator& e, int floor); // This is a call from inside elevator.
        void handleSafetyEvent(const std::string& code);

    private:

};

#endif // ELEVATORCONTROLSYSTEM_H
