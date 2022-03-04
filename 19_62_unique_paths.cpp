// old
class Solution {
public:
    int uniquePaths(int m, int n) {
        // // (m+n-2)! / (m-1)! / (n-1)!
        // if (n > m)
        // {
        //     swap(n, m);
        // }
        // long int ans = 1;
        // for (int i = m + n - 2; i > m - 1; i--)
        // {
        //     ans *= i;
        // }
        // for (int i = 1; i <= n-1; i++)
        // {
        //     ans /= i;
        // }
        // return ans;
        vector<vector<int>> ans(m, vector<int>(n, 1));
        return dp(ans, m-1, n-1);
    }
    int dp(vector<vector<int>>& ans, int m, int n)
    {
        if (m == 1 || n == 1) {
            ans[m][n] = 1;
            return 1;
        }
        if (ans[m-1][n] == 0)
            ans[m-1][n] = dp(ans, m-1, n);
        if (ans[m][n-1] == 0)
            ans[m][n-1] = dp(ans, m, n-1);
        if (ans[m][n] == 0)
            ans[m][n] = ans[m-1][n] + ans[m][n-1];
        return ans[m][n];
    }
};

// 1 time
class Solution {
public:
    int uniquePaths(int m, int n) {
        // if m,n == 2,2
        // 1 to go 1,2
        // 1 to go 2,1
        // so total 2
        //
        // if m,n == 3,2
        // 3 different time to go down
        // so 3.
        //
        // if m,n == 3,3
        // 3 + 2 + 1
        //
        // so it is like
        //  & <- (m,n)
        //       10 4 1
        //        6 3 1
        //      4 3 2 1
        //      1 1 1 *
        if (m == 1 || n == 1)
            return 1;
        vector<vector<int>> map(m, vector<int>(n, 1));
        for (int i = 1; i < m; i++)
        {
            for (int j = 1; j < n; j++)
            {
                map[i][j] = map[i][j-1] + map[i-1][j];
            }
        }
        return map[m-1][n-1];
    }
};
