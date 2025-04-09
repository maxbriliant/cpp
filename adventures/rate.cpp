#include <iostream>
#include <cstdlib> // für rand() und srand()
#include <ctime>   // für time()

int main() {
    srand(time(0)); // Initialisiert den Zufallsgenerator

    int secretNumber = rand() % 100 + 1; // Geheime Zahl zwischen 1 und 100
    int attemptsLeft = 7;
    int guess;

    std::cout << "Willkommen beim Rätsel des Artefakts!" << std::endl;
    std::cout << "Errate die geheime Zahl zwischen 1 und 100." << std::endl;
    std::cout << "Du hast maximal 7 Versuche." << std::endl << std::endl;

    while (attemptsLeft > 0) {
        std::cout << "Versuch #" << 8 - attemptsLeft << ": ";
        std::cin >> guess;

        if (guess < secretNumber) {
            std::cout << "Zu niedrig! Versuche es noch einmal." << std::endl;
        } else if (guess > secretNumber) {
            std::cout << "Zu hoch! Versuche es noch einmal." << std::endl;
        } else {
            std::cout << "Glückwunsch! Du hast die geheime Zahl " << secretNumber << " erraten!" << std::endl;
            break;
        }

        attemptsLeft--;
    }

    if (attemptsLeft == 0) {
        std::cout << "Du hast leider alle Versuche aufgebraucht. Die geheime Zahl war " << secretNumber << "." << std::endl;
    }

    return 0;
}
