class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        // search from PO
        m = heights.size();
        n = heights[0].size();
        vector<vector<int>> t = { {1,0}, {-1,0},{0,1},{0,-1}};
        directions = t;
        // -1, visiting
        // 0, unvisit
        // 1, done, reach one
        vector<vector<int>> statePO(m, vector<int>(n, 0));
        vector<vector<int>> stateAO(m, vector<int>(n, 0));

        for (int r = 0; r < m; r++)
        {
            // r, 0
            flow(r, 0, heights, statePO);
            flow(r, n-1, heights, stateAO);
        }
        for (int c = 0; c < n; c++)
        {
            // 0, c
            flow(0, c, heights, statePO);
            flow(m-1, c, heights, stateAO);
        }
        // search from AO
        
        vector<vector<int>> ans;
        for (int r = 0; r < m; r++)
        {
            for (int c = 0; c < n; c++)
            {
                if (statePO[r][c] == 1 && stateAO[r][c] == 1)
                {
                    ans.push_back({r,c});
                }
            }
        }
        return ans;
    }
    void flow(int r, int c, vector<vector<int>>& heights, vector<vector<int>>& state)
    {
        state[r][c] = 1;

        for (auto& dir : directions)
        {
            int rr = r + dir[0];
            int cc = c + dir[1];
            if (rr >= m || cc >= n || rr < 0 || cc < 0)
                continue;
            if (state[rr][cc] == 1)
                continue;
            if (heights[rr][cc] >= heights[r][c])
                flow(rr,cc,heights, state);
        }
        // state[r][c] = 1;
    }
private:
    int m;
    int n;
    vector<vector<int>> directions;
};
