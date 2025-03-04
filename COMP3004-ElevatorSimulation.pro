QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    Passenger.cpp \
    SimulationController.cpp \
    Action.cpp \
    Building.cpp \
    ElevatorControlSystem.cpp \ 
    Elevator.cpp \
    ElevatorDoor.cpp \
    DoorSensor.cpp \
    ElevatorPanel.cpp \
    AudioSystem.cpp \
    DisplaySystem.cpp \
    FloorPanel.cpp \
    FloorSensor.cpp \
    SafetySystem.cpp

HEADERS += \
    mainwindow.h \
    Passenger.h \
    SimulationController.h \
    Action.h \
    Building.h \
    ElevatorControlSystem.h \ 
    Elevator.h \
    ElevatorDoor.h \
    DoorSensor.h \
    ElevatorPanel.h \
    AudioSystem.h \
    DisplaySystem.h \
    FloorPanel.h \
    FloorSensor.h \
    SafetySystem.h


FORMS += \
    mainwindow.ui

INCLUDEPATH += $$PWD/nlohmann

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
