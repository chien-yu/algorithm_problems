class Solution {
public:
    int maxProduct(vector<int>& nums) {
        // 0 to reset
        // key point is that answer must start from begin or end on last one
        int n = nums.size();
        int ans = nums[0];
        int product = 1;
        for (int i = 0; i < n; i++)
        {
            // product until index i
            if (product == 0)
            {
                //reset
                product = nums[i];
            }
            else
            {
                product = product * nums[i];
            }
            ans = max(ans, product);
        }
        
        // iterate from the back
        product = 1;
        for (int i = n-1; i >= 0; i--)
        {
            if (product == 0)
            {
                product = nums[i];
            }
            else
            {
                product = product * nums[i];
            }
            ans = max(ans, product);
        }
        return ans;
    }
};
