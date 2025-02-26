#include "Action.h"

Action::Action(int pID, const std::string& action, int dest = -1):
    passengerID(pID), action(action), destination(dest) {}