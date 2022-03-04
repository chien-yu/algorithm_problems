// old
class Solution {
public:
    vector<int> dp;
    bool canJump(vector<int>& nums) {
        // can jump to index i?
        // dp[0], can jump to 0, yes
        // dp[1], can jump to 1?
        //   dp[0] is yes and nums[0] larger than 1
        // dp[2], depends on dp[0] and dp[1]
        // or, nums[i] just update all following dp?
        if (nums.size() == 1)
            return true;
        dp.resize(nums.size()); // 0 means hasn't reach
        dp[0] = 1;
        // update first index can jump to
        int count = nums[0];
        for (int i = 1; i < nums.size() && count > 0; i++)
        {
            dp[i] = 1;
            count--;
        }
        for (int i = 1; i < nums.size(); i++)
        {
            // update from previous
            if (dp[i] == 0)
                continue;
            if (i == nums.size() - 1)
                break;
            count = nums[i];
            for (int j = i+1; j < nums.size() && count > 0; j++)
            {
                dp[j] = 1;
                count--;
            }
        }
        return (dp[nums.size() - 1] == 1);
    }
//         int size = nums.size();
//         // backward?
//         // find who can reach to the last?
//         if (size == 1)
//             return true;
//         if (size == 2)
//             return nums[0] >= 1;
//         dp = vector<int>(size, 0);
        
//         // bottom up
//         dp[0] = 1;
//         dp[1] = nums[0] >= 1;
//         for (int i = 2; i < size; i++)
//         {
//             bool res = false;
//             for (int j = i-1; j >= 0; j--)
//             {
//                 if (nums[j] >= i - j)
//                 {
//                     if (dp[j] == 1)
//                     {
//                         res = true;
//                         break;
//                     }
//                 }
//             }
//             if (res)
//             {
//                 dp[i] = 1;
//             }
//         }
//         return dp[size - 1] == 1;
//         // return canJumpTo(size - 1);
//     }
    
    
    // bool canJumpTo(vector<int>& nums, int last)
    // {
    //     if (dp[last] == 1)
    //         return true;
    //     if (dp[last] == 0)
    //         return false;
    //     // if dp[last] == -1
    //     // start from n = 3, last 2 elemental
    //     if (last - 1 < 0)
    //         return false;
    //     for (int i = last - 1; i >= 0; i--)
    //     {
    //         if (nums[i] == size - 1 - i)
    //         {
    //             // found
    //             return cap
    //         }
    //     }
    // }
};

// timeout
// but add the end check to pass.
class Solution {
public:
    bool canJump(vector<int>& nums) {
        // see who can jump to last index first?
        // then check who can jump to those pre index?
        // or
        // just start from the beginning, mark each
        // reachable index on the way of iteration.

        // 0 means unable
        // 1 means can jump to
        vector<int> state(nums.size(), 0);
        // dont need to check last one
        state[0] = 1;
        for (int i = 0; i < nums.size() - 1; i++)
        {
            if (state[i] == 0)
                continue;
            for (int j = 1; j <= nums[i]; j++)
            {
                // there are nums[i] possible next place
                if (i+j >= nums.size())
                {
                    // don't care
                    continue;
                }
                else if (i+j == nums.size() - 1)
                {
                    return true;
                }
                state[i+j] = 1;
            }
        }
        
        return state.back() == 1;
    }
};

// O(n)
class Solution {
public:
    bool canJump(vector<int>& nums) {
        // we just need to find the farest point
        int n = nums.size();
        int i = 0;
        int maximum = 0; // max possible location
        // i at 0 in the begin time
        for (; i < n; i++)
        {
            if (i > maximum)
            {
                // we can't reach to i
                break;
            }

            // nums[i] is the farest point on i
            maximum = max(i + nums[i], maximum);
        }
        return i == n;
    }
};
