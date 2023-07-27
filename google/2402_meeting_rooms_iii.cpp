#include <queue>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    using RoomNumber = int;
    using FinishedTime = int;
    using Room = pair<FinishedTime, RoomNumber>;
    int mostBooked(int n, vector<vector<int>>& meetings) {
        // I think the most important hint is all start time are unique
        // looks like just simulate this
        // n = 3, meetings = [[1,20],[2,10],[3,5],[4,9],[6,8]]
        // we can definitely sort the meetins based on start time

        // ---------------------------------------> time
        // 0   [      1-20            ]
        // 1    [  2-10   ][6-8]
        // 2     [3-5][4-9]
        //       <-  7   ->
        //

        // we can just marked the ending time of each meetings
        // when allocating meetings, just check which rooms has smallest finished time
        // [1,20]
        //   0:0
        //   1:0
        //   2:0
        //   update:
        //   0:20 (finish at min 20)
        //
        // [2,10]
        //   we can see room 1 has smallest ftime
        //   update:
        //   0:20
        //   1:10
        //   2:0

        // looks like we need to quickly know which room has smallest ft
        // use a priority queue here? so we can know which room has smallest very quick, and
        // can update easily

        sort(meetings.begin(), meetings.end(), [](auto& v1, auto& v2){
            return v1[0] < v2[0]; // use less in sort to keep the smallest in the front
        });

        // build pq for rooms
        // the room with smallest finished time in the top
        // when we get the ft, we should also get which room it is
        // pair<FT, ROOM_NUM
        // auto cmp = [](const auto& lhs, const auto& rhs){
        //     return lhs.first > rhs.first; // use greater to keep smallest in the top
        // };
        // priority_queue<Room, vector<Room>, decltype(cmp)> pqBusy(cmp);
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pqBusy;

        // smallest room number on top
        priority_queue<RoomNumber, vector<RoomNumber>, greater<RoomNumber>> pqFree;

        for (int i = 0; i < n; i++)
        {
            pqFree.push(i);
        }

        vector<int> count(n, 0);
        int curMax = 0;
        int ansRoom = n;

        for (auto& meeting : meetings)
        {
            int startTime = meeting[0];
            int endTime = meeting[1];

            // see if any busy is free now
            while (pqBusy.size() && pqBusy.top().first <= startTime)
            {
                RoomNumber num = pqBusy.top().second;
                pqBusy.pop();
                pqFree.push(num);
            }

            // assign room
            RoomNumber num = 0;
            if (pqFree.size())
            {
                num = pqFree.top();
                pqFree.pop();
                pqBusy.push(make_pair(endTime, num));
            }
            else
            {
                // all busy need delay
                num = pqBusy.top().second;
                FinishedTime t = pqBusy.top().first;
                pqBusy.pop();
                // [   5-10   ]
                //  [       6-16    ]
                // [   5-10   ]
                //            [    10-20 ]
                pqBusy.push(make_pair(t + endTime - startTime, num));
            }

            if (num >= n)
                cout << "GG\n";
            count[num]++;
            if (count[num] > curMax)
            {
                curMax = count[num];
                ansRoom = num;
            }
            else if (count[num] == curMax)
            {
                if (num <= ansRoom)
                {
                    ansRoom = num;
                }
            }

            // [0,20] [1,10] [3,5] [15,18]
            // 0: [         0-20           ]
            // 1:  [  1-10   ]     [15-18]
            // 2:   [3-5]
            //                      
            //  0->20, 1->10, 2->0  pq top is 0
            //  [15, 18)
            // I see the problem, we could have multiple room available
            // right now room 1 and 2 both ready, but rule is to use the smaller number first
            // maybe we should build another pq for room are ready?
            // or, when we get new startTime, before we push, we should check all the value, to update
            // which room is ready?
            // in this way we don't need pq? just always check from room 0 to see where we have space?
            // we could have another var to track the min finished time?
            //   if smaller than this meeting's start, then we at least know we don't need to delay
            //   when we need to delay, the pq becomes useful, because it wait untils first free
            //
            //   if no delay, just search from room 0 (complexity might become O(N^2), if last room is mostly free)
            //   how do I know if I search from room 0 is faster? or going from top of pq is faster?
            //
            // hint is another PQ for free room
        }

        // find first max element
        return ansRoom;
    }

};

int main()
{
    Solution s;
    vector<vector<int>> meetings = {{0,10}, {1,2}, {12,14}, {13,15}};
    cout << s.mostBooked(2, meetings) << endl;;

    return 0;
}