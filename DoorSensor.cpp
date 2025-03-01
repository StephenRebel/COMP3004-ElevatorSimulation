#include "DoorSensor.h"

DoorSensor::DoorSensor(int id): elevatorID(id) {}

bool DoorSensor::detectObstacle() {
    std::default_random_engine generator; // Return a random number for whether door is clear or not: https://cplusplus.com/reference/random/bernoulli_distribution/.
    std::bernoulli_distribution distribution(0.75);
    
    return distribution(generator);
}