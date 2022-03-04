class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        // think from back?
        int n = cost.size();
                    
        vector<int> dp(n, 0);
        // this record the best cost
        dp[0] = cost[n-1];
        dp[1] = cost[n-2]; // you won't pay extra cost[n-1]...
        // then need to think about how far to go
        // dp[2] = cost[n-3] + min(dp[1], dp[0]);
        for (int i = 2; i < n; i++)
        {
            dp[i] = cost[n-1-i] + min(dp[i-1], dp[i-2]);
        }
        
        return min(dp[n-1], dp[n-2]);
    }
};
