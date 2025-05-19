#include <iostream>
#include <string>
#include <vector>


using std::string, std::cout, std::endl, std::cerr;

string args = "";
int argumentParse(int arg_count, char** arg_vector, string& arg_string);
bool is_v_flagged();
bool is_o_flagged();


int main(int argc, char* argv []) {
try{
argumentParse(argc, argv, args);
} catch(std::exception &e) {
cerr << "Parsing failed: " << e.what() << endl;
}

if (is_v_flagged()) {
cout << "Verbose Activated" << endl;
}


if (is_o_flagged()) {
cout << "Prepare to use output-filename of the user" << endl;
}

return 0;
}















int argumentParse(int arg_count, char** arg_vector, string& arg_string){
    if(arg_count == 1) {
        cerr << "Keine Argumente Übergeben" << endl;
        return 1;
    }

    for (int i = 1; i < arg_count ;i++) {
        arg_string += (static_cast<std::string>(arg_vector[i]) + " ");
    }
return 0;
}
    
    
    
    //Only Use after Parsing
    
    bool is_v_flagged() {
    return args.contains("-v") || args.contains("--verbose");
    }
    bool is_o_flagged() {
    if(args.contains("-o")){
        return true;
    } else return false;
    }