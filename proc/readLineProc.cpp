#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <chrono>
#include <thread>
#include <iomanip> // Für std::fixed und std::setprecision

using namespace std;

/*Simple Is-Numeric function in C++*/
bool is_digit(const char value) { return std::isdigit(value); }
bool is_numeric(const string& value) { return all_of(value.begin(), value.end(), is_digit); }


// method declarations
std::vector<long long> parse_cpu_stat();
double calculate_cpu_usage();


int main(void) {
	double cpu_percent_usage = calculate_cpu_usage();
	cout << "CPU Auslastung während der Messung: " << fixed << setprecision(2) << cpu_percent_usage << "%" << "\n" << endl;
	return 0;
}


double calculate_cpu_usage() {

	long long idle_1;
	long long idle_2;

	auto cpu_stats_1 = parse_cpu_stat();
	this_thread::sleep_for(std::chrono::milliseconds(3000));
	auto cpu_stats_2 = parse_cpu_stat();

	long long total_1 = accumulate(cpu_stats_1.begin(), cpu_stats_1.end(), 0LL);
	long long total_2 = accumulate(cpu_stats_2.begin(), cpu_stats_2.end(), 0LL);

	if (cpu_stats_1.size() >= 4 && cpu_stats_2.size() >= 4) {
		idle_1 = cpu_stats_1.at(3);
		idle_2 = cpu_stats_2.at(3);
	} else {
		cerr << "CPU Stats Listen kleiner als 4!" << endl;
		return -1.0; // Fehlerwert
	}

	long long total_delta = total_2 - total_1;
	long long idle_delta = idle_2 - idle_1;

	
	double cpu_usage = 0.0;
	
	if (total_delta > 0) {
		cpu_usage = 100.0 * static_cast<double>(total_delta - idle_delta) / total_delta;
	}
	return cpu_usage;
}


std::vector<long long> parse_cpu_stat(){
	// variables
	string file_name = "/proc/stat";
	string to_find = "cpu ";
	ifstream input(file_name);
	vector <long long> numbers;

	for (string line; getline(input, line); ){
		istringstream iss(line);
		string word;

		if (line.find(to_find) == 0) {

			while (iss >> word){

				if (is_numeric(word)) {
					numbers.push_back(stoll(word));

					if (numbers.size() >= 10) {
						return numbers;
					}

				}
			}
			break; // Wichtige Optimierung: Nur die erste "cpu " Zeile verarbeiten
		} 
	}
	return numbers;
}
