class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if (intervals.size() <= 1)
            return 0;
        // same as the max of remaining intervals
        sort(intervals.begin(), intervals.end(), [](vector<int>& v1, vector<int>& v2){
            return v1[0] < v2[0];
        });
        // for (auto v : intervals)
        //     cout << v[0] << endl;
        int ans = 0;
        int prevIdx = 0;
        for (int i = 1; i < intervals.size(); i++)
        {
            auto& prev = intervals[prevIdx];
            auto& cur = intervals[i];
            if (prev[1] > cur[0])
            {
                ans++;
                if (prev[1] > cur[1])
                    prevIdx = i;
            }
            else // prev[1] <= cur[0]
            {
                prevIdx = i;
            }
        }
        
        return ans;
    }
};
