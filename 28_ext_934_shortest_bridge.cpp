class Solution {
public:
    int shortestBridge(vector<vector<int>>& grid) {
        // use dfs to form one island
        // then search bfs until reach another island
        n = grid.size();
        bool found = false;
        for (int i = 0; i < n && !found; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == 1)
                {
                    found = true;
                    dfs(i, j, grid);
                    break;
                }
            }
        }
        
        // use queue to bfs
        int distance = 0;
        int thisDistanceSize = nodes.size();
        // cout << thisDistanceSize << endl;
        int count = 0;
        #if 1
        while (nodes.size())
        {
            vector<int> node = nodes.front();
            nodes.pop();
            count++;
            for (auto& dir : directions)
            {
                int i = node[0] + dir[0];
                int j = node[1] + dir[1];
                if (i < 0 || j < 0 || i >= n || j >= n)
                    continue;
                if (grid[i][j] == 0)
                {
                    grid[i][j] = 2; //visited
                    // cout << i << " " << j << endl;
                    nodes.push({i, j});
                }
                else if (grid[i][j] == 1)
                {
                    return distance;
                }
            }
            if (count == thisDistanceSize)
            {
                // cout << thisDistanceSize << endl;
                distance++;
                thisDistanceSize = nodes.size();
                count = 0;
            }
        }
        #else
        // int dir[5] = {0, 1, 0, -1, 0};
        while (!nodes.empty()) {
            queue<vector<int>> q1;
            while (nodes.size()) {
                vector<int>& node = nodes.front();
                int i = node[0];
                int j = node[1];
                nodes.pop();
                for (auto& dir : directions)
                {
                    int x = i + dir[0];
                    int y = j + dir[1];
                    if (x < 0 || y < 0 || x >= n || y >= n)
                        continue;
                    else
                    {
                // for (int d = 0; d < 4; ++d) {
                //     int x = i + dir[d], y = j + dir[d + 1];
                //     if (min(x, y) >= 0 && max(x, y) < grid.size()) {
                        if (grid[x][y] == 1)
                        {
                            return distance;
                        }
                        if (grid[x][y] == 0) {
                            grid[x][y] = grid[i][j] + 1;
                            q1.push({x, y});
                        }
                    }
                }
            }
            swap(nodes, q1);
            cout << nodes.size() << endl;
            distance++;
        }
        #endif
        return distance;
    }
    bool dfs(int i, int j, vector<vector<int>>& grid)
    {
        // visiting == 2, so won't loop
        if (i < 0 || j < 0 || i >= n || j >= n)
            return false;
        if (grid[i][j] >= 2)
            return true;
        if (grid[i][j] == 0)
            return true;;
        grid[i][j] = 2;
        bool connectToZero = false;
        for (auto& dir : directions)
        {
            int ii = i + dir[0];
            int jj = j + dir[1];
            if (dfs(ii, jj, grid) && grid[ii][jj] == 0)
            {
                connectToZero = true;
            }
        }
        if (connectToZero)
        {
            nodes.push({i,j});
        }

        grid[i][j] = 3; // first island
        return true;
    }
private:
    int n;
    queue<vector<int>> nodes;
    vector<vector<int>> directions = {{1,0}, {-1,0}, {0,-1},{0,1}};
};
