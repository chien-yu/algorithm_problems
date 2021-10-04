class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int sum = 0;
        for (int n : nums)
        {
            sum += n;
        }
        return (nums.size() * (nums.size() + 1) / 2) - sum;
        // test
        // nums = [0]
        // 1 * 2 / 2 - 0 = 1
    }
};
