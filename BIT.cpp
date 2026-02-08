#include <iostream>
#include <vector>

using namespace std;

class MaxBIT { // One-based indexing
    vector<int> bit;
public:
    MaxBIT(int size) {
        bit.resize(size + 1);
    }
    int get(int idx) {
        cout << "get idx:" << idx;
        int ans = 0;
        for (; idx > 0; idx -= idx & -idx)
            ans = max(ans, bit[idx]);
        cout << " value is: " << ans << endl;
        return ans;
    }
    void update(int idx, int val) {
        cout << "update idx:" << idx << " with val:" << val <<endl;
        for (; idx < bit.size(); idx += idx & -idx)
            bit[idx] = max(bit[idx], val);
    }
};
class Solution { // 16 ms, faster than 72.16%
public:
    int lengthOfLIS(const vector<int>& nums) {
        // int BASE = 10001;
        // MaxBIT bit(20001);
        int BASE = 0;
        MaxBIT bit(8);
        for (int x : nums) {
            int subLongest = bit.get(BASE + x - 1);
            bit.update(BASE + x, subLongest + 1);
        }
        // return bit.get(20001);
        return bit.get(8);
    }
};

int main()
{
    Solution s;
    cout << s.lengthOfLIS(vector<int>{1, 2, 3}) << endl;
    return 0;
}