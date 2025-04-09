#include "AndGate.h"

AndGate::AndGate(Transistor& ic0, Transistor& ic1){
    zustand = ic0.isConducting() && ic1.isConducting();
}

bool AndGate::output(){
    return zustand;
}

