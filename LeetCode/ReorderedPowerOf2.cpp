// https://leetcode.com/problems/reordered-power-of-2

#include <bitset>
#include <string>
#include <unordered_map>
#include <math.h>
#include <algorithm>

bool isPowerOf2(int n) {
    std::bitset<32> bits(n);
    return 1 == bits.count();
}

bool reorderedPowerOf2(int n) {
    // Already a power of 2
    if(1 == n || isPowerOf2(n))
        return true;

    std::unordered_map<std::string, bool> powerOf2Map;
    for(int i = 0; i <= 30; i++) {
        std::string powerStr = std::to_string(int(pow(2, i)));
        sort(powerStr.begin(), powerStr.end());
        powerOf2Map[powerStr] = true;
    }

    std::string numStr = std::to_string(n);
    std::sort(numStr.begin(), numStr.end());

    return powerOf2Map.end() != powerOf2Map.find(numStr);
}
