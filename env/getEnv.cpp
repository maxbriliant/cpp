#include <iostream>
#include <cstdlib>
#include <optional>
#include <string>
#include <memory>

std::optional<std::string> get_environment_variable(const std::string& lookup);

int main() {
    std::unique_ptr<std::string> output; // Pointer for the output
    std::optional<std::string> opt = get_environment_variable("PATH");

    if (opt) {
        output = std::make_unique<std::string>(*opt); // Capture the value in the pointer
        std::cout << "Your ENV Variable:\n\n" << *output << "\n" << std::endl;
    } else {
        output = std::make_unique<std::string>("No Data Passed");
        std::cout << *output << std::endl; // Use the pointer in the else block
    }

    return 0;
}

std::optional<std::string> get_environment_variable(const std::string& lookup) {
    const char* value = getenv(lookup.c_str());
      return std::string(value); // Convert C-string to std::string and return
    } 

