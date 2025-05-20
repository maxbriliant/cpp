#include <iostream>
#include <string>
#include <compare>

// includes... du brauchst mindestens: <string>, <iostream>, <compare>

struct Raumfahrer {
    std::string name_;
    unsigned int rang_; 
    unsigned int alter_;


// KOSNTRUKTOR
// Erste Variante initialisiert erst mit Standardwerten und überschreibt dann - NotEfficient
//Raumfahrer(std::string n, unsigned int r, unsigned int a) { name_= n; rang_ = r; alter_ = a; }

// (BEST PRATICE): Zweite Variante Initialisiert direkt und ist bei const felder sowieso erforderlich
Raumfahrer(std::string n, unsigned int r, unsigned int a) : name_(n), rang_(r), alter_(a) {};
    
// Standard Konstruktor nice to know
//auto operator<=>(const Raumfahrer& other) const = default;


// Alternativ => Reihenfolge explizit definieren:
// Spaceship-Operator: sortiere zuerst nach rang, dann alter
    auto operator<=>(const Raumfahrer& other) const {
        if (auto cmp = rang_ <=> other.rang_; cmp != 0) {
            return cmp; // Vergleiche zuerst nach rang_
        }
        return  alter_ <=> other.alter_;  // Falls rang_ gleich ist, vergleiche nach alter_
    }
};

// Freie Funktion zum überladen des operator<<
std::ostream& operator<<(std::ostream& os, const Raumfahrer& r){
    os << r.name_;
    return os;
}

// Funktion, die zwei Raumfahrer vergleicht und anzeigt, wer "höher im Kommando" steht
int is_higher_in_order(Raumfahrer r1, Raumfahrer r2) {
    if(r1.rang_ > r2.rang_) { return 1; }
    else if (r1.rang_ == r2.rang_) { return 0; }
    else { return -1; }
}

int main() {
    // Erstelle 2 Raumfahrer
    Raumfahrer rMember1{"Anikin", 3, 20};
    Raumfahrer rMember2{"Obiwan", 5, 52}; 

    // Vergleiche sie
    if (rMember1 > rMember2) {
        std::cout << rMember1 << " is higher in Rang and/or Age" 
                    << " than " << rMember2 << "\n" << std::endl;

    } else if(rMember1 < rMember2) {
        std::cout << rMember2 << " is higher in Rang and/or Age" 
                    << " than " << rMember1 << "\n" << std::endl;

    } else { 
        std::cout << rMember1 << " and " << rMember2 << " are the same Rank and/or Age\n" << std::endl;
    }

}
