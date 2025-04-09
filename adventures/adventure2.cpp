#include <iostream>
#include <string>

void entscheidung(std::string richtung) {
    if (richtung == "links") {
        std::cout << "Du gehst nach links und stößt auf ein altes, verlassenes Schloss." << std::endl;
        // Hier kannst du weitere Aktionen oder Entscheidungen hinzufügen
    } else if (richtung == "rechts") {
        std::cout << "Du gehst nach rechts und entdeckst eine dunkle Höhle." << std::endl;
        // Hier kannst du weitere Aktionen oder Entscheidungen hinzufügen
    } else if (richtung == "geradeaus") {
        std::cout << "Du gehst geradeaus und kommst zu einer alten Brücke über einen Fluss." << std::endl;
        // Hier kannst du weitere Aktionen oder Entscheidungen hinzufügen
    } else {
        std::cout << "Das ist keine gültige Richtung. Du bleibst stehen und denkst nach." << std::endl;
    }
}

int main() {
    std::cout << "Du befindest dich in einem dunklen Wald." << std::endl;
    std::cout << "Welchen Weg wählst du? (links/rechts/geradeaus): ";

    std::string richtung;
    std::getline(std::cin, richtung);

    entscheidung(richtung);

    return 0;
}
