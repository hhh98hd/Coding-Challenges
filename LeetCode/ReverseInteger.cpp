// https://leetcode.com/problems/reverse-integer/

#include <bits/stdc++.h>

using namespace std;

int ctoi(char c) {
    switch(c) {
        case '0': return 0;
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;
    }

    return -1;
}

int reverse(int x) {
    if(0 == x)
        return 0;

    long res = 0;
    string numStr = to_string(x);

    bool isNeg = numStr[0] == '-';

    for(int i = numStr.length() - 1; i >= 0; i--) {
        if(numStr[i] == '-') {
            continue;
        }

        res += !isNeg ? pow(10, i) * ctoi(numStr[i]) : pow(10, i - 1) * ctoi(numStr[i]);
    }

    if(isNeg) res = -res;

    if(res < 0 && res < INT_MIN)
        return 0;

    if(res > 0 && res > INT_MAX)
        return 0;
        
    return res;
}
