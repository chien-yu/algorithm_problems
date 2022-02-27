// old
class Solution {
public:
    string longestPalindrome(string s) {
        if (s.size() == 0)
            return "";
        if (s.size() == 1)
            return s;
        int mid = 0;
        int right_max = s.size()-1;
        
        // stats for answer
        int ans_left = 0;
        int max_length = 0;

        // keep moving mid
        while(mid <= right_max) {
            int right = mid;
            int left = mid;
            while (right<right_max && s[right+1]==s[right])
                right++; // Skip duplicate characters in the middle
            mid=right+1; //for next iter
            
            while (left >= 0 && right <= right_max && s[left] == s[right]) {
                left--;
                right++;
            }
            int new_length = right - left - 1; //right-1 - left-1 + 1
            if (new_length > max_length) {
                max_length = new_length;
                ans_left = left+1;
            }
        }
        return s.substr(ans_left, max_length);
    }
};

// 1-time solution
class Solution {
public:
    string longestPalindrome(string s) {
        // if start from "a", to 2 direction
        // then "aa" is good, "bab" is also good
        
        // iterate every character in first round
        // iterate on any dup pair in second round?
        
        // O(n^2)?
        int ansStart = 0;
        int ansLength = 0;
        
        int left = 0;
        int right = 0;
        for (int i = 0; i < s.size(); i++)
        {
            for (int d = 0; ; d++)
            {
                left = i - d;
                right = i + d;
                if (left >= 0 && right < s.size() &&
                   s[left] == s[right])
                {
                    if (right - left + 1 > ansLength)
                    {
                        ansStart = left;
                        ansLength = right - left + 1;
                    }
                    continue;
                }
                break;
            }
        }
        
        for (int i = 0; i < s.size() - 1; i++)
        {
            if (s[i] == s[i+1])
            {
                // start from 0 to record itself;
                for (int d = 0; ; d++)
                {
                    left = i - d;
                    right = i+1 + d;
                    if (left >= 0 && right < s.size() &&
                       s[left] == s[right])
                    {
                        if (right - left + 1 > ansLength)
                        {
                            ansStart = left;
                            ansLength = right - left + 1;
                        }
                        continue;
                    }
                    break;
                }
            }
        }
        
        return s.substr(ansStart, ansLength);
    }
};
