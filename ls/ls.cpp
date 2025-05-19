#include <cstring>
#include <iostream>
#include <dirent.h>
#include <string>
#include <error.h>

using namespace std;

int main() {
    DIR *pd;
    struct dirent *pde;

    string dirname;
    cout << "Gib einen Pfad ein: ";
    getline(cin, dirname);

    pd = opendir(dirname.c_str());

    if (pd == NULL) {
        cerr << "Fehler beim Öffnen: " << strerror(errno) << endl;
        return 1;
    }

    // Durchlauf 1: Gib die ersten beiden Einträge aus
    for (int i = 0; i < 2; i++) {
        pde = readdir(pd);
        if (pde != NULL) {
            cout << pde->d_name << endl;
        }
    }

    // Speicher die aktuelle Position
    long int saved = telldir(pd);

    // Durchlauf 2: Gib noch ein Element aus, bevor du zurückspringst - 
    // Sonst siehst du den Effekt von saved = telldir() nicht.
    pde = readdir(pd); 
    if (pde != NULL) {
        cout << pde->d_name << endl;
    }

    // Gehe zurück zur gespeicherten Position
    seekdir(pd, saved);
    cout << endl;

    // Durchlauf 3: Gib das restliche Verzeichnis aus
    while ((pde = readdir(pd)) != NULL) {
        cout << pde->d_name << endl;
    }

    closedir(pd);
    return 0;
}
