#include <iostream>
#include <string>

void erkundeHöhle(std::string pfad) {
    if (pfad == "beleuchtet") {
        std::cout << "Du wählst den beleuchteten Gang und findest eine alte Schatztruhe!" << std::endl;
        // Hier kannst du weitere Aktionen oder Entscheidungen hinzufügen
    } else if (pfad == "schmal") {
        std::cout << "Du gehst den schmalen Pfad zwischen den Felsen entlang." << std::endl;
        std::cout << "Plötzlich stößt du auf eine Gruppe Fledermäuse, die dich angreifen!" << std::endl;
	std::cout << "Du Iterierst nun über dein Inventar um etwas nützliches zu finden, \nwomit du die COVID Erregenden Tiere abwehren kannst." << std::endl;
    } else if (pfad == "steil") {
        std::cout << "Du kletterst den steilen Aufstieg hinauf und entdeckst eine verborgene Kammer." << std::endl;
        // Hier kannst du weitere Aktionen oder Entscheidungen hinzufügen
    } else {
        std::cout << "Das ist keine gültige Wahl. Du bleibst stehen und überlegst dir deinen nächsten Zug." << std::endl;
    }
}

int main() {
    std::cout << "Du bist in einer dunklen Höhle." << std::endl;
    std::cout << "Welchen Pfad wählst du? (beleuchtet/schmal/steil): ";

    std::string pfad;
    std::getline(std::cin, pfad);

    erkundeHöhle(pfad);

    return 0;
}
