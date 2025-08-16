// https://leetcode.com/problems/maximum-69-number/

#include <bits/stdc++.h>

using namespace std;

int maximum69Number (int num) {
    string numStr = to_string(num);

    for(int i = 0; i < numStr.length(); i++) {
        if('6' == numStr[i]) {
            numStr[i] = '9';
            break;
        }
        else {
            continue;                
        }
    }

    return stoi(numStr);
}
