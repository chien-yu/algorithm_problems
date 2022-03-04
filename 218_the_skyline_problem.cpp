// first try
class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        // iterate each x point
        // build a list of existing build on current x point
        // check the existing build on every x point
        
        // or just iterate on building's edge, they are only
        // point could change things.
        
        // build a list of all points (left and right)
        vector<vector<int>> xAxis;
        for (int i = 0; i < buildings.size(); i++)
        {
            xAxis.push_back({buildings[i][0], buildings[i][2]});
            xAxis.push_back({buildings[i][1], buildings[i][2]});
        }
        // sort
        sort(xAxis.begin(), xAxis.end(), [](auto& v1, auto& v2){
            // should v1 goes before v2?
            return v1[0] < v2[0];
        });
        
        vector<vector<int>> ans;
        for (auto v : xAxis)
        {
            cout << v[0] << endl;
        }
//         int currentHeight = 0; //highest
//         vector<vector<int>> remaining;
//         for (int i = 0; i < buildings.size(); i++)
//         {
//             int left = buildings[i][0];
//             int right = buildings[i][1];
//             int height = buildings[i][2];
            
//             for (auto remain : remaining)
//             {
//                 if (remain[0] <= left)
//                 {
                    
//                 }
//             }
//             if (height > currentHeight)
//             {
//                 ans.push_back({left, height});
//                 currentHeight = height;
//             }
//             // remember the end
//             remaining.push_back({right, height});
//         }
        return ans;        
    }
};

// pass first test case
class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        vector<vector<int>> xAxis;
        // 3 element per point.
        // x,y point, and then 0 means left edge, 1 means right edge
        for (int i = 0; i < buildings.size(); i++)
        {
            xAxis.push_back({buildings[i][0], buildings[i][2], 0});
            xAxis.push_back({buildings[i][1], buildings[i][2], 1});
        }
        // sort
        // if the x point the same, then taller comes first.
        sort(xAxis.begin(), xAxis.end(), [](auto& v1, auto& v2){
            // should v1 goes before v2?
            if (v1[0] < v2[0]) return true;
            if (v1[0] > v2[0]) return false;
            // equal
            return v1[1] > v2[1];
        });

        vector<vector<int>> ans;
        priority_queue<int> pq;
        pq.push(xAxis[0][1]); // tallest
        ans.push_back({xAxis[0][0], xAxis[0][1]});
        for (int i = 1; i < xAxis.size(); i++)
        {
            auto& v = xAxis[i];
            if (v[2] == 0)
            {
                // add
                int currentTop = pq.top();
                pq.push(v[1]);
                if (currentTop != pq.top())
                {
                    // record change
                    ans.push_back({v[0], v[1]});
                }
            }
            else
            {
                int currentTop = pq.top();
                if (currentTop == v[1])
                {
                    pq.pop();
                    // record new highest
                    if (pq.size())
                    {
                        ans.push_back({v[0], pq.top()});
                    }
                    else
                    {
                        ans.push_back({v[0], 0});
                    }
                }
                else
                {
                    vector<int> backup;
                    while (pq.top() != v[1])
                    {
                        backup.push_back(pq.top());
                        pq.pop();
                    }
                    if (pq.top() == v[1])
                    {
                        pq.pop();
                    }
                    for (auto v : backup)
                    {
                        pq.push(v);
                    }
                }
            }
        }
        // this priority q keep the existing build height, if passing
        // the right edge, then remove it.

        return ans;        
    }
};
