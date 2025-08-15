// https://leetcode.com/problems/power-of-four/

bool isPowerOfFour(int n) {
    if(1 == n)
        return true;

    if(n < 4 || n % 2 != 0)
        return false;

    if(1 != __builtin_popcount(n))
        return false;

    if(__builtin_ctz(n) % 2 == 0)
        return true;
    else
        return false;
}
