#ifndef TRANSISTOR_H  // Prüft, ob das Makro nicht definiert ist
#define TRANSISTOR_H  // Definiert das Makro, um ein mehrfaches Einbinden zu verhindern

class Transistor{
    private:
        bool zustand;
        

    public:
        Transistor(bool zustand); //Konstruktor

        bool isConducting();
        void switchOn();
        void switchOff();
        void setState(bool);
};

#endif  // Schließt die #ifndef Direktive ab
