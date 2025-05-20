#include <iostream>
#include <memory>
#include <string>


struct Raumstation{ 
    //inline static unsigned int starship_count = 0;
    std::string name_;

    Raumstation(std::string n) : name_{n} {/*++Raumstation::starship_count;*/ std::cout << "Raumstation wurde gebaut." << std::endl;}
    ~Raumstation(){/*--Raumstation::starship_count;*/ std::cout << "Raumstation wurde zerstört." << std::endl;}
};

int print_ships(std::shared_ptr<Raumstation>& r_ptr);

int main() {
    std::shared_ptr<Raumstation> station1 = std::make_shared<Raumstation>("Aurora");
    std::shared_ptr<Raumstation> station1_ref = station1;
    std::shared_ptr<Raumstation> station2_ref = station1;
    std::shared_ptr<Raumstation> station3_ref = station1;
    
    print_ships(station1);

    return 0;
}









int print_ships(std::shared_ptr<Raumstation>& r_ptr) {

    std::string wort2_singular_string = " Referenz auf die Station";
    std::string wort2_plural_string = " Referenzen auf die Station";

    std::string wort1_singular_string = "ist"; 
    std::string wort1_plural_string = "sind";
    
    std::string wort1_used{};
    std::string wort2_used{};

    long int starship_count = r_ptr.use_count();

    if (starship_count == 1){
        wort1_used = wort1_singular_string;
        wort2_used = wort2_singular_string;
    }
    else if ((starship_count > 1 || starship_count == 0)) {
        wort1_used = wort1_plural_string;
        wort2_used = wort2_plural_string;
    }
    else { 
        std::cout << "Es " << wort1_used << " gerade " << "keine" << wort2_used <<" im Umlauf!\n" << std::endl;
        return 0;
    }
    //Print Zeile
    std::cout << "Es " << wort1_used << " gerade " << starship_count << wort2_used <<" im Umlauf!\n" << std::endl;
    return 0;
}