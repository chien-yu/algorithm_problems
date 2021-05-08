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


class SolutionDP {
public:
    int coinChange(vector<int>& coins, int amount) {
        // from bottom
        if (amount < 1) return 0;
        vector<int> dp(amount + 1, 0); // work from bottom, doesn't care init value
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
                if (tmpAns == 0) // can't fit
                    continue;
                if (tmpAns < ans)
                    ans = tmpAns;
            }
            if (ans == i+1)
                dp[i] = -1;
            else
                dp[i] = ans;
        }
        return dp[amount];
    }

};
