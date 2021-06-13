class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        // priority_queue<int, vector<int>, greater<int>> pq;
        map<int, int> m;
        for (int n : nums)
        {
            ++m[n];
        }
        // sort by value
        vector<pair<int, int>> m_v;
        for (auto& obj : m)
        {
            m_v.emplace_back(obj.first, obj.second);
        }
        sort(m_v.begin(), m_v.end(), [](const pair<int, int>& p1, const pair<int, int>& p2) {
            return (p1.second > p2.second);
        });
        vector<int> ans;
        auto itr = m_v.begin();
        for (int i = 0; i < k; i++)
        {
            auto& p = *itr;
            ans.push_back(p.first);
            itr++;
        }
        return ans;
    }
};
