// old
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if (s.empty())
            return 0;
        if (s.length() == 1)
            return 1;
        set<char> charSeen;

        int ans = 0;
        vector<int> prevLocations;
        int i = 0, j = 0, len = s.length();
        // i is the position our set starting to count
        while (i < len && j < len)
        {
            char ch = s[j];
            cout << "i: " << i << " j: " << j << endl;
            if (charSeen.count(ch))
            {
                // erase position i 
                charSeen.erase(s[i]);
                // cout << "ans is: " << j-i << endl;
                i++;
            }
            else
            {
                charSeen.insert(ch);
                j++;
                ans = max(ans, j - i);
            }
        }
        return ans;
    }
};


// again
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if (s.size() <= 1)
            return s.size();
        // use map to track the window's characters
        // use map or set?
        // i want access is O(1), also write and remove
        unordered_map<char, int> m;
        int left = 0;
        int right = 0;
        m[s[0]] = 1;
        int ans = 0;
        while (right < s.size() - 1)
        {
            if (m.count(s[right+1]))
            {
                // right+1 is repeated, try move left
                m.erase(s[left]);
                left++;
            }
            else
            {
                // no repeating
                right++;
                m[s[right]] = 1;
                ans = max(ans, right-left+1);
            }
        }
        return ans;
    }
};