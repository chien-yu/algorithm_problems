class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        // find the most overlapping interval
        sort(intervals.begin(), intervals.end(), [](vector<int>& first, vector<int>& end){
            return first[0] < end[0];
        });

        ////////////////////////////////////////////////////
        // First thought is too simple, we always need to
        // check all previous end time
        ////////////////////////////////////////////////////
        // [  ]
        //   [   ]
        //     [   ]
        //      [ ]
        // see the 2nd interval overlap, do what?
        //   check if 1st end > 2nd start
        //     no -> current end is 2nd end
        //        [  ]
        //             [  ]
        //     yes -> current end is 1st end
        //       what do I remember?
        //       [  ]
        //         [   ]
        //        [ ] <- this is impossible, this we already sort
        //               so we don't need to remember start of 1st
        // [     ]
        //   [ ] <- do I need one more room? yes
        //      [   ] <- do I need one more room? no
        //        [   ] <- do I needco one more room? yes?
        //
        // [     ]
        //   [    ]
        //      [   ]
        //
        // [          ]
        //   [    ]
        //      [   ]
        //
        // [          ]
        //   [  ]
        //        [  ]
        int currentEnd = intervals[0][1];
        int ans = 1;
        for (int i = 1; i < intervals.size(); i++)
        {
            auto& v = intervals[i];
            if (currentEnd > v[0])
            {
                // overlap
                // end keep the same.
                ans++;
            }
            else
            {
                currentEnd = v[1];
            }
        }
        return ans;

        ////////////////////////////////////////////////////
        // First thought is too simple, we always need to
        // check all previous end time
        ////////////////////////////////////////////////////
        // [     ]
        //   [    ]
        //      [   ] <- check previous 2 end time
        //         [  ] <- remove 2 passed end time
        //
        // [        ]
        //   [ ]
        //       [ ] <- remove 1 passed end time, and still 1 unpassed
        //
        // need to keep the end time in order, easier to remove and check
        // pq
        priority_queue<int, vector<int>, greater<int>> pq;
        pq.push(intervals[0][1]);
        int ans = 1;
        for (int i = 1; i < intervals.size(); i++)
        {
            auto& v = intervals[i];
            while (pq.size())
            {
                int end = pq.top();
                if (v[0] < end)
                {
                    // [   ]
                    //    [   ]
                    // all other end time are latter
                    // no room can be free
                    break;
                }
                else
                {
                    // [  ]
                    //    [  ]
                    pq.pop();
                }
            }
            // already free room, add now
            pq.push(v[1]);
            if (pq.size() > ans) ans = pq.size();
        }
        return ans;
    }
};