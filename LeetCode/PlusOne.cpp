// https://leetcode.com/problems/plus-one/

#include <bits/stdc++.h>

using namespace std;

vector<int> plusOne(vector<int> &digits)
{
    int n = digits.size();

    if (digits[n - 1] != 9)
    {
        vector<int> res(digits.begin(), digits.end());
        res[n - 1] += 1;
        return res;
    }

    vector<int> res(n);
    res[n - 1] = 0;
    int carry = 1;

    for (int i = n - 2; i >= 0; i--)
    {
        res[i] = (digits[i] + carry) % 10;
        if (10 == digits[i] + carry)
            carry = 1;
        else
            carry = 0;
    }

    if (1 == carry)
        res.insert(res.begin(), 1);

    return res;
}