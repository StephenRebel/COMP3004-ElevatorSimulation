#include "Action.h"

Action::Action(int pID, const std::string& action, int dest = -1, int code = -1):
    passengerID(pID), action(action), destination(dest), code(code) {}
