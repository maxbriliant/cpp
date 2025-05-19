#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>    // für std::ranges::contains in C++2
#include <unordered_set>


std::vector<int> get_unique_elements(const std::vector<int>& in);



int main(void) {
  const std::vector<int> numVec{1,2,4,7,4,1,2,7,5,2};
  std::vector<int> unique_nums = get_unique_elements(numVec);
  
  
  // Teste es Vorsichtig
  for (int e : unique_nums) {
    std::cout << e << " ";
  }
  std::cout << std::endl;

  return 0;
}

std::vector<int> get_unique_elements(const std::vector<int>& input){
  std::unordered_set<int> tempSet;
  std::vector<int> erfolgsVektor;
  for (auto num : input){
     // Hinzufügen zum Set gibt 
     // Iterator und einen Bool über den erfolg zurück -> .second für das if
     // Emplace erzeugt keine Kopie (Efficency)
    if (tempSet.emplace(num).second) {
      erfolgsVektor.push_back(num);
    }
  }
  return erfolgsVektor;
}

