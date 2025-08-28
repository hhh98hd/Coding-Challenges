// https://leetcode.com/problems/first-unique-character-in-a-string/

#include <bits/stdc++.h>

using namespace std;

int firstUniqChar(string s) {
    unordered_map<char, int> freqMap;

    for(const char& c : s) {
        freqMap[c] += 1;
    }

    for(int i = 0; i < s.length(); i++) {
        if(1 == freqMap[s[i]])
            return i;
    }

    return -1;
}
