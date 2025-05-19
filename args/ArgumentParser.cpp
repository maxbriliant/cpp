#include <iostream>
#include <string>
#include <vector> 

using std::string, std::cout, std::endl, std::cerr, std::vector;


class ArgumentParser {
private:
    vector<string> arguments_{};

public:
	ArgumentParser(int argc, char** argv) {
		for (int i = 1; i<argc; i++) {
			arguments_.push_back(argv[i]);
		}
	}

	bool has_option(const string& option_name) const {
			for (auto args : arguments_) {
				if (args == option_name) {
					return true;
				}
			}
			return false;
	}
	string get_option_value(const string& option_name) const {
		for (size_t i = 0; i < arguments_.size(); ++i) { // size_t ist der korrekte Typ fuer Indizes/Groessen
			if (arguments_[i] == option_name) {
				size_t value_index = i + 1;
					if (value_index < arguments_.size()) {
						return arguments_.at(value_index);
					} else {
						return "";
					}
				}
			}
			return "";
	}
};