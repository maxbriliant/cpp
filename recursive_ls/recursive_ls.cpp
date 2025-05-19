#include <cstring>
#include <iostream>
#include <string>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

using namespace std;

int counter = 0;

void recursive_open(DIR *continous_dir, const string& base_path);

int main() {
    DIR *start = opendir("/home/mx/");
    if (start == NULL) {
        cerr << "Fehler beim Öffnen des Verzeichnisses! Fehler: " << strerror(errno) << endl;
        return 1;
    }
    recursive_open(start, "/home/mx/");
    
    cout << "Dateianzahl in allen Unterverzeichnissen: " << counter << endl;
    closedir(start);

    return 0;
}

void recursive_open(DIR *continous_dir, const string& base_path) {
    struct dirent *entry;

    while( (entry = readdir(continous_dir)) != NULL ) {
        // Überspringe . und ..
        if ( (strcmp(entry->d_name, ".") == 0) || (strcmp(entry->d_name, "..") == 0)) {
            continue;
        }
        
        string full_path = base_path + "/" + entry->d_name;  // Vollständigen Pfad erstellen
        if (base_path.back() == '/') {
            full_path = base_path + entry->d_name; // Kein zusätzlicher Schrägstrich
        }
        //cerr << "Verarbeite: " << full_path << endl;        // Ausgabe zur Fehlersuche
        
        // Prüfe, ob es ein Unterverzeichnis ist
        if (entry->d_type == DT_DIR) {
            // Öffne Unterverzeichnis und gehe rekursiv weiter
            DIR *sub_dir = opendir(full_path.c_str());
            if (sub_dir != NULL) {
                recursive_open(sub_dir, full_path);  // Rekursiver Aufruf
                closedir(sub_dir);
            } else {
                cerr << "Kann Verzeichnis nicht öffnen: " << full_path << " Fehler: " << strerror(errno) << endl;
            }
        } else if (entry->d_type == DT_REG) {
            ++counter;  // Zähle reguläre Dateien
        }
    }
}
