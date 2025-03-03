#ifndef ELEVATORPANEL_H
#define ELEVATORPANEL_H

#include <iostream>
#include <string>

class ElevatorPanel {
    
    public:
        ElevatorPanel(int id);

        void pressButton(int floor);
        void pressOpenDoor();
        void pressCloseDoor();
        void pressHelpButton();

    private:
        int elevatorID;

};

#endif // ELEVATORPANEL_H