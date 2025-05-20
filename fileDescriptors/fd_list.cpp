#include <iostream>
#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

void fd_list();

int main() {
    // TODO: /proc/self/fd öffnen und Einträge zählen
    // TODO: readlink() auf die Einträge für Zielpfade
    fd_list();
    return 0;
}

void fd_list() {
    const char* fd_path = "/proc/self/fd";
    DIR* fd_dir = opendir(fd_path);
    if (fd_dir != nullptr) {
        struct dirent* entry;
        char buffer[PATH_MAX];
        while ((entry = readdir(fd_dir)) != nullptr) {
            // Ignoriere "." und ".."
            if (std::string(entry->d_name) == "." || std::string(entry->d_name) == "..") {
                continue;
            }

            // Erstelle den vollständigen Pfad zum Dateideskriptor
            std::string full_path = std::string(fd_path) + "/" + entry->d_name;

            // Lese den Zielpfad des Dateideskriptors
            ssize_t len = readlink(full_path.c_str(), buffer, sizeof(buffer) - 1);
            if (len != -1) {
                buffer[len] = '\0';
                std::cout << "FD\t" << entry->d_name << " → " << buffer << "\n";
            } else {
                std::cerr << "Fehler beim Lesen des Links für FD " << entry->d_name << "\n";
            }
        }
        closedir(fd_dir);
    } else {
        std::cerr << "Verzeichnis konnte nicht geöffnet werden!" << std::endl;
    }
}


