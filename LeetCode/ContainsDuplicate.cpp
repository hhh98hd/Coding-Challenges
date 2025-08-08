#include <vector>
#include <unordered_set>

bool containsDuplicate(std::vector<int>& nums) {
    int n = nums.size();

    if(1 == n || 0 == n) {
        return false;
    }

    if(2 == n) {
        return nums[0] == nums[1];
    }

    std::unordered_set<int> s(nums.begin(), nums.end());
    return s.size() != n;
}