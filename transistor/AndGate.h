#ifndef ANDGATE_H  // Prüft, ob das Makro noch nicht definiert wurde
#define ANDGATE_H  // Definiert das Makro, wenn es nicht bereits definiert wurde

#include "Transistor.h"

class AndGate{
    
    private: //Attribute
        bool zustand;

    public: //Konstruktor
        AndGate(Transistor& ic0, Transistor& ic1);
        
        bool output();

};

#endif  // Schließt die #ifndef Direktive ab
