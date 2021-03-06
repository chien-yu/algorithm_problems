// This timeout
class SolutionRecursive {
public:
    map<int, int> dp; // store f(x) = y in (x,y)
    int coinChange(vector<int>& coins, int amount) {
        // how to find sub problem?
        // target = 11
        // if I use 1,  then what is optimal for 11-1=10
        // remember these sub problem result, 10, 9, 8, ...
        
        // for 11,
        // take 1: f(10) + 1
        // take 2: f(9) + 1
        // take 5: f(6) + 1
        
        // for 6,
        // take 1: f(5) + 1
        // take 2: f(4) + 1
        // take 5: f(1) + 1
        
        // f(1), f(2), f(5) are all 1
        if (amount < 1)
            return 0;
        return sub(coins, amount);
    }
    int sub(vector<int>& coins, int amount)
    {
        if (amount < 0) return -1;
        if (amount == 0) return 0;
        if (dp.find(amount) != dp.end()) return dp[amount];

        if (find(coins.begin(), coins.end(), amount) != coins.end())
            return 1;
        // cout << "counting " << amount << endl;
        int ans = amount+1; // max
        bool found = false;
        for (auto v : coins)
        {
            int f = sub(coins, amount - v);
            if (f > 0)
            {
                int tmpAns = 1 + f;
                if (tmpAns < ans)
                {
                    ans = tmpAns;
                    dp[amount] = ans;
                    // cout << "found " << amount << " best at " << ans << endl;
                    found = true;
                }
            }
        }
        if (found)
        {
            return ans;
        }
        else
        {
            dp[amount] = -1;
            return -1;
        }
    }
};

// PASSED
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        // from bottom
        if (amount < 1) return 0;
        vector<int> dp(amount + 1, amount + 1); // do care the init value
        dp[0] = 0;
        for (int i = 1; i <= amount; i++)
        {
            int ans = i+1;
            for (auto coin : coins)
            {
                int remaining = i - coin;
                if (remaining == 0) ans = 1;
                if (remaining < 0 ) continue;
                int tmpAns = 1 + dp[remaining];
                if (dp[i] > tmpAns)
                    dp[i] = tmpAns;
            }
        }
        if (dp[amount] == amount + 1)
            return -1;
        return dp[amount];
    }
};

// timeout
class Solution {
public:
    Solution() :
        ans(0)
    {}
    map<int, int> dp;
    int coinChange(vector<int>& coins, int amount) {
        if (amount == 0)
            return 0;
        if (find(coins.begin(), coins.end(), amount) != coins.end())
        {
            return 1;
        }
        if (dp[amount] != 0)
            return dp[amount];
        
        int min = amount + 1;
        for (int c : coins)
        {
            if (c < amount)
            {
                int tmp = coinChange(coins, amount - c);
                if (tmp != -1 && tmp < min)
                    min = tmp;
            }
        }
        if (min == amount + 1)
            return -1;

        dp[amount] = min + 1;
        return dp[amount];
    }
};


// genuis
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<long> dp(amount + 1, INT_MAX);
        dp[0] = 0;

        for(auto i : coins)
            for(int j = i; j <= amount; j++)
                dp[j] = min(dp[j], 1 + dp[j - i]);

        return dp[amount] == INT_MAX ? -1 : dp[amount];
    }
};


// a terrible one
//         if (amount == 0)
//             return 0;
//         for (int i = 0; i < coins.size(); i++)
//         {
//             int c = coins[i];
            
//         }
//         find(coins, amount, 0);
//         if (ans == 0)
//             return -1;
//         return ans;
//     }

//     int find(vector<int>& coins, int target, int layer)
//     {
//         for (int c : coins)
//         {
//             if (c == target)
//             {
//                 if (ans == 0)
//                 {
//                     ans = layer + 1;
//                 }
//                 if (layer + 1 < ans)
//                 {
//                     ans = layer + 1;
//                 }
//                 return layer;
//             }
//             if (target > c)
//             {
//                 find(coins, target - c, layer + 1);
//             }
//             else
//             {
//                 return -1;
//             }
//         }
//         return -1;
//     }
