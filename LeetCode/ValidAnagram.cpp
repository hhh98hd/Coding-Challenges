// https://leetcode.com/problems/valid-anagram/

#include <string>

bool isAnagram(std::string s, std::string t) {
    int n1 = s.length();
    int n2 = t.length();

    if(n1 != n2)
        return false;

    int freq1[26], freq2[26];

    for(int i = 0; i < n1; i++) {
        freq1[int(s[i]) - 97] += 1;
        freq2[int(t[i]) - 97] += 1;
    }

    for(int i = 0; i < 26; i++) {
        if(0 != freq1[i] - freq2[i])
            return false;
    }

    return true;
}