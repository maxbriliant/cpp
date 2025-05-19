#include <array>
#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using std::cin; 
using std::cout; 
using std::string;
using std::getline;
using std::fstream;
using std::ifstream;

void eingabe(
    std::string &name,
    unsigned &gebTag,
    unsigned &gebMonat,
    unsigned &gebJahr,
    long long &steuernummer,
    std::array<int,12> &moantseinkommen)
{
    std::ifstream input{"input.txt"};

    cout << "Name: ";
    std::getline(input, name);
    cout << name << "\n";
    if(name.length() == 0) {
        cout << "Sie haben einen leeren Namen eingegeben.\n";
        exit(1);
    }
    
    string buffer;
    cout << "Geb.-Tag: "; 
    getline(input, buffer);
    gebTag = stoi(buffer);
    cout << gebTag << "\n";
    
    cout << "Geb.-Monat ";
    getline(input, buffer);
    gebMonat = stoi(buffer);
    cout << gebMonat << "\n";

    cout << "Geb.-Jahr "; 
    getline(input, buffer);
    gebJahr = stoi(buffer);
    cout << gebJahr << "\n";

    cout << "Steuernummer: "; 
    getline(input, buffer);
    steuernummer = stoi(buffer);
    cout << steuernummer << "\n";

    for(int m=0; m<12; ++m){
        cout << "Einkommen Monat " << m+1 << ": ";
        getline(input, buffer);
        moantseinkommen[m] = stoi(buffer);
        cout << moantseinkommen[m] << "\n"; 
    }
cout << std::endl;
}
int main(int argc, char* argv[]){
    
    std::string name{};
    unsigned tag = 0;
    unsigned monat = 0;
    unsigned jahr = 0;
    long long stNr = 0;
    std::array<int,12> einkommen {};
    eingabe(name, tag, monat, jahr, stNr, einkommen);
}


