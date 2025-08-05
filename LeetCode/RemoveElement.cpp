// https://leetcode.com/problems/remove-element/description/

#include <iostream>
#include <vector>
#include <algorithm>

int removeElement(std::vector<int>& nums, int val) {
    int n = nums.size();

    if(0 == n) { return 0;}

    if(1 == n) {
        if(nums[0] != val)
            return 1;
        else {
            // nums = std::vector<int>{};
            return 0;
        }
    }

    if(2 == n) {
        if(nums[0] == val && nums[0] == nums[1])
            return 0;
        
        if(nums[0] == val) {
            nums[0] = nums[1];
            return 1;
        }

        if(nums[1] == val)
            return 1;
    }

    int matchCnt = 0, beginIdx = 0, endIdx = n - 1, prevBeginValIdx = -1, prevEndValIdx;

    while(beginIdx < endIdx) {
        if(nums[beginIdx] == val) {
            if(prevBeginValIdx != beginIdx) {
                prevBeginValIdx = beginIdx;
                matchCnt += 1;
            }

            if(nums[endIdx] == val) {
                if(prevEndValIdx != endIdx) {
                    prevEndValIdx = endIdx;
                    matchCnt += 1;
                }
                endIdx--;
                continue;

            } else {
                nums[beginIdx] = nums[endIdx];
                nums[endIdx] = val;
                endIdx--;
            }
        }

        beginIdx++;
        if(nums[endIdx] == val && prevEndValIdx != endIdx) {
            prevEndValIdx = endIdx;
            matchCnt += 1;
        }
    }

    return n - matchCnt;
}

int main() 
{
    std::vector<int> nums = { 2, 3, 2, 2 };
    int n = removeElement(nums, 2);

    for(int i = 0; i < n; i++)
        std::cout << nums[i] << " ";
    std::cout << std::endl;
}