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

class Solution {
public:
    // string minWindow(string s, string t) {
    // The final answer's start/end point must on a matched character.
    // Only need to check the char in s which occurs in candidata t. O(n)
    // There is no need to keep multiple answer in a list. If we anvance
    // the start point carefully, we know the end point won't move too far.
    
    int cToI(char c)
    {
        int index = 0;
        if (isupper(c))
            index = (c - 'A') + 26;
        else
            index = c - 'a';
        return index;
    }
    string minWindow(string s, string t) {
        // build a table of t
        // a=0, z=25, A=26, Z=51
        vector<int> table(52, 0);
        for (char c : t)
        {
            table[cToI(c)]++;
        }
        
        vector<int> refTable(table);
        int count = t.size();
        int start = 0;
        int end = 0;
        int answer = s.size() + 1; // impossible
        int answerStart = 0;
        while (end < s.size())
        {
            char c = s[end];
            int indexOfC = cToI(c);
            // char existing in t
            //
            // Noted, not refTable but table, since we want to find char we miss
            // to fulfill the table list.
            // Important, if there is an over-fit char, like 
            // A..BBBBB..C
            // we need to know there are multiple B, and can skip so of them.
            // if t is "ABBC", then are 3 unused.
            //
            // A..BBBBB..C
            // [         ] first match
            //             there should be somewhere to store 5, and know the start pointer need to skip 3.
            //       [    ...] should be next, only contains 2 B.
            // It was 2, from t, and then minus 5, to -3 and to 2, so we have to count each matched char
            // First pointer to minus, if == 0, found, when count == 0, then first all match.
            // And second pointer to increase, A will back to 1.
            // For the B case, it will back to 1 on 4th B, so it is good.
            // How about unmatched one? If we decrease unmatched, then it can back to 0 later.
            table[indexOfC]--;
            if (count && table[indexOfC] >= 0)
            {
                count--;
                if (count == 0)
                {
                    // advance start until next matched char
                    char cStart = s[start];
                    table[cToI(cStart)]++;
                    while (table[cToI(cStart)] <= 0)
                    {
                        // not yet find minimal window, advance
                        start++;
                        cStart = s[start];
                        table[cToI(cStart)]++;
                    }
                    // reach here means the start points to matched
                    // update answer
                    int tmpAns = end - start + 1;
                    if (tmpAns < answer)
                    {
                        answerStart = start;
                        answer = tmpAns;
                    }
                    start++;
                    count++;
                }
            }
            end++;
        }

        if (answer < s.size() + 1)
        {
            return s.substr(answerStart, answer);
        }
        else
            return "";
    }
};

// One time KO
class Solution {
public:
    string minWindow(string s, string t) {
        vector<int> dict(128, 0);
        for (char c : t)
        {
            dict[c]++;
        }
        int count = t.size();
        int left = 0;
        int ansStart = 0;
        int ansSize = s.size() + 1;
        for (int i = 0; i < s.size(); i++)
        {
            char c = s[i];
            // move right pointer
            dict[c]--; // need to make it 0, can go negative
            // but if go negative, don't decrease count
            if (dict[c] >= 0 /*&& count*/)
            {
                count--;
                if (count == 0)
                {
                    // all t found
                    // ready to move left pointer
                    while (1)
                    {
                        char cc = s[left];
                        dict[cc]++;
                        // go above 0 means we skip the key one.
                        // go back to 0 could be just non-key
                        // if still negative?
                        // t = AB
                        // s = A C A C B C A A B
                        if (dict[cc] > 0)
                        {
                            count++;
                            if (i - left + 1 < ansSize)
                            {
                                ansStart = left;
                                ansSize = i - left + 1;
                            }
                            // record the state, could move pointer to find new
                            left++;
                            break;
                        }
                        // move to find boundray
                        left++;
                    }
                }
            }
        }
        return ansSize == s.size() + 1 ? "" : s.substr(ansStart, ansSize);
    }
};


// okay okay
class Solution {
public:
    string minWindow(string s, string t) {
        
        if (s.size() == 1)
        {
            return s == t ? s : "";
        }
        // still 2 pointers
        // first pointer on any first match
        // then go until we find all match
        // how to move the left pointer?
        // move to any place that has match
        //
        // ADOBEC
        // then move left to
        //    BEC       -> invalid
        // then move right
        //    BECODEBA
        //      CODEBA  -> valid
        //          BA
        //          BANC
        // basically you stop on every key char
        map<char, int> dic;
        set<char> setOfS;
        for (char c : t)
        {
            dic[c]++;
            setOfS.insert(c);
        }
        // dic represents the number we need to find.
        // set s is to check if it is key char
        int left = 0;
        int m = s.size();
        // first find all key char
        int right = left;
        int n = t.size();
        int nMatch = 0;
        int minLength = m + 1;
        int ansStart = 0;
        for (; right < m; right++)
        {
            if (setOfS.count(s[right]))
            {
                if (dic[s[right]] > 0)
                {
                    dic[s[right]]--;
                    nMatch++;
                }
                else// if (dic[s[right]] <= 0)
                {
                    dic[s[right]]--;
                    // extra match
                    // t = ABBC
                    // s = A B B B B C
                    //           ^ we don't count match anymore
                }
            }
            // what happen if we see it twice?
            // A B B B D D D D
            // we should mark 2nd and 3rd B differently?
            // since we just need 1B, we should know we
            // can move to 3rd B if we move left pointer.
            //   ^1 -> 0
            //     ^0 -> -1
            //       ^-1 -> -2
            // when move left
            //   ^-2 -> -1
            //     ^-1 -> 0
            //       ^0 -> 1, stop when it becomes positive
            // this works when we have 2B
            if (nMatch == n)
            {
                // all found, need to move left
                for (; left <= right; left++)
                {
                    // t = ABC
                    // s = D A B C D A
                    if (setOfS.count(s[left]))
                    {
                        if (dic[s[left]] < 0)
                        {
                            dic[s[left]]++;
                            // continue
                        }
                        else if (dic[s[left]] == 0)
                        {
                            // t = ABBC
                            // s = A B B B B C
                            //     ^ should decrease nMatch to find next A
                            //           ^ should decrease to find next B
                            nMatch--;
                            dic[s[left]]++;
                            if (right - left + 1 < minLength)
                            {
                                minLength = right - left + 1;
                                ansStart = left;
                            }
                            left++;
                            break;
                        }
                    }
                }
            }
        }
        if (minLength == m+1)
            return "";
        return s.substr(ansStart, minLength);
    }
};
