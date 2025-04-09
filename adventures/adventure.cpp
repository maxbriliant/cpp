#include <iostream>
#include <string>

int main() {
    std::string name;

    std::cout << "Wie heißt du? ";
    std::getline(std::cin, name);

    std::cout << "Willkommen, " << name << "! Kleenscher Knob, Weiter gehts!" << std::endl;

    return 0;
}
