#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>    // für std::ranges::contains in C++23

void remove_duplicates(const std::vector<int>& in, std::vector<int>& out);

const std::vector<int> numVec{1,2,4,7,4,1,2,7,5,2};
std::vector<int> to_fill{};

int main(void) {
  // Beispielcode zum Testen
  remove_duplicates(numVec, to_fill);
  for (auto i : to_fill){
    std::cout << i << " ";
  }
  std::cout << std::endl;
    return 0;
}

void remove_duplicates(const std::vector<int>& input, std::vector<int>& output){
  for (auto num : input){
    if (!output.empty()) {
      // C++23 Lösung mit std::ranges::contains
      if(!std::ranges::contains(output, num)) {
        output.push_back(num);
      }
    } else {
     // Wenn der Vektor leer ist, fügen wir das Element direkt hinzu
      output.push_back(num);
    }
  }
}

