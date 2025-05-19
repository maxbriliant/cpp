#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <regex>
#include <cctype>
#include <iomanip>
#include <locale> // Für std::tolower mit locale

using std::map, std::string, std::cout, std::cin, std::endl, std::transform, std::setw, std::left;

// Hilfsfunktion, um Präfixe zu überprüfen
bool startsWithIgnoreCase(const string &input, const string &prefix) {
    if (input.size() < prefix.size()) return false;
    for (size_t i = 0; i < prefix.size(); ++i) {
        if (std::tolower(input[i]) != std::tolower(prefix[i])) {
            return false;
        }
    }
    return true;
}

// Hilfsfunktion, um Namen unabhängig von Groß-/Kleinschreibung zu finden
string findNameIgnoreCase(const map<string, string> &entries, const string &name) {
    for (const auto &entry : entries) {
        if (std::equal(name.begin(), name.end(), entry.first.begin(), entry.first.end(),
                      [](char a, char b) { return std::tolower(a) == std::tolower(b); })) {
            return entry.first;
        }
    }
    return ""; // Gibt einen leeren String zurück, wenn kein Name gefunden wird
}

int main() {
    string name;
    string nummer;
    string input;
    map<string, string> entries;

    cout << "Verfügbare Befehle: neu/new, zeige/show, liste/list, ende/end." << endl;
    cout << "Bitte geben Sie einen Befehl ein:\t\n" << endl;

    while (true) {
        std::getline(cin, input); // Liest die gesamte Zeile ein

        // Konvertiere Eingabe in Kleinbuchstaben für case-insensitive Vergleich
        string lowerInput = input;
        std::transform(lowerInput.begin(), lowerInput.end(), lowerInput.begin(), [](unsigned char c) { return std::tolower(c); });

        if (startsWithIgnoreCase(input, "neu") || startsWithIgnoreCase(input, "new")) {
            std::regex pattern("(neu|new)\\s+(\\S+)\\s+(\\S+)");
            std::smatch match;

            if (std::regex_match(input, match, pattern)) {
                name = match[2];
                nummer = match[3];
                entries[name] = nummer;

                cout << "\nEintrag hinzugefügt:\t" << name << " -> " << nummer << "\n\n" << endl;
            } else {
                cout << "Ungültiges Format. Bitte geben Sie 'neu __Name __Nummer' ein." << endl;
            }
        } else if (startsWithIgnoreCase(input, "zeige") || startsWithIgnoreCase(input, "show")) {
            std::regex pattern("(zeige|show)\\s+(\\S+)");
            std::smatch match;

            if (std::regex_match(input, match, pattern)) {
                name = match[2];
                string foundName = findNameIgnoreCase(entries, name);

                if (!foundName.empty()) {
                    cout << "-----------------------------------" << endl;
                    cout << "Name:\t" << foundName << endl;
                    cout << "Nummer:\t" << entries[foundName] << endl;
                    cout << "-----------------------------------" << endl;
                } else {
                    cout << "Kein Eintrag für\t" << name << " gefunden." << endl;
                }
            } else {
                cout << "Ungültiges Format. Bitte geben Sie 'zeige __Name' ein." << endl;
            }
        } else if (startsWithIgnoreCase(input, "liste") || startsWithIgnoreCase(input, "list")) {
            if (entries.empty()) {
                cout << "Das Telefonbuch ist leer." << endl;
            } else {
                size_t maxNameLength = 0;
                for (const auto &entry : entries) {
                    maxNameLength = std::max(maxNameLength, entry.first.length());
                }

                cout << "-----------------------------------" << endl;
                for (const auto &entry : entries) {
                    cout << "Name:   " << std::left << std::setw(maxNameLength) << entry.first
                         << "   Nummer:   " << entry.second << endl;
                }
                cout << "-----------------------------------" << endl;
            }
        } else if (startsWithIgnoreCase(input, "ende") || startsWithIgnoreCase(input, "end")) {
            cout << "Programm beendet." << endl;
            break;
        } else {
            cout << "Unbekannter Befehl. Verfügbare Befehle: neu/new, zeige/show, liste/list, ende/end." << endl;
        }

        cout << "Verfügbare Befehle: neu/new, zeige/show, liste/list, ende/end." << endl;
        cout << "Bitte geben Sie einen Befehl ein:\t\n" << endl;
    }

    return 0;
}