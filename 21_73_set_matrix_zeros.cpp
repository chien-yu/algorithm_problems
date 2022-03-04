class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        // we don't want to create
        // another vector m,n to store which row/column to
        // 0, so we must reuse the matrix's place
        //
        // 1 0 0 1 1
        // 1 1 1 1 1 
        // 1 1 1 0 1
        // ^ maybe try to reuse this column? then visit later
        //
        //
        // O 0 0 O 1
        // 1 1 1 1 1 
        // O 1 1 0 1
        // bool bCorner = false;
        bool bFirstColumn = false;
        bool bFirstRow = false;
        int m = matrix.size();
        int n = matrix[0].size();
        for (int i = 0; i < n; i++)
        {
            if (matrix[0][i] == 0)
            {
                bFirstRow = true;
                // bCorner = true;
            }
        }
        for (int i = 0; i < m; i++)
        {
            if (matrix[i][0] == 0)
            {
                bFirstColumn = true;
                // bCorner = true;
            }
        }
        for (int i = 1; i < m; i++)
        {
            // work from row 1
            if (matrix[i][0] == 0)
            {
                continue;
            }
            for (int j = 1; j < n; j++)
            {
                if (matrix[i][j] == 0)
                {
                    matrix[i][0] = 0;
                    break;
                }
            }
        }
        for (int j = 1; j < n; j++)
        {
            // work from column 1
            if (matrix[0][j] == 0)
            {
                continue;
            }
            for (int i = 1; i < m; i++)
            {
                if (matrix[i][j] == 0)
                {
                    matrix[0][j] = 0;
                    break;
                }
            }
        }
        
        // update matrix
        for (int i = 1; i < m; i++)
        {
            for (int j = 1; j < n; j++)
            {
                if (matrix[0][j] == 0 || matrix[i][0] == 0)
                    matrix[i][j] = 0;
            }
        }
        
        if (bFirstRow)
        {
            for (int j = 0; j < n; j++)
            {
                matrix[0][j] = 0;
            }
        }
        if (bFirstColumn)
        {
            for (int i = 0; i < m; i++)
            {
                matrix[i][0] = 0;
            }
        }

    }
};
