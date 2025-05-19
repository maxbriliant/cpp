#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Wort {
    string wort;
    string kategorie;
};

void show_menu(){
    cout << "\nWillkommen im Wortgarten!\n";
    cout << "1. Wort hinzufügen\n";
    cout << "2. Garten anzeigen\n";
    cout << "3. Beenden\n";
    cout << "Bitte wählen Sie eine Option:";
}

void word_add(vector<Wort>& garten){
    string wort, kategorie;
    cout << "Bitte gib ein Wort ein: ";
    cin >> wort;
    cout << "Bitte gib dazu die passende Kategorie ein: ";
    cin >> kategorie;

    garten.push_back({wort, kategorie});
    cout << "Das Wort \"" << wort << "\" wurde hinzugefügt!\n";
}

void show_garden(const vector<Wort>& garten){
    cout << "\nDein Wortgarten:\n";

    for (const Wort& w : garten){
        cout << w.kategorie << ": " << w.wort << "\n";
    }
}
int main(){
    vector<Wort> garten;
    int auswahl;
    do {
        show_menu();
        cin >> auswahl;
        if (auswahl == 1) {
            word_add(garten);
        } else if (auswahl == 2) {
            show_garden(garten);
        } else if (auswahl != 3) {
            cout << "Ungültige Auswahl, versuchen sie es Erneut. \n";
        }
    }
    while( auswahl != 3);

    cout << "Danke für deinen Besuch im WortGarten!\n";
    return 0;
}