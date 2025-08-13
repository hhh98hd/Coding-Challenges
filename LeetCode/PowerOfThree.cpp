// https://leetcode.com/problems/power-of-three/

#include <bits/stdc++.h>

using namespace std;

bool isPowerOfThree(int n)
{
    if (1 == n || 3 == n || 9 == n || 27 == n || 81 == n)
        return true;

    if (n <= 0 || n % 2 == 0 || n % 3 != 0)
        return false;

    while (n > 1)
    {
        if (n % 3 != 0)
            return false;

        n = n / 3;
    }

    return true;
}
