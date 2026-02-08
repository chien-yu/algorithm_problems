class Solution {
public:
    int numDecodings(string s) {
        // dp
        
        int n = s.size();
        if (n == 1)
        {
            if (s[0] == '0')
                return 0;
            else
                return 1;
        }
        
        vector<int> dp(n, 0);
        // if starts from index i, how many way?
        // 0 can't be the start
        dp[n-1] = s[n-1] == '0' ? 0 : 1;
        if (s[n-2] == '0')
        {
            dp[n-2] = 0;
        }
        else if (s[n-2] == '1')
        {
            dp[n-2] = 1 + dp[n-1];
        }
        else if (s[n-2] == '2')
        {
            if (s[n-1] - '0' <= 6)
            {
                dp[n-2] = 1 + dp[n-1];
            }
            else
            {
                dp[n-2] = 1;
            }
        }
        else
        {
            dp[n-2] = dp[n-1];
        }
        
        for (int i = n-3; i >= 0; i--)
        {
            char c = s[i];
            if (c == '0')
                dp[i] = 0;
            else if (c == '1')
            {
                dp[i] = dp[i+1] + dp[i+2];
            }
            else if (c == '2')
            {
                char nextC = s[i+1];
                if (nextC - '0' <= 6)
                {
                    dp[i] = dp[i+1] + dp[i+2];
                }
                else
                {
                    dp[i] = dp[i+1];
                }
            }
            else
            {
                dp[i] = dp[i+1];
            }
        }
        
        return dp[0];
    }
};

// simplier
class Solution {
public:
    int numDecodings(string s) {
        // dp
        
        int n = s.size();
        if (n == 1)
        {
            if (s[0] == '0')
                return 0;
            else
                return 1;
        }
        
        vector<int> dp(n + 1, 0);
        // if starts from index i, how many way?
        // 0 can't be the start
        dp[n] = 1;
        dp[n-1] = s[n-1] == '0' ? 0 : 1;
//         if (s[n-2] == '0')
//         {
//             dp[n-2] = 0;
//         }
//         else if (s[n-2] == '1')
//         {
//             dp[n-2] = 1 + dp[n-1];
//         }
//         else if (s[n-2] == '2')
//         {
//             if (s[n-1] - '0' <= 6)
//             {
//                 dp[n-2] = 1 + dp[n-1];
//             }
//             else // 27 28 29
//             {
//                 dp[n-2] = 1;
//             }
//         }
//         else
//         {
//             dp[n-2] = dp[n-1];
//         }
        
        for (int i = n-2; i >= 0; i--)
        {
            char c = s[i];
            if (c == '0')
                dp[i] = 0;
            else if (c == '1')
            {
                dp[i] = dp[i+1] + dp[i+2];
            }
            else if (c == '2')
            {
                char nextC = s[i+1];
                if (nextC - '0' <= 6)
                {
                    dp[i] = dp[i+1] + dp[i+2];
                }
                else // 27 28 29
                {
                    dp[i] = dp[i+1];
                }
            }
            else
            {
                dp[i] = dp[i+1];
            }
        }
        
        return dp[0];
    }
};
