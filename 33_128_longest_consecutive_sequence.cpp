class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        // put everything in a set, to allow constant time look up
        // and only do search when that is the beginning'
        unordered_set<int> s;
        for (int i : nums)
        {
            s.insert(i);
        }
        
        int ans = 0;
        for (int i : s)
        {
            if (s.count(i-1) == 0)
            {
                int tmpAns = 1;
                int ii = i;
                while (s.count(++ii))
                {
                    tmpAns++;
                }
                if (tmpAns > ans) ans = tmpAns;
            }
        }
        return ans;
    }

    // first solution
    int longestConsecutive(vector<int>& nums) {
        // if we try to get O(n), the map we should use is set, so we have O(1) look up time.
        // every time add new item, just go both direction to get best answer
        // time complexity depends on the answer, since most of search could end up early.
        if (nums.size() == 0)
            return 0;
        set<int> s;
        int ans = 0;
        for (int n : nums)
        {
            if (s.find(n) != s.end())
            {
                // don't worry duplicate
                continue;
            }
            else
            {
                s.insert(n);
            }
            int count = 0;
            int back = n-1;
            while (s.find(back) != s.end())
            {
                count++;
                back--;
            }
            int forth = n+1;
            while (s.find(forth) != s.end())
            {
                count++;
                forth++;
            }
            if (count > ans)
                ans = count;
        }
        return ans + 1;
    }

    // another bad one
    int longestConsecutive(vector<int>& nums) {
        // if we try to get O(n), the map we should use is set, so we have O(1) look up time.
        // every time add new item, just go both direction to get best answer
        // time complexity depends on the answer, since most of search could end up early.
        if (nums.size() == 0)
            return 0;
        set<int> s;
        // try to record the longest answer's head and end, so we don't need to go too far
        // if 2 sequence are competing, then this helper might not be useful.
        int head = nums[0];
        int end = nums[0];
        int ans = 0;
        for (int n : nums)
        {
            if (s.find(n) != s.end())
            {
                // don't worry duplicate
                continue;
            }
            else
            {
                s.insert(n);
            }
            if (n <= end && n >= head)
            {
                // within the answer range, this must not reach. It is duplicate case
                continue;
            }
            else if (n == end + 1)
            {
                end = n;
                ans++;
                continue;
            }
            else if (n == head - 1)
            {
                head = n;
                ans++;
                continue;
            }
            int count = 0;
            int back = n-1;
            while (s.find(back) != s.end())
            {
                count++;
                back--;
            }
            int forth = n+1;
            while (s.find(forth) != s.end())
            {
                count++;
                forth++;
            }
            if (count > ans)
            {
                ans = count;
                head = back + 1;
                end = forth - 1;
            }
        }
        return ans + 1;
    }
};

// Other thinking, union find
// https://leetcode.com/problems/longest-consecutive-sequence/discuss/166544/Union-Find-Thinking-Process
