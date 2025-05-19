#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include <regex>

using namespace std;

int main (){

    map <string, string> cpuinfo_map;
    ifstream fs;
    string line;
    string splitted;

    fs.open("/proc/cpuinfo");
    
    if(fs.is_open()) {
        while (getline(fs,line)) {
            //std::string line = std::string(line);
            if(line.contains("cpu MHz") || line.contains("model name")){
                // to split we need sstream
                stringstream line_splitter{line};
                // Get till ':' in the actual line
                getline(line_splitter, splitted, ':');
                string splitted_before = splitted;
                // Get after ':' in the actual line
                getline(line_splitter, splitted, ':');
                string splitted_after = splitted;
                // Whitespace Cleanup
                splitted_after = std::regex_replace(splitted_after, std::regex("^ +| +$| {2,}"), "$1");
                splitted_before = std::regex_replace(splitted_before, std::regex("^ +| +$| {2,}"), "$1");;
                // insert into map
                cpuinfo_map[splitted_before] = splitted_after;
            }
        }
        for (auto map_element : cpuinfo_map){
            cout << map_element.first << " : " << map_element.second << endl;
        }
    }
    return 0;
} 