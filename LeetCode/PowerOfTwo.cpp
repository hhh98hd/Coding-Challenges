// https://leetcode.com/problems/power-of-two/

#include <bitset>

bool isPowerOfTwo(int n) {
    if(n < 0)
        return false;

    std::bitset<32> bits(n);
    return 1 == bits.count();
}