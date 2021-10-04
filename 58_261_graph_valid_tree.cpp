class Solution {
public:
    bool validTree(int n, vector<vector<int>>& edges) {
        // do a bfs search and make sure no cycle, and
        // reach to everyone
        // easier when convert the edges to a 2d matrix?
        vector<vector<int>> matrix(n, vector<int>(n, 0));
        vector<int> visited(n, 0);
        for (auto& e : edges)
        {
            matrix[e[0]][e[1]] = 1;
            matrix[e[1]][e[0]] = 1;
        }
        
        // this search can't go back, but how to determine a loop?
        // close the path!?
        if (bfs(0, n, matrix, visited) == false)
            return false;
        for (auto v : visited)
        {
            // any node unvisited
            if (v == 0)
                return false;
        }
        return true;
    }
    
    bool bfs(int node, int n, vector<vector<int>>& matrix, vector<int>& visited)
    {
        if (visited[node] == 1)
        {
            return false;
        }
        visited[node] = 1;
        for (int i = 0; i < n; i++)
        {
            if (matrix[node][i] == 1)
            {
                // close the path
                matrix[node][i] = 0;
                matrix[i][node] = 0;
                if (bfs(i, n, matrix, visited) == false)
                    return false;
            }
        }
        return true;
    }
};
