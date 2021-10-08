class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        // find a start point word[0], and BFS
        int index = 0;
        for (int i = 0 ; i < board.size(); i++)
        {
            for (int j = 0; j < board[0].size(); j++)
            {
                // 0, unvisited
                // 1, visiting
                // 2, found, can't be reuse
                vector<vector<int>> visited(board.size(), vector<int>(board[0].size(), 0));
                if (board[i][j] == word[index])
                {
                    // cout << "top: " << " i: " << i << ", j: " << j << endl;
                    if (bfs(board, word, visited, i, j, index + 1))
                    {
                        return true;
                    }
                    visited[i][j] = 0;
                }
            }
        }
        return false;
    }
    
    bool bfs(vector<vector<char>>& board, string& word, vector<vector<int>>& visited, int i, int j, int index)
    {
        // cout << "index: " << index << " finding: " << word[index] << " current i: " << i << ", j: " << j <<  endl;
        if (visited[i][j] == 1)
        {
            // can't use duplicate cell
            return false;
        }
        if (index == word.size())
        {
            return true;
        }
        visited[i][j] = 1;
        vector<vector<int>> dir = { {1,0}, {-1,0}, {0,1}, {0,-1}};
        for (auto d : dir)
        {
            int ii = i + d[0];
            int jj = j + d[1];

            if (ii >= 0 && ii < board.size() && jj >= 0 && jj < board[0].size())
            {
                // cout << "i: " << ii << ", j: " << jj << " [" << board[ii][jj] << "]" << endl;
                if (board[ii][jj] == word[index])
                {
                    if (bfs(board, word, visited, ii, jj, index + 1))
                    {
                        return true;
                    }
                }
            }
        }
        visited[i][j] = 0;
        return false;   
    }
};

// nice
class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        // dfs search
        // dfs(i) search from index i
        // we can start from 0,0, and from beginning of the word
        m = board.size();
        n = board[0].size();
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (dfs(board, word, i, j, 0))
                    return true;
            }
        }
        
        return false;
    }
    
    // return true if we can find the end
    // if any neighbor don't have mapping char on index i, return false
    // see if i,j on board is word[idx], then run dfs on neighbor to find word[idx+1]
    // if go backward, return false;
    bool dfs(vector<vector<char>>& board, string word, int i, int j, int idx)
    {
        // even out of boundary, since we already finish all word
        if (idx == word.size())
            return true;
        
        if (i < 0 || i >= m || j < 0 || j >=n)
            return false;
        if (word[idx] != board[i][j])
            return false;
        
        // same cell can't be reused, so we can't go backward
        char backupC = board[i][j];
        board[i][j] = '*';
        for (auto& dir : directions)
        {
            int ii = i + dir[0];
            int jj = j + dir[1];
            if (dfs(board, word, ii, jj, idx + 1))
                return true;
        }
        board[i][j] = backupC;
        return false; 
    }
    
    int m;
    int n;
    vector<vector<int>> directions = { {1,0}, {-1, 0}, {0, 1}, {0,-1} };
};
