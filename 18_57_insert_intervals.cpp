// old
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> ans;
        int left = newInterval[0];
        int right = newInterval[1];
        int idx = 0;
        for ( ;idx < intervals.size(); idx++)
        {
            if (intervals[idx][1] < left)
            {
                ans.push_back(intervals[idx]);
            }
            else
            {
                break;
            }
        }
        
        int newLeft = left;
        int newRight = right;
        for ( ;idx < intervals.size(); idx++)
        {
            if (intervals[idx][0] > right)
                break;

            // find the min
            if (newLeft > intervals[idx][0])
            {
                newLeft = intervals[idx][0];
            }
            
            if (newRight < intervals[idx][1])
                newRight = intervals[idx][1];
        }
        // add merged interval
        ans.push_back(vector<int> {newLeft, newRight});
        
        for ( ;idx < intervals.size(); idx++)
        {
            // put the rest
            ans.push_back(intervals[idx]);
        }
        return ans;
    }
};

// 1 time
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        // [   ]
        //        [     ]
        //   [  ]
        // if (intervals.size() == 0)
        //     return vector<vector<int>>{newInterval};
        vector<vector<int>> ans;
        
        int left = newInterval[0];
        int right = newInterval[1];
        int i = 0;
        for (; i < intervals.size(); i++)
        {
            int curLeft = intervals[i][0];
            int curRight = intervals[i][1];
            if (newInterval[0] > curRight)
            {
                ans.push_back(intervals[i]);
                continue;
            }
            if (newInterval[1] < curLeft)
            {
                break;
            }
            // else if (newInterval[0] <= curRight)
            left = min(left, curLeft);
            right = max(right, curRight);
        }
        ans.push_back(vector<int>{left, right});
        // push the rest
        for (; i < intervals.size(); i++)
        {
            ans.push_back(intervals[i]);
        }
        return ans;
    }
};
