// https://leetcode.com/problems/range-product-queries-of-powers/

#include <bits/stdc++.h>

using namespace std;

vector<int> productQueries(int n, vector<vector<int>>& queries) {
    vector<int> res;
    vector<unsigned long> powers;

    bitset<32> bits(n);
    for(int i = 0; i < 32; i++) {
        if(1 == bits[i]) {
            powers.push_back( (unsigned long)(pow(2, i)) );
        }
    }

    for(auto query : queries) {
        int beginIdx = query[0];
        int endIdx = query[1];
        unsigned long long prod = 1;

        if(beginIdx == endIdx) {
            prod = powers[beginIdx];
        } else {
            for(int i = beginIdx; i <= endIdx; i++) {
                prod = (prod * powers[i]) % 1000000007;
            }
        }

        res.push_back(prod);
    }
    
    return res;
}