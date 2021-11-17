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

class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        // it is a bit hard to flow down, since we don't know the state until
        // we reach the ocean. do it backward is easier
        // find a cell to flow to which ocean, and mark it
        // so later dfs can be easier
        // check the return value, if contains both, then save it
        vector<vector<int>> po(heights.size(), vector<int>(heights[0].size(), 0));
        vector<vector<int>> ao(heights.size(), vector<int>(heights[0].size(), 0));
        vector<vector<int>> ans;

        // start from po
        for (int i = 0; i < heights.size(); i++)
        {
            dfs_up(i, 0, po, heights);
            dfs_up(i, heights[0].size() - 1, ao, heights);
        }
        for (int j = 0; j < heights[0].size(); j++)
        {
            dfs_up(0, j, po, heights);
            dfs_up(heights.size() - 1, j, ao, heights);
        }

        for (int i = 0; i < heights.size(); i++)
        {
            for (int j = 0; j < heights[0].size(); j++)
            {
                if (po[i][j] && ao[i][j])
                {
                    ans.emplace_back(std::initializer_list<int>{i, j});
                }
            }
        }
        
        return ans;
    }
    
    void dfs_up(int i, int j, vector<vector<int>>& m, vector<vector<int>>& heights)
    {
        if (i < 0 || i >= heights.size() || j < 0 || j >= heights[0].size())
            return;
        if (m[i][j] == 1)
            return;

        m[i][j] = 1;
        
        for (auto dir :directions)
        {
            int ii = i + dir[0];
            int jj = j + dir[1];
            if (ii < 0 || ii >= heights.size() || jj < 0 || jj >= heights[0].size())
                continue;
            if (heights[i][j] <= heights[ii][jj])
            {
                dfs_up(ii, jj, m, heights);
            }
        }
    }

    vector<vector<int>> directions = {{1,0}, {0,1}, {-1,0}, {0,-1}};
};
