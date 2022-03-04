// first try
class Solution {
public:
    int search(vector<int>& nums, int target) {
        // 4 5 6 7 8 1 2 3, t = 2
        //       ^
        // 7 > 2, and 4 > 2, so the other side
        //           ^
        // 1 < 2, and
        if (target < nums[0] || target > nums[nums.size()-1])
            return -1;
        return search(nums, target, 0, nums.size() - 1);
    }
    
    int search(vector<int>& nums, int target, int left, int right)
    {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target)
            return mid;
        if (nums[left] == target)
            return left;
        if (nums[right] == target)
            return right;
        if (left > right)
            return -1;
        if (left == right && nums[left] != target)
            return -1;
        if (nums[left] > nums[right])
        {
            // rotated
            if (nums[mid] > nums[left])
            {
                if (nums[left] < target && target < nums[mid])
                {
                    return search(nums, target, left + 1, mid - 1);
                }
                else
                {
                    return search(nums, target, mid + 1, right);
                }
            }
            else
            {
                if (nums[mid] < target && target < nums[right])
                {
                    return search(nums, target, mid + 1, right - 1);
                }
                else
                {
                    return search(nums, target, left, mid - 1);
                }
            }
        }
        else
        {
            // non rotated
            if (nums[mid] > target)
            {
                return search(nums, target, left, mid - 1);
            }
            else
            {
                return search(nums, target, mid + 1, right);
            }
        }
    }
};

// tune a lot
class Solution {
public:
    int search(vector<int>& nums, int target) {
        // 4 5 6 7 8 1 2 3, t = 2
        //       ^
        // 7 > 2, and 4 > 2, so the other side
        //           ^
        // 1 < 2, and
        // if (target < nums[0] || target > nums[nums.size()-1])
        //     return -1;
        return search(nums, target, 0, nums.size() - 1);
    }
    
    int search(vector<int>& nums, int target, int left, int right)
    {
        // cout << left << " " << right << endl;
        int mid = left + (right - left) / 2;
        if (nums[mid] == target)
            return mid;
        if (nums[left] == target)
            return left;
        if (nums[right] == target)
            return right;
        if (left > right)
            return -1;
        if (left == right && nums[left] != target)
            return -1;
        
        // only 2 left, boundary check above
        if (left + 1 == right || left + 2 == right)
        {
            return -1;
        }
        
        if (nums[left] < nums[mid])
        {
            if (nums[left] < target && target < nums[mid])
            {
                return search(nums, target, left + 1, mid - 1);
            }
            else
            {
                return search(nums, target, mid + 1, right);
            }
        }
        else
        {
            if (nums[mid] < target && target < nums[right])
            {
                return search(nums, target, mid + 1, right - 1);
            }
            else
            {
                return search(nums, target, left, mid - 1);
            }
        }
    }
};
