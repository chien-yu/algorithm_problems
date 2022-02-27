// 1-time solution
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        // [2,3,6,7], target = 7
        // pick 2, reminder 5
        // pick 2 again or pick 3. (2+ paths)
        // if we go all the way, pick all 2.
        // then how to swtich to start from 3?
        
        // if reminder is 5 now.
        // i will try 2, but also try 3
        vector<int> tmpAns;
        sort(candidates.begin(), candidates.end());
        internal(candidates, tmpAns, 0, target);
        return ansLists;
    }
    void internal(vector<int>& candidates, vector<int>& tmpAns, int startIdx, int target)
    {
        for (int i = startIdx; i < candidates.size(); i++)
        {
            int v = candidates[i];
            if (target < v)
            {
                break;
            }
            else if (target == v)
            {
                vector<int> ans = tmpAns;
                ans.push_back(v);
                ansLists.push_back(ans);
                break;
            }
            else
            {
                vector<int> ans = tmpAns;
                ans.push_back(v);
                // give chance to find same element
                internal(candidates, ans, i, target - v);
            }
        }
    }
private:
    vector<vector<int>> ansLists;
};
