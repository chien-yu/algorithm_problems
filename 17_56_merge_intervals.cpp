// old
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if (intervals.size() == 1)
            return intervals;
        //sort by first index
        vector<vector<int>> ans;
        auto compare = [](vector<int> v1, vector<int> v2){
              return v1[0] < v2[0];
        };
        std::sort(intervals.begin(), intervals.end(), compare);
        // for (auto v : intervals)
        //     cout << v[0] << " " << v[1] << endl;
        
        // how many cases?
        // [  ]
        //   [   ]
        //

        //
        // keep current windows boundary
        // [  ]
        // if next left are no within, then create current windows
        // if next within, update window boundary
        int left = intervals[0][0];
        int right = intervals[0][1];
        bool bWindowBuffer = false;
        for (auto v: intervals)
        {
            int ll = v[0];
            int rr = v[1];
            if (ll > right)
            {
                // [  ]
                //        [    ]
                ans.push_back(vector<int>({left, right}));
                left = ll;
                right = rr;
                bWindowBuffer = false;
            }
            else // ll <= right
            {
                // [   ]
                //    [    ]
                right = max(rr, right);
                bWindowBuffer = true;
            }
        }
        // flush, it won't double flush
        ans.push_back(vector<int>({left, right}));
        return ans;
    }
};

// 1 time
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), [](auto& v1, auto& v2){
            return v1[0] < v2[0];
        });
        // cases:
        // [    ]
        //   [ ]
        //
        // [    ]
        //     [   ]
        //
        // [    ]
        //        [   ]
        vector<vector<int>> ans;
        int left = intervals[0][0];
        int right = intervals[0][1];
        for (int i = 1; i < intervals.size(); i++)
        {
            int newLeft = intervals[i][0];
            int newRight = intervals[i][1];
            if (newLeft <= right)
            {
                right = max(newRight, right);
            }
            else
            {
                ans.push_back(vector<int>{left, right});
                left = newLeft;
                right = newRight;
            }
        }
        ans.push_back(vector<int>{left, right});
        
        return ans;
    }
};
