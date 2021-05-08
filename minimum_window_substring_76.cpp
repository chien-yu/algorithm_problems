class Solution {
public:
    // The final answer's start/end point must on a matched character.
    // Only need to check the char in s which occurs in candidata t. O(n)
    // The answer list grows when we see more matched chars. Checked if
    // the char list of t is fulfilled. O(n)
    // Complexity is O(n^2).
    struct Ans
    {
        int start;
        int end;
        int count;
        vector<int> table;
        Ans() :
            start(0),
            end(0),
            count(0)
        {}
    };
    string minWindow(string s, string t) {
        // start a new search history for each possible match.
        // build a table of t
        // a=0, z=25, A=26, Z=51
        vector<int> table(52, 0);
        for (char c : t)
        {
            int index = 0;
            if (isupper(c))
                index = (c - 'A') + 26;
            else
                index = c - 'a';
            table[index]++;
        }
        int count = t.size();
        vector<Ans> vAns;
        int idx = 0;
        for (char c : s)
        {
            int index = 0;
            if (isupper(c))
                index = (c - 'A') + 26;
            else
                index = c - 'a';
            // char existing in t
            if (table[index])
            {
                // check every possible answer
                for (auto& a : vAns)
                {
                    if (a.table[index] && a.count)
                    {
                        a.table[index]--;
                        a.count--;
                        if (a.count == 0)
                        {
                            a.end = idx;
                        }
                    }
                }
                
                // add itself to new posssible answer
                vAns.emplace_back();
                vAns.back().start = idx;
                vAns.back().end = s.size();
                vAns.back().count = count;
                vAns.back().table = table;
                // already seen one
                vAns.back().count--;
                vAns.back().table[index]--;    
                if (vAns.back().count == 0)
                {
                    vAns.back().end = idx;
                }
            }
            idx++;
        }
        
        int min = s.size();
        int targetStart = 0;
        int targetEnd = 0;
        bool found = false;
        for (auto ans : vAns)
        {
            if (ans.end >= s.size())
            {
                continue;
            }
            int d = ans.end - ans.start + 1;
            if (d <= min && d >= 0)
            {
                found = true;
                min = d;
                targetStart = ans.start;
                targetEnd = ans.end;
            }
        }
        if (found)
        {
            return s.substr(targetStart, targetEnd - targetStart +1);
        }
        else
            return "";
    }
};