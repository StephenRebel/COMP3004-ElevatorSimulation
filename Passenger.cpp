#include "Passenger.h"

int Passenger::LastestID = 0;

Passenger::Passenger(int initial_floor_num):
    id(++LastestID), currentFloorNum(initial_floor_num), inElevator(false) /*currentElevator(nullptr), currentFloor(nullptr get current floor object)*/ {}

