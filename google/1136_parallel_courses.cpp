#include <vector>
#include <set>
#include <stack>
#include <queue>

using namespace std;


// 4 / 39 testcases passed
class Solution {
public:

    int minimumSemesters(int n, vector<vector<int>>& relations) {
        // this is a graph problem
        // it must be a DAG
        // we need to track how many levels when search from the "root"

        // build a ds to know what are next courses, and calculate the degree
        vector<set<int>> vs(n, set<int>());
        vector<int> inDegree(n, 0);

        for (auto& relation : relations)
        {
            int pre = relation[0] - 1;
            int next = relation[1] - 1;
            vs[pre].insert(next);
            inDegree[next]++;
        }

        /*
        // we start with vertex with 0 in-degree
        // we can DFS, if find loop then -1
        // 1 -> 2 -> 3 -> 4 -> 5
        //   ----------------> 5
        // we might set node 1 to level 2
        // we can carry a level in each DFS, increase by 1 each time.
        // when we are iterative, it is hard to use single variable.
        int ans = 0;
        int noZeroDegree = 1;
        for (int i = 0; i < n; i++)
        {
            if (inDegree[i] == 0)
            {
                noZeroDegree = 0;
                // iterative
                stack<pair<int, int>> s;
                s.push(make_pair(i,1));
                // how to determine cycle under iterative?
                // do we still need visited vector? when to set?
                // if we just want to validate cycle or not, but not recursive, any simpler way?
                while (s.size())
                {
                    auto& node = s.top();
                    int level = node.second;
                    ans = level > ans ? level : ans;
                    s.pop();
                    for (int next : vs[node.first])
                    {
                        s.push(make_pair(next, level + 1));
                    }
                }
            }
        }
        if (noZeroDegree)
            return -1;
        return ans;
        */

        /*********************************/
        /* we can't DFS in iterative way */
        /* no way to check cycle         */
        /*********************************/

        // try BFS, interative
        int ans = 0;
        int noZeroDegree = 1;
        queue<int> q;
        for (int i = 0; i < n; i++)
        {
            if (inDegree[i] == 0)
            {
                q.push(i);
            }
        }

        int level = 0;
        queue<int> subQ;
        while (q.size())
        {
            int node = q.front();
            q.pop();
            for (int next : vs[node])
            {
                subQ.push(next);
            }
            if (q.size() == 0)
            {
                level++;
                q = subQ;
                queue<int> tmp;
                subQ = tmp;
            }
        }
        // same question, how to detect cycle?
        // we can't push to queue like this
        // we must wait other routes all finish, then push, it means
        // we still need to modify inDegree
        if (level == 0)
            return -1;
        return level;
    }
};

/*
// needs redo
class Solution {
public:
    vector<set<int>> graph;
    vector<int> inDegree;
    int ans = 1;

    int dfs(int course, vector<int>& visited, int level)
    {
        // cout << course << endl;
        if (visited[course] == 1)
        {
            return -1;
        }
        if (visited[course] == 2)
        {
            return 0;
        }
        visited[course] = 1;

        if (level > ans)
        {
            ans = level;
        }
        for (int next : graph[course])
        {
            if (-1 == dfs(next, visited, level + 1))
                return -1;
        }

        visited[course] = 2;
        return 0;
    }
    int minimumSemesters(int n, vector<vector<int>>& relations) {
        inDegree.resize(n+1);
        graph.resize(n+1, set<int>{});
        // find degree in the same time
        for (auto& relation : relations)
        {
            int pre = relation[0];
            int next = relation[1];
            graph[pre].insert(next);
            inDegree[next]++;
        }

        // iterate all 0 degree
        int started = 0;
        queue<int> q;
        for (int i = 1; i <= n; i++)
        {
            if (inDegree[i] == 0)
            {
                started = 1;
                q.push(i);

                // vector<int> visited(n+1, 0);
                // int level = 1;
                // if (-1 == dfs(i, visited, level))
                // {
                //     return -1;
                // }
            }
        }
        if (started == 0)
            return -1;

        int level = 0;
        int count = q.size();
        // how to increase level?
        // we need to remember the size of each round
        while (q.size())
        {
            int course = q.front();
            q.pop();
            for (int next : graph[course])
            {
                q.push(next);
            }
            count--;
            if (count == 0)
            {
                level++;
                count = q.size();
            }
        }
        ans = level;

        return ans;
    }
};
*/
