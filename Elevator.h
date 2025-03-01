#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <vector>
#include <string>

#include "ElevatorDoor.h"
#include "AudioSystem.h"
#include "DisplaySystem.h"
#include "ElevatorPanel.h"
#include "FloorSensor.h"

class Elevator {

    public:
        Elevator(int id);
        ~Elevator();

        void move();
        void openDoor();
        void closeDoor();
        void updateDisplays();
        void triggerAlarm(const std::string& code);

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
        ElevatorPanel* eP;

};

#endif