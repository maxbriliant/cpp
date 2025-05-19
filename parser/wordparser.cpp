#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

unsigned max_path = 0;

string filepath_input; 
char* full_path_cstr;
unsigned get_needed_cstr_size(char* []);
void check_input(int,  char* []);





int main (int argc,  char* argv[]) {
	
	check_input(argc, argv); 							// Checks input and Initializes c_array length
	realpath(filepath_input.c_str(), full_path_cstr); 	//sets full_path_cstr
	string full_path = full_path_cstr;

	return 0; 
}






























// Input Pfad wird Verarbeitet falls Übergeben
void check_input(int argc, char* argv[]){
	//Prüfung auf zweites argument
	if (argc >=2){
		string(filepath_input) = argv[1];
		max_path = get_needed_cstr_size(argv);
		full_path_cstr[max_path];

	} else { 
		cout << "Es wurde keine datei übergeben!\nVerwende: ./wordpraser file\n" << endl;
	}
}



unsigned get_needed_cstr_size(char* argv[]){
		unsigned new_max_path = string(argv[1]).size(); 
		return new_max_path;
	}