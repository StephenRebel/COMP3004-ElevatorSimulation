#ifndef ACTION_H
#define ACTION_H

#include <string>

class Action {
    
    public:
        Action(int pID, const std::string& action, int dest);

        int passengerID;
        std::string action;
        int destination;
};

#endif //ACTION_H