class Solution {
public:
    int characterReplacement(string s, int k) {
        if (s.size() == 1)
            return 0;
        if (s.size() == 2)
        {
            if (s[0] == s[1])
                return 2;
            else
            {
                if (k >= 1)
                    return 2;
                else
                    return 1;
            }
        }
        // build a running window
        // the most freq char + k == window size, then it is max size window
        int left = 0;
        map<char, int> m;
        m[s[0]]++;
        m[s[1]]++;
        int mostCount = 1;
        int right = 1;
        int ans = 1;
        while (right < s.size() && left <= right)
        {
            int winSize = right - left + 1;
            int maxCount = max_element(m.begin(), m.end(), [](const auto& p1, const auto& p2){
                return p1.second < p2.second;
            })->second;
            // cout << left << " " << right << " " << maxCount << endl;
            if (maxCount + k >= winSize)
            {
                if (ans < winSize)
                    ans = winSize;
                right++;
                m[s[right]]++;
            }
            else
            {
                // move left
                m[s[left]]--;
                left++;
            }
        }
        return ans;
    }
};
