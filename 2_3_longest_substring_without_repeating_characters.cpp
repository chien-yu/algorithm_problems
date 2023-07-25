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

// 7/25/2023
#include <iostream>
#include <string>
#include <unordered_map>
#include <cassert>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // sliding window
        // prepare a map to count each character
        // input space is ASCII?
        // if there are any char count larger than 1, we start to move left pointer

        if (s.size() <= 1)
            return s.size();
        if (s.size() == 2)
            return s[0] == s[1] ? 1 : 2;
        int i = 0, j = 0;
        unordered_map<char, int> buf;

        int answer = 0;
        while (i <= j && j < s.size())
        {
            // start from left, move j until counter larger 1
            // or until j == size - 1 (right-most)
            char dupC = '\0';
            for (; j < s.size(); j++)
            {
                if (buf.count(s[j]) == 0 || buf[s[j]] == 0)
                {
                    buf[s[j]] = 1;
                    answer = answer < (j - i + 1) ? (j - i + 1) : answer;
                }
                else
                {
                    buf[s[j]]++;
                    dupC = s[j];
                    // cout << dupC << endl;
                    break;
                }
            }

            // move i
            if (dupC != '\0')
            {
                for (; i <= j; i++)
                {
                    buf[s[i]]--;
                    if (s[i] == dupC)
                    {
                        if (buf[s[i] < 0])
                        {
                            assert(false);
                        }
                        i++;
                        break;
                    }
                }
            }

            // handle okay, back to move j
            j++;
        }
        return answer;
    }
};
