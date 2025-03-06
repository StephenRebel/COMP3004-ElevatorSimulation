#include "Logger.h"
#include "SimulationController.h"

SimulationController* Logger::controller = nullptr;

void Logger::log(const std::string& message) {
    if (controller) {
        controller->logToConsole(message);
    }
}
