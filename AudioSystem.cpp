#include "AudioSystem.h"

AudioSystem::AudioSystem(int id): elevatorID(id) {}

void AudioSystem::ringBell() const {
    std::cout << "Elevator " << elevatorID << ": rings bell 'Ding!'" << std::endl;
}

void AudioSystem::playMessage(const std::string& message) const {
    std::cout << "Elevator " << elevatorID << ": Audio System outputs: " << message << std::endl;
}

void AudioSystem::connectToOperator() const {
    std::cout << "Elevator " << elevatorID << ": Connecting to operator...\nCommunicating with operator...\nConnection closed."  << std::endl;
}