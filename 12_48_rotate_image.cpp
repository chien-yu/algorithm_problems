// old
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        // do it every 4
        int n = matrix.size();
        
        // diagnal flip
        // vertical flip
        // method 1:
        // for (int y = n; y >= 0; y--)
        // {
        //     for (int x = n-y; x < n; x++)
        //     {
        //         // m[3-3,2] m[2,3-3]
        //         swap(matrix[n - y][x], matrix[x][n - y]);
        //     }
        // }
        // method 2: use the other side
        for (int y = 0; y < n; y++)
        {
            for (int x = 0; x < y; x++)
            {
                swap(matrix[y][x], matrix[x][y]);
            }
        }

        // // method 1:
        // for (int y = 0; y < n; y++)
        // {
        //     for (int x = 0; x < n/2; x++)
        //     {
        //         swap(matrix[y][x], matrix[y][n-1-x]);
        //     }
        // }
        // method 2:
        for (int y = 0; y < n; y++)
        {
            reverse(matrix[y].begin(), matrix[y].end());
        }
        

        // // 3x3 -> 1
        // // 4x4 -> 2
        // // 5x5 -> 2
        // for (int y = 0; y < n/2; y++)
        // {
        //     // 3x3 -> 2
        //     // 4x4 -> 3,1
        //     // 5x5 -> 4,2
        //     for (int x = 0; x < n - 1; x++)
        //     {
        //         // (matrix[0][0],
        //         // matrix[0][3],
        //         // matrix[3][3],
        //         // matrix[3][0]);
        //         (matrix[y][0],
        //         matrix[0][3],
        //         matrix[3][3],
        //         matrix[3][0]);
        //     }
        // }
    }
};

// 1 time
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        // move every row, same operation 4 times
        // possible simple mapping/flip?
        // flip from middle, then flip from diagnal
        
        // 1 swap
        for (vector<int>& v : matrix)
        {
            reverse(v.begin(), v.end());
        }
        int m = matrix.size();
        for (int i = 0; i < m - 1; i++)
        {
            for (int j = 0; j < m - 1 - i; j++)
            {
                // 0, 2 -> 1, 3
                // 2, 0 -> 3, 1
                swap(matrix[i][j], matrix[m-1-j ][m-1-i]);
            }
        }
    }
};