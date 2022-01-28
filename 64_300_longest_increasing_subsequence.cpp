class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if (nums.size() == 1) return 1;
        if (nums.size() == 2) return nums[1] > nums[0] ? 2 : 1;;
        // even you start on each index when you see
        // a smaller value, you still can't know which
        // sequence is optimal.
        // in each index, there is 2^n combination
        // 2, 100, 3, 4, 5
        // you can't just choose a larger number in sequence
        // basic algorithm is try to skip a possible number,
        // and try next one
        // 2, 100
        // 2, 3,
        vector<int> dp(nums.size(), 1);
        // dp[5] dp[6]
        // 2, 100, 3, 4, 5    1, smaller than last in sequence
        //                  101, larger than last in sequence
        // if nums[n+1] > nums[n]
        //   dp[n+1] = dp[n] + 1
        // else if nums[n+1] > nums[n-1]
        //   dp[n+1] = dp[n-1] + 1
        dp[0] = 1;
        dp[1] = nums[1] > nums[0] ? 2 : 1;
        int ans = dp[1];
        for (int i = 2; i < nums.size(); i++)
        {
            for (int j = i; j >= 1; j--)
            {
                if (nums[i] > nums[j-1])
                {
                    dp[i] = max(dp[i], dp[j-1] + 1);
                }
            }
            ans = max(ans,dp[i]);
        }
        return ans;
    }
};

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        if (n == 1)
            return 1;
        // work from the back
        // dp[K] is the longest length from element K to end
        vector<int> dp(n, 1);
        for (int i = n-2; i >= 0; i--)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (nums[i] < nums[j])
                {
                    dp[i] = max(dp[i], 1 + dp[j]);
                }
            }
        }
        return *max_element(dp.begin(), dp.end());
    }
};