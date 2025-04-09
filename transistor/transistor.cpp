#include <iostream>
#include "AndGate.h"
#include "OrGate.h"
#include "Transistor.h"

using namespace std;

int main() {

    Transistor ic0(false);
    Transistor ic1(true);
    Transistor ic2(true);
    Transistor ic3(true);
    
    AndGate andGate0(ic0, ic1);
    AndGate andGate1(ic2, ic3);
    
    OrGate orGate0(ic0, ic1);


    cout << boolalpha;

    //cout << "State: " << ic0.isConducting() << endl;
    //ic0.switchOn();
    //(cout << "State: " << ic0.isConducting() << endl;
    

    cout << "AND Gatter on ic0 and ic1: " << andGate0.output() << endl;
    cout << "OR Gatter on ic0 and ic1: " << andGate1.output() << endl;
    

    return 0;
}
