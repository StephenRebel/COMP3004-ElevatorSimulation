#ifndef DISPLAYSYSTEM_H
#define DISPLAYSYSTEM_H

#include <iostream>
#include <string>

class DisplaySystem {

    public:
        DisplaySystem(int id);

        void updateFloor(int floor) const;
        void warningMessage(const std::string& message) const;

    private:
        int elevatorID;
};

#endif // DISPLAYSYSTEM_H