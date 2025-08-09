// https://leetcode.com/problems/group-anagrams/

#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {
    std::unordered_map<std::string, std::vector<std::string>> mp;
    std::vector<std::vector<std::string>> res;

    for(std::string str : strs) {
        std::string originalStr = str;
        sort(str.begin(), str.end());
        
        if(mp.end() == mp.find(str)) {
            mp[str] = std::vector<std::string> { originalStr };
        } else {
            mp[str].push_back(originalStr);
        }
    }

    for(auto it = mp.begin(); it != mp.end(); it++) {
        res.push_back(it->second);
    }

    return res;
}