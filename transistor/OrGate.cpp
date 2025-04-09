#include "Transistor.h"
#include "OrGate.h"

OrGate::OrGate(Transistor& ic0, Transistor& ic1){
    zustand = ic0.isConducting() || ic1.isConducting();
}

bool OrGate::output(){
    return zustand;
}

