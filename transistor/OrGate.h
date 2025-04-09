#ifndef ORGATE_H  // Prüft, ob das Makro noch nicht definiert wurde
#define ORGATE_H  // Definiert das Makro, wenn es nicht bereits definiert wurde

#include "Transistor.h"

class OrGate{
    
    private: //Attribute
        bool zustand;

    public: //Konstruktor
        OrGate(Transistor& ic0, Transistor& ic1);
        
        bool output();

};


#endif  // Schließt die #ifndef Direktive ab
