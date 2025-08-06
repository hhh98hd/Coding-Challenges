// https://leetcode.com/problems/search-insert-position/description/

#include <iostream>
#include <vector>

int binarySearch(std::vector<int>& nums, int target, int leftIdx, int rightIdx) {
    if(nums[leftIdx] == target)
        return leftIdx;

    if(nums[rightIdx] == target)
        return rightIdx;

    if(leftIdx + 1 == rightIdx) {
        if(nums[leftIdx] == target)
            return leftIdx;

        if(nums[rightIdx] == target)
            return rightIdx;

        if(target < nums[leftIdx]) {
            return leftIdx;
        } else if(nums[leftIdx] < target && target < nums[rightIdx]) {
            return rightIdx;
        } else if(target > nums[rightIdx]) {    
            return rightIdx + 1;
        }
    }

    int midIdx = leftIdx + (rightIdx - leftIdx) / 2;
    int midVal = nums[midIdx];

    if(midVal < target)
        return binarySearch(nums, target, midIdx, rightIdx);
    else
        return binarySearch(nums, target, leftIdx, midIdx);
    }
    

int searchInsert(std::vector<int>& nums, int target) {
    int n = nums.size();
    if(1 == n) { 
        if(target <= nums[0])
            return 0;
        else if(target > nums[0])
            return 1;
    }
    return binarySearch(nums, target, 0, n - 1);
}

int main() {    
    std::vector<int> nums = { 1, 3, 5, 6 };
    int res = searchInsert(nums, 0);

    std::cout << res << std::endl;
}
