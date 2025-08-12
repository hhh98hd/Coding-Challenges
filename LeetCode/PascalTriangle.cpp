// https://leetcode.com/problems/pascals-triangle/

#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> generate(int numRows)
{
    vector<vector<int>> res;
    vector<int> prevRow;

    for (int i = 1; i <= numRows; i++)
    {

        if (1 == i)
        {
            vector<int> row;
            row.push_back(1);
            res.push_back(row);
            continue;
        }

        if (2 == i)
        {
            vector<int> row;
            row.push_back(1);
            row.push_back(1);
            res.push_back(row);
            continue;
        }

        if (3 == i)
        {
            vector<int> row;
            row.push_back(1);
            row.push_back(2);
            row.push_back(1);
            res.push_back(row);
            continue;
        }

        if (4 == i)
        {
            vector<int> row;
            row.push_back(1);
            row.push_back(3);
            row.push_back(3);
            row.push_back(1);
            res.push_back(row);
            prevRow = row;
            continue;
        }

        vector<int> row(i);
        row[0] = 1;
        row[i - 1] = 1;

        for (int j = 1; j < i - 1; j++)
        {
            row[j] = prevRow[j - 1] + prevRow[j];
        }

        prevRow = row;
        res.push_back(row);
    }

    return res;
}