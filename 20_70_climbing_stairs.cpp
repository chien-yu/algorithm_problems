class Solution {
public:
    int climbStairs(int n) {
        // thinking from the end?
        // last one is 2
        vector<int> dp(n, 0);

        if (n == 1)
            return 1;
        if (n == 2)
            return 2;

        // dp[-1] = 1; end point
        dp[0] = 1; // n = 1
        dp[1] = 2; // n = 2
        for (int i = 2; i < n; i++)
        {
            // dp[3] = dp[2] + dp[1]
            dp[i] = dp[i-1] + dp[i-2];
        }
        return dp[n-1];
    }
};
