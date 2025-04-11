#include <iostream>

int charToInt(char c) {
    switch (c)
    {
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

bool isSymmetric(int num) {
    std::string numStr = std::to_string(num);
    int strLen = numStr.length();

    if(strLen % 2 != 0)
        return false;

    std::string firstHalf = numStr.substr(0, strLen / 2);
    std::string secondHalf = numStr.substr(strLen / 2, std::string::npos);

    int sum1 = 0, sum2 = 0;

    for(char c : firstHalf) 
        sum1 += charToInt(c);
    for(char c : secondHalf)
        sum2 += charToInt(c);
    
    return (sum1 == sum2);
}

int countSymmetricIntegers(int low, int high) {
    int ret = 0;

    for(int i = low; i <= high; i++)
        ret += isSymmetric(i) ? 1 : 0;

    return ret;
}

int main() {
    std::cout << isSymmetric(1230);
}