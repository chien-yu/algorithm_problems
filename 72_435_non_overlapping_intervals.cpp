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

// 2/12/22
// quick
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), [](auto& v1, auto& v2){
            return v1[0] < v2[0];
        });
        
        // case 1:
        //   |------|
        //    |----|  earlier
        // case 2:
        //   |------|
        //    |--------| later
        int currentEnd = intervals[0][1];
        int numRemove = 0;
        for (int i = 1; i < intervals.size(); i++)
        {
            auto& itv = intervals[i];
            if (itv[0] < currentEnd)
            {
                // overlap, must take out 1
                numRemove++;
                if (currentEnd > itv[1])
                {
                    // use the new interval
                    currentEnd = itv[1];
                }
            }
            else
            {
                currentEnd = itv[1];
            }
        }
        return numRemove;
    }
};
