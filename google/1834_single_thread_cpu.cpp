#include <queue>
#include <utility>
#include <iostream>

using namespace std;

// 15 / 39 testcases passed
class Solution {
public:
    vector<int> getOrder(vector<vector<int>>& tasks) {
        // sort the tasks so we can find the first one
        // [[1,2],[2,4],[3,2],[4,1]]
        // at time 2, we can't process, but we can update
        // the waiting queue
        // I guess is priority queue
        // we can remember the task ID and finish time, and use
        // finished time as key
        // (3, 0): task 0 finished at time 3
        // top is 3
        // (6, 1): need to be at time 2, but time 2 is busy
        // 3 > 2
        // finished time = 6 + (3-2) = 7
        // but we need to check more, it is possible the next task with shorter processing time
        // [          ]
        //   [     ]
        //     [ ]       <- this is chose next
        //       [ ]
        //             ^--- at this time
        // so we should hold a PQ with key is process time

        // p1 is processing time, p2 is index
        // smaller processing time on top, so need greater comparator.
        // smaller index on top, greater cmp.
        auto f = [](auto& p1, auto& p2){
            if (p1.first == p2.first)
                return p1.second > p2.second;
            return p1.first > p2.first;
        };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(f)> pqReady(f);
        // we need to put all due tasks into pq

        // // sort task first
        // // smaller enqueueTime first, so less cmp.
        // sort(tasks.begin(), tasks.end(), [](auto& v1, auto& v2){
        //     return v1[0] < v2[0];
        // });
        // but if we sort, I lost the index I need to report, should I add them to another
        // pq, and return the smaller enqeueTime?
        // this pq we need smaller enqeueTime on top, smaller index on top
        auto f2 = [](auto& p1, auto& p2){
            if (p1.first == p2.first)
                return p1.second > p2.second;
            return p1.first > p2.first;
        };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(f2)> pqEnqueue(f2);
        for (int i = 0; i < tasks.size(); i++)
        {
            int enqueueTime = tasks[i][0];
            pqEnqueue.push(make_pair(enqueueTime, i));
        }

        vector<int> ans;
        // we know first one is pqEnqueue.top()
        // and we know finished time is tasks[i][0] + tasks[i][1]
        // before this time finish, we have sorted tasks by enqueueTime
        //
        //    [    ]
        //      [ ]
        // but this doesnt mean the top will get processed first, so we just use this PQ to find first one?
        // no, we need to push all ready tasks into another pq, which can make
        //      [ ]
        //    [    ]
        // the order we want to process, this is pqReday, which mean we ready to process after
        // a certain time.

        // define init cond
        int lastFinishedTime = 0;

        // debug state
        // tasks =     [[1,2],[2,4],[3,2],[4,1]]
        // pqEnqueue = [[1,0],[2,1],[3,2],[4,3]]
        //
        // in while loop
        // [1,0] must be first to process
        // pqReady = [[2,0]]
        // pqEnqueue = [[2,1],[3,2],[4,3]]
        // lastFinishedTime = 3
        // we should queue in [2,1] and [3,2]
        // pqReady = []
        //
        // next round
        // pqEnqueue = [[4,3]]
        // pqReady = [[2,2],[4,1]]
        // lastFinishedTime = 5
        //
        // this round we and queue in [4,1]

        while (pqEnqueue.size() || pqReady.size())
        {
            // prepare ready task
            int nextEnqueueTime = pqEnqueue.top().first;
            int taskIdx =  pqEnqueue.top().second;
            // empty
            if (lastFinishedTime <= nextEnqueueTime)
            {
                lastFinishedTime = nextEnqueueTime;
            }

            // we should have lastFinishedTime now, since there are task waiting
            // [          ]  <- processing
            //    [  ]
            //      [  ]
            // put other to ready queue
            while (pqEnqueue.size() && pqEnqueue.top().first <= lastFinishedTime)
            {
                nextEnqueueTime = pqEnqueue.top().first;
                taskIdx =  pqEnqueue.top().second;
                // add ready tasks
                if (nextEnqueueTime <= lastFinishedTime)
                {
                    // key is processingTime
                    pqReady.push(make_pair(tasks[taskIdx][1], taskIdx));
                    pqEnqueue.pop();
                }
                else
                {
                    break;
                }
            }

            // process
            int nextTaskIdx = pqReady.top().second;
            ans.push_back(nextTaskIdx);
            auto& task = tasks[nextTaskIdx];
            // new timing
            // |-----[   ]
            if (lastFinishedTime <= task[0])
            {
                lastFinishedTime = task[0] + task[1];
            }
            //       |
            //   [ ]
            // the next task is waiting
            else
            {
                lastFinishedTime += task[1];
            }
            
            pqReady.pop();
        }
        return ans;
    }
};

int main()
{
    auto f = [](auto& p1, auto& p2){
        cout << "compare " << p1.first << "," << p1.second << " to " << p2.first << "," << p2.second << endl;
        if (p1.first == p2.first)
            return p1.second > p2.second;
        return p1.first < p2.first;
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(f)> pq(f);
    cout << "adding 1,1\n";
    pq.push(make_pair(1, 1));
    cout << "adding 1,2\n";
    pq.push(make_pair(1, 2));
    cout << "adding 2,3\n";
    pq.push(make_pair(2, 3));
    cout << "adding 2,4\n";
    pq.push(make_pair(2, 4));
    while (pq.size())
    {
        cout << pq.top().first << ", " << pq.top().second << endl;
        pq.pop();
    }

    return 0;
}