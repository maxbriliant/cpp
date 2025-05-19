#include <vector>
#include <iostream>
#include <string>

using namespace std;

int main () {
    // Deklariere Vector vom <TYP> string 
    vector <string> names {"1","2","3","4","5","6"};
    
    // Hole den Iterator aus names.begin() 
    // DATENTYP: auto hier besser wahl
    // Für CONST Iteratoren mit cbegin() und cend() inintialisieren
    // Wenn änderungen am Ziel erwünscht sind mit -- auto it = names.being() -- initialisieren
    // Prüfe darauf, ob der Iterator schon auf das Ende Zeigt
    // Inkremetiere ganz normal den Iterator
    
    for (std::vector<std::string>::const_iterator it = names.cbegin(); it != names.cend(); ++it) {
            // DEREFERENZIERE den Iterator mit * ->>> Das ist der Wichtigste Punkt.
        cout << *it << endl;
    }
}