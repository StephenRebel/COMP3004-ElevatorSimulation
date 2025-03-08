#include "SafetySystem.h"

SafetySystem::SafetySystem() {}

void SafetySystem::triggerAlarm(const std::string& code) {
    activeAlarms.push_back(code);

    Logger::log("Safety System: " + code + " alarm triggered");

    // Simulating what might happen triggering things but elevator system handles important things for us elsewhere
    if (code == "fire") {
        Logger::log("Safety System: Activating fire response protocol");
    } else if (code == "powerout") {
        Logger::log("Safety System: Activating emergency power systems");
    }
}
