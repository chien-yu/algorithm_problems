class Solution {
public:
    long long countVowels(string word) {
        // use different size of window in every round?
        int n = word.size();
        long long ans = 0;
        set<char> vowels = {'a', 'e', 'i', 'o', 'u'};
        // abcdefg
        //
        // a
        // ab
        // abc
        // ...
        // abcdefg     <----- i == 0
        //  b
        //  bc
        //  ...
        //  bcdefg
        //
        //      f      <----- i == n-2
        //      fg
        //       g     <----- i == n-1
        //       ^ this will see 1n times
        //      ^ this will see 2(n-1) times
        //     ^ 3(n-2)
        // ^(n)1
        for (int i = 0; i < n; i++)
        {
            if (vowels.count(word[i]))
            {
                // i == 0
                // n-0 * 0+1
                // i == n-1
                // n-(n-1) * n-1+1
                ans += (long)(long)(n-i) * (i+1);
            }
        }
        // for (int i = n-1; i >= 0; i++)
        // {
        //     // string tmp;
        //     for (int j = i; j < n; j++)
        //     {
        //         // i is the start index, j is the end index
        //         // tmp += word[j];
        //         // if we already see vowels when we are in j, then
        //         // we must see in j ~ n-1
        //         if (vowels.count(word[j]))
        //         {
        //             ans += n-1 - j + 1;
        //         }
        //     }
        // }
        return ans;
    }
};
