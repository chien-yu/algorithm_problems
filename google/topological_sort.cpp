#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cassert>
#include <random>

using namespace std;

/*
direction enum
N = 1
S = 1 << 1
E = 1 << 2
W = 1 << 3
*/
// enum class Direction
// {
//     N = 1,
//     S = 1 << 1,
//     E = 1 << 2,
//     W = 1 << 3,
// };

#define Dir_N 1
#define Dir_S 2
#define Dir_E 4
#define Dir_W 8
#define Dir_NE Dir_N | Dir_E
#define Dir_SE Dir_S | Dir_E
#define Dir_NW Dir_N | Dir_W
#define Dir_SW Dir_S | Dir_W

// #define LOG()

struct Entry
{
    int p1;
    int p2;
    // Direction d;
    int d;
};

class Solution {
private:
    // p1
    // ^
    // p2
    void addNS(int p1, int p2)
    {
        graphNS[p1][p2] = 1;
    }

    // p2 -> p1
    void addEW(int p1, int p2)
    {
        graphEW[p1][p2] = 1;
    }

    int bfs(int N, int cur, vector<int>& visited, vector<vector<int>>& graph)
    {
        if (visited[cur] == 2)
            return 0;
        if (visited[cur] == 1)
        {
            cout << cur << " dup\n"; 
            return 1; // error
        }

        visited[cur] = 1;
        progress.push_back(cur);
        // go child first
        for (int i = 0; i < N; i++)
        {
            if (graph[cur][i]) // has child
            {
                if (1 == bfs(N, i, visited, graph))
                {
                    return 1;
                }
            }
        }
        visited[cur] = 0;
        progress.pop_back();
        return 0;
    }

    int process(int N, vector<vector<int>>& graph)
    {
        // turns all points into graph in 2D array

        // 0: not yet visit
        // 1: visiting
        // 2: visited
        vector<int> visited(N);

        // iterator from any point
        for (int i = 0; i < N; i++)
        {

            // logging
            progress.resize(0);

            // put all next to a queue
            // if B->C, B->D
            // we need to finish C and D first
            // it is like BFS
            
            // recursive
            if (1 == bfs(N, i, visited, graph))
            {
                return 1;
            }

            // iterative
            // for ()

        }
        return 0;
    }

    vector<vector<int>> graphNS;
    vector<vector<int>> graphEW;

    // logging
    vector<int> progress;
public:
    void printProgress()
    {
        int init = 1;
        for (int i : progress)
        {
            if (init)
            {
                cout << i;
                init = 0;
            }
            else
            {
                cout << " -> " << i;
            }
        }
        cout << endl;
    }
    bool check(vector<Entry>& data, int N) {
        // we need to process in 2 direction N-S and E-W
        // each direction put into a directed graph to check cycle

        graphNS.resize(N, vector<int>(N));
        graphEW.resize(N, vector<int>(N));

        for (Entry e : data)
        {
            // validate p1 p2 value

            if (e.d & Dir_N)
            {
                addNS(e.p1, e.p2);
            }
            else if (e.d & Dir_S)
            {
                addNS(e.p2, e.p1);
            }

            if (e.d & Dir_E)
            {
                addEW(e.p1, e.p2);
            }
            else if (e.d & Dir_W)
            {
                addEW(e.p2, e.p1);
            }
/*
            switch (e.d)
            {
                case Dir_N:
                    addNS(e.p1, e.p2);
                    break;
                case Dir_S:
                    addNS(e.p2, e.p1);
                    break;
                case Dir_E:
                    addEW(e.p1, e.p2);
                    break;
                case Dir_W:
                    addEW(e.p2, e.p1);
                    break;
                case Dir_NE:
                    addNS(e.p1, e.p2);
                    addEW(e.p1, e.p2);
                    break;
                case Dir_SE:
                    addNS(e.p2, e.p1);
                    addEW(e.p1, e.p2);
                    break;
                case Dir_NW:
                    addNS(e.p1, e.p2);
                    addEW(e.p2, e.p1);
                    break;
                case Dir_SW:
                    addNS(e.p2, e.p1);
                    addEW(e.p2, e.p1);
                    break;
                default:
                    assert(false);
            }
*/
        }

        if (process(N, graphNS) || process(N, graphEW))
            return 1;
        else
            return 0;
    }
};


int main() {
    vector<Entry> data;

    Solution s1;

    int N = 10;

    // Create a random number generator engine
    std::random_device rd; // Seed the generator with a true random value from the OS
    std::mt19937 gen(rd()); // Mersenne Twister 19937 engine (a widely used random number generator)

    // Create a uniform distribution for integers within the range
    int min_value = 0;
    int max_value = N - 1;
    std::uniform_int_distribution<int> dist(min_value, max_value);
    std::vector<int> directions = {Dir_N, Dir_S, Dir_E, Dir_W, Dir_NE, Dir_SE, Dir_NW, Dir_SW};

    for (int i = 0; i < 15; i++)
    {
        int r1 = dist(gen);
        int r2 = dist(gen);
        while (r1 == r2) {
            r2 = dist(gen); // Keep generating the second random number until it's different from the first
        }
        data.push_back({r1, r2, directions[r1 % 8]});
        cout << "r1: " << r1 << ", r2: " << r2 << ", d: " << directions[r1 % 8] << endl;
    }

    int result = s1.check(data, N);
    cout << "result: " << result << endl;
    if (result)
     s1.printProgress();

    return 0;
}
