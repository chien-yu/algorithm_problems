// old
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int n_x = matrix[0].size();
        int n_y = matrix.size();
        if (n_y == 1)
            return matrix[0];
        vector<vector<int>> mVisited(n_y, vector<int>(n_x, 0));
        vector<int> ans;
        if (n_x == 1)
        {
            for (auto a : matrix)
                ans.push_back(a[0]);
            return ans;
        }

        vector<vector<int>> directions { {1, 0}, // m[x][y]
                                  {0, 1},
                                 {-1, 0},
                                 {0, -1}};
        int idxDir = 0;
        int x = 0;
        int y = 0;
        while(1)
        {
            // seen visited twice, should end
            if (mVisited[y][x] == 1)
            {
                break;
            }
            else
            {
                cout << matrix[y][x] << " ";
                ans.push_back(matrix[y][x]);
                mVisited[y][x] = 1;
            }
            auto dir = directions[idxDir];
            int xx = x + dir[0];
            int yy = y + dir[1];
            if (xx == n_x ||
                xx == -1 ||
                yy == n_y ||
                yy == -1 ||
                mVisited[yy][xx] == 1)
            {
                idxDir = (idxDir+1) % 4;
                dir = directions[idxDir];
            }
            x += dir[0];
            y += dir[1];
        }
        return ans;
    }
};

// try boundary, but tedious
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        // use direction?
        // or iterate every bounardy? then
        // next round start from (n,n)
        int m = matrix.size();
        int n = matrix[0].size();
        // 2 -> 0
        // 3 -> 1
        // 4 -> 1
        int round = (min(m,n) + 1)/2 - 1;
        for (int d = 0; d <= round; d++)
        {
            getBoundary(matrix, d, m - 1 - d, n - 1 - d);
        }
        return ans;
    }
    
    // idx is the left top corner
    // mm, nn is the bottom right corner of the boundary
    // starts from (d,d) - > (mm, nn)
    void getBoundary(vector<vector<int>>& matrix, int d, int mm, int nn)
    {
        if (d > nn || d > mm)
            return;
        for (int j = d; j <= nn; j++)
        {
            ans.push_back(matrix[d][j]);
        }
        // do we need to go down?
        if (d+1 > mm)
            return;
        for (int i = d+1; i <= mm; i++)
        {
            ans.push_back(matrix[i][nn]);
        }
        // once we go down, then go left?
        if (nn <= d)
            return;
        for (int j = nn - 1; j >=0; j--)
        {
            ans.push_back(matrix[mm][j]);
        }
        for (int i = mm - 1; i >= d+1; i--)
        {
            ans.push_back(matrix[i][d]);
        }
    }
private:
    vector<int> ans;
};

// just simulate
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        // use direction? just simulate
        int m = matrix.size();
        int n = matrix[0].size();
        int top = 0;
        int bottom = m - 1;
        int left = 0;
        int right = n - 1;
        int direction = 0;
        while (top <= bottom && left <= right)
        {
            switch (direction) {
                case 0:
                {
                    for (int i = left; i <= right; i++)
                        ans.push_back(matrix[top][i]);
                    top++;
                    break;
                }
                case 1:
                {
                    for (int i = top; i <= bottom; i++)
                    {
                        ans.push_back(matrix[i][right]);
                    }
                    right--;
                    break;
                }
                case 2:
                {
                    for (int i = right; i >= left; i--)
                    {
                        ans.push_back(matrix[bottom][i]);
                    }
                    bottom--;
                    break;
                }
                case 3:
                {
                    for (int i = bottom; i >= top; i--)
                    {
                        ans.push_back(matrix[i][left]);
                    }
                    left++;
                    break;
                }
            }
            direction = (direction + 1) % 4;
        }
        return ans;    
    }
private:
    vector<int> ans;
};
