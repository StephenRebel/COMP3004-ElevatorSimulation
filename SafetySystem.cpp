#include "SafetySystem.h"

SafetySystem::SafetySystem() {}

void SafetySystem::triggerAlarm(const std::string& code) {
    activeAlarms.push_back(code);
}