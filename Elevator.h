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
        Elevator(int id, int maxWeight, ElevatorControlSystem& ecs);
        ~Elevator();

        void move();
        void checkFloorArrival();
        void updateDisplays();
        void triggerAlarm(const std::string& code, int safeFloor);
        void addDestination(int dest);
        void updateState();
        void checkWeight();
        void closeDoor();

        // Passenger interaction points
        void pressOpenDoor();
        void pressCloseDoor();
        void pressFloor(int floor);
        void pressHelp(int helpCode);

        int getCurrentFloor();
        bool isMoving();
        int getDirection();
        std::vector<int>& getFloorQueue();
        int getID() { return id; }

        void addRemoveWeight(int weight); // Positive or negative weight amount to add to current weight. Would noramlly be a sensor but I don't have those.

        std::string reportState() const;

    private:
        int id;
        int currentFloor;
        int maxWeight;
        int currentWeight;
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
