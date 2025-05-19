#include <vector>
#include <iostream>
#include <algorithm>

using std::vector;

std::vector<int> get_unique_elements(vector<int>& nums);

int main(void) {
  vector<int> nums{1, 2, 2, 3, 4, 4, 5, 2, 4};
  auto uniq_nums = get_unique_elements(nums);
  for (auto e : uniq_nums) {
    std::cout << e << " ";
  }
  return 0;
}


std::vector<int> get_unique_elements(std::vector<int>& nums) {
  auto uniq_num_begin = std::unique(nums.begin(), nums.end());
  nums.erase(uniq_num_begin, nums.end());
  return nums;
}
