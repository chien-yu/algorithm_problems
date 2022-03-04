class Solution {
public:
    int maxArea(vector<int>& height) {
        int max = 0;
        int i = 0;
        int j = height.size() - 1;
        while (i < j)
        {
            int minHeight = min(height[i], height[j]);
            int tmp = minHeight * (j - i);
            if (max < tmp)
                max = tmp;
            if (height[i] > height[j])
                j--;
            else
                i++;
        }
        return max;
    }
};
