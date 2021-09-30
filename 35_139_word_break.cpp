class Solution {
public:
    //////////////////////////
    // dp
    //////////////////////////
    bool wordBreak(string s, vector<string>& wordDict) {
        vector<int> dp(s.size(), -1); // 1 means from index i to end, there is a solution. // 0 mean no solution
        set<string> word_set(wordDict.begin(), wordDict.end());
        return hasSolutionFrom(0, dp, s, word_set);
    }
    bool hasSolutionFrom(int start, vector<int>& dp, string s, set<string>& word_set)
    {
        if (start == s.size())
        {
            // there is no more, all s matches
            return true;
        }
        if (dp[start] != -1)
        {
            return dp[start];
        }
        for (int idx = start; idx < s.size(); idx++)
        {
            string strToCheck = s.substr(start, idx - start + 1);
            // cout << strToCheck << endl;
            if (word_set.find(strToCheck) != word_set.end())
            {
                // got to find next
                bool res = hasSolutionFrom(idx + 1, dp, s, word_set);
                if (res)
                {
                    dp[start] = 1;
                    return dp[start];
                    // cout << "found " << start << endl;
                }
            }
        }
        return dp[start] = 0;
    }

    //////////////////////////
    // dp, but loop wordDict
    //////////////////////////

    // x
    // xxx
    // xxxxxxx
    // if these are all the words, then we can know we don't need to check the position 1, since
    // there is no word can starts from there.
    // just go to each possible position, and try all words.
    // complexity is k * N
    vector<int> dp(s.size() + 1, 0);
    // dp[i] means the sequence can start in pos i, which mean ends in i-1
    // if word is aaa
    // dp[3] is 1
    for (string word : wordDict)
    {
        int size = word.size();
        if (word.size() > s.size()) continue;
        string tmpS = s.substr(0, size);
        if (word == tmpS)
        {
            dp[size] = 1;
        }
    }
    for (int i = 1; i < s.size(); i++)
    {
        if (dp[i])
        {
            for (string word : wordDict)
            {
                // leetcode
                // i = 4
                //     apple
                int size = word.size();
                if (i + word.size() > s.size()) continue;
                string tmpS = s.substr(i, size);
                // leetcode
                // i = 4
                //     cat
                if (word == tmpS)
                {
                    dp[i + size] = 1;
                }
            }
        }
    }
    return dp[s.size()] == 1;

    // https://leetcode.com/problems/word-break/discuss/43908/4-different-ways-to-solve-this-with-detailed-explanation.
};