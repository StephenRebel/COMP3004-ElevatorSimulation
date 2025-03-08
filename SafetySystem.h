#ifndef SAFETYSYSTEM_H
#define SAFETYSYSTEM_H

#include <string>
#include <vector>

#include "Logger.h"

class SafetySystem {

    public:
        SafetySystem();

        void triggerAlarm(const std::string& code);

    private:
        std::vector<std::string> activeAlarms;

};

#endif // SAFETYSYSTEM_H
