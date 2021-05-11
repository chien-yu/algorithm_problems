class Solution {
public:
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
};
