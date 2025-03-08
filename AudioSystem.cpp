#include "AudioSystem.h"

AudioSystem::AudioSystem(int id): elevatorID(id) {}

void AudioSystem::ringBell() const {
    Logger::log("Elevator " + std::to_string(elevatorID) + ": rings bell Ding!");
}

void AudioSystem::playMessage(const std::string& message) const {
    Logger::log("Elevator " + std::to_string(elevatorID) + ": Audio System outputs: " + message);
}

void AudioSystem::connectToOperator() const {
    Logger::log("Elevator " + std::to_string(elevatorID) + ": Connecting to operator...");
}
