/*
Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]]
such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.

Notice that the solution set must not contain duplicate triplets.

Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]
*/

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        // reuse 2 sum
        vector<vector<int>> ans;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size() - 2; i++)
        {
            if (nums[i] <= 0 &&
                (i == 0 || nums[i - 1] != nums[i]))
            {
                twoSum(nums, i, ans);
            }
        }
        return ans;
    }
    
    void twoSum(vector<int>& nums, int i, vector<vector<int>>& ans)
    {
        unordered_set<int> dic;
        int target = (-1) * nums[i];
        for (int j = i + 1; j < nums.size(); j++)
        {
            if (dic.count(nums[j]) == 0)
            {
                dic.insert(target - nums[j]); // put the compensate
            }
            else
            {
                ans.push_back(vector<int> {nums[i], nums[j], target - nums[j]});
                // move j
                while ((j < nums.size() - 1) && (nums[j] == nums[j + 1]))
                {
                    j++;
                }
            }
        }
    }
};