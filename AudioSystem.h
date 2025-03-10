#ifndef AUDIOSYSTEM_H
#define AUDIOSYSTEM_H

#include <iostream>
#include <string>

#include "Logger.h"

class AudioSystem {

    public:
        AudioSystem(int id);

        void ringBell() const;
        void playMessage(const std::string& message) const;
        void connectToOperator() const;

    private:
        int elevatorID;

};

#endif // AUDIOSYSTEM_H
