#ifndef LOGGER_H
#define LOGGER_H

#include <string>

class SimulationController;

class Logger {

    private:
        static SimulationController* controller;

    public:
        static void setController(SimulationController* simCont) { controller = simCont; }

        static void log(const std::string& message);
};

#endif // LOGGER_H
