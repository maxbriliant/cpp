#include <iostream>
#include <map>
#include <string>

using std::string, std::ostream, std::map;

// Forward Declaration von Room & Connection
class Room;
struct Connection;

struct Connection {
    Room* r1_;
    Room* r2_;
  
    string c_r1_to_r2;
    string c_r2_to_r1;


    // Standardkonstruktor
    Connection() : r1_(nullptr), r2_(nullptr), c_r1_to_r2(""), c_r2_to_r1("") {}


    // Konstruktor: Initialisiert beide Kompassrichtungen
    Connection(Room* room1, Room* room2, string compass_r1_to_r2)
        : r1_(room1), r2_(room2), c_r1_to_r2(compass_r1_to_r2) {
        // Gegenpol direkt im Konstruktor setzen
        c_r2_to_r1 = (c_r1_to_r2 == "N") ? "S" :
                     (c_r1_to_r2 == "S") ? "N" :
                     (c_r1_to_r2 == "W") ? "E" :
                     (c_r1_to_r2 == "E") ? "W" : "";
    }
};

class Room {  
  private:
    string name_;
    string descr_;
    map<string, Connection> connections_; // Maximal eine Verbindung pro Himmelsrichtung

  public:
    Room(string name, string descr) : name_(name), descr_(descr) {}

    void set_name(string name) {
        name_ = name;
    }

    void set_descr(string descr) {
        descr_ = descr;
    }

    // Verbindung hinzufügen
    bool add_connection(const Connection& connection) {
        if (connections_.count(connection.c_r1_to_r2)) {
            std::cerr << "Error: Connection for direction " << connection.c_r1_to_r2 << " already exists.\n";
            return false;
        }
        connections_[connection.c_r1_to_r2] = connection;
        return true;
    }

    // Verbindung für eine bestimmte Himmelsrichtung abrufen
    Connection* get_connection(const string& direction) {
        if (connections_.count(direction)) {
            return &connections_[direction];
        }
        return nullptr;
    }

    // Alle Verbindungen abrufen
    map<string, Connection> get_all_connections() const {
        return connections_;
    }

    // Alle Verbindungen ausgeben
    void print_connections() const {
        for (const auto& [direction, connection] : connections_) {
            std::cout << "Direction: " << direction << ", Connection: " << connection.c_r1_to_r2 << " -> " << connection.c_r2_to_r1 << "\n";
        }
    }
};

ostream& operator<<(ostream& os, const Connection& c) {
    os << "Room 1: " << c.r1_ 
       << ", Room 2: " << c.r2_ 
       << ", Compass R1->R2: " << c.c_r1_to_r2 
       << ", Compass R2->R1: " << c.c_r2_to_r1;
    return os;
}

int main() {
    // Räume ohne Verbindungen erstellen
    Room kueche{"Küche", "Hier wird gekocht"};
    Room flur{"Flur", "Ein schmaler Flur"};
    Room wohnzimmer{"Wohnzimmer", "Hier wird entspannt"};

    // Verbindungen erstellen
    Connection c_kueche_flur{&kueche, &flur, "N"};
    Connection c_flur_wohnzimmer{&flur, &wohnzimmer, "E"};
    Connection c_wohnzimmer_kueche{&wohnzimmer, &kueche, "S"};

    // Verbindungen hinzufügen
    kueche.add_connection(c_kueche_flur);
    flur.add_connection(c_flur_wohnzimmer);
    wohnzimmer.add_connection(c_wohnzimmer_kueche);

    // Verbindungen ausgeben
    std::cout << "Küche Verbindungen:\n";

    kueche.print_connections();

    std::cout << "Flur Verbindungen:\n";
    flur.print_connections();

    std::cout << "Wohnzimmer Verbindungen:\n";
    wohnzimmer.print_connections();

    return 0;
}




