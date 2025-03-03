#include "Floor.h"

Floor::Floor(int id): id(id) {
    fP = new FloorPanel(id);
}

Floor::~Floor() {
    delete fP;
}

void Floor::upButtonPressed() {

}

void::Floor::downButtonPressed() {

}