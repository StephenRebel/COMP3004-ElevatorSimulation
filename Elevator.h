#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <vector>
#include <string>
#include <algorithm>

#include "ElevatorDoor.h"
#include "AudioSystem.h"
#include "DisplaySystem.h"
#include "FloorSensor.h"
#include "Logger.h"

class ElevatorControlSystem;

class Elevator {

    public:
        Elevator(int id, ElevatorControlSystem& ecs);
        ~Elevator();

        void move();
        void updateDisplays();
        void triggerAlarm(const std::string& code);
        void addDestination(int dest);
        void updateState();
        void closeDoor();

        // Passenger interaction points
        void pressOpenDoor();
        void pressCloseDoor();
        void pressFloor(int floor);
        void pressHelp();

        int getCurrentFloor();
        bool isMoving();
        int getDirection();
        std::vector<int>& getFloorQueue();
        int getID() { return id; }

        std::string reportState() const;

    private:
        int id;
        int currentFloor;
        std::vector<int> destinations;
        bool activeState; // These two states are the implementation of the state: Enum, this seems better.
        int movingDirection; // < 0 for down, 0 > for up.
        
        ElevatorDoor* eD;
        FloorSensor* fS;
        DisplaySystem* dS;
        AudioSystem* aS;

        ElevatorControlSystem& ECS;
};

#endif // ELEVATOR_H
