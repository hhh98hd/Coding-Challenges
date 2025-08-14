// https://leetcode.com/problems/largest-3-same-digit-number-in-string/

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

char itoc(int n) {
    switch(n) {
        case 0: return '0';
        case 1: return '1';
        case 2: return '2';
        case 3: return '3';
        case 4: return '4';
        case 5: return '5';
        case 6: return '6';
        case 7: return '7';
        case 8: return '8';
        case 9: return '9';
    }

    return 'x';
}

string largestGoodInteger(string num) {
    int largestGoodInt = -1;

    for(int i = 0; i < num.length() - 1; i++) {
        char firstDigit = num[i];
        char secondDigit = num[i + 1];
        char thirdDigit = num[i + 2];

        if(firstDigit == secondDigit && secondDigit == thirdDigit) {
            int digit = ctoi(firstDigit);
            if(digit > largestGoodInt)
                largestGoodInt = digit;
        }
    }

    if(-1 == largestGoodInt)
        return "";
    else {
        string res;

        char digit = itoc(largestGoodInt);
        res += digit;
        res += digit;
        res += digit;

        return res;
    }
}
