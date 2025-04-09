#include "Transistor.h"

Transistor::Transistor(bool state){
    zustand = state;
}

bool Transistor::isConducting(){
    return zustand;
}

void Transistor::switchOn(){
    zustand = true;
}

void Transistor::switchOff(){
    zustand = false;
}

