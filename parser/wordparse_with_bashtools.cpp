#include <iostream>
#include <fstream>
#include <string>
#include "bash_tools.hpp"
#include <sstream>
#include <vector>

using namespace std;

unsigned full_count;
string filepath_input; 

void check_input(int,  char* []);



int main (int argc,  char* argv[]) {
	
	check_input(argc, argv); 		
	string my_realpath = bash_tools::get_realpath(filepath_input);
	cout << "My Realpath is: " << my_realpath << endl;

	std::vector<string> wordlist;
	std::string word;

	fstream input_stream(my_realpath);
	if(!input_stream.is_open()) {
		cerr << "Fehler beim öffnen von " << my_realpath << endl;
	}
	while (input_stream >> word){
		wordlist.push_back(word);
		//cout << word << endl;
	}

	unsigned full_count = wordlist.size();

	
	return 0; 
}




// Input Pfad wird Verarbeitet falls Übergeben
void check_input(int argc, char* argv[]){
	//Prüfung auf zweites argument
	if (argc >=2){
		filepath_input = argv[1];
	} else { 
		cout << "Es wurde keine datei übergeben!\nVerwende: ./wordpraser file\n" << endl;
	}
}