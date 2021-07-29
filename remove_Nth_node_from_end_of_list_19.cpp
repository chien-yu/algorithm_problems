/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

/*
Given the head of a linked list, remove the nth node from the end of the list and return its head.

Input: head = [1,2,3,4,5], n = 2
Output: [1,2,3,5]
*/
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // go to end, O(N)
        // then we can know where is N-n
        // then go to N-n-1, and go to N-n+1
        // and connect them
        // maybe use 2 pointers
        // [1,2]
        // 1 <= n <= sn
        // ptr
        // ptr2 = ptr + n
        // if ptr2 reach sn
        // then ptr at sn - N

        // test, if n = 1, it means the last one
        //   5 -> 6 -> 7
        //            ptr2
        //       ptr1
        // take ptr1 and connect next to ptr1->next->next
        // dry run
        // if n = 2
        // 4 -> 5 -> 6 -> 7
        //               ptr2
        //     ptr1
        
        // corner case:
        // if sn = 1, n must = 1

        // when sn = n, first one is removed
        // dummy -> 1 -> 2 -> null
        //              ptr2
        // ptr1
        if (!head->next)
            return nullptr;
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode* ptr1 = dummy;
        ListNode* ptr2 = ptr1;
        for (int i = 0; i < n; i++)
        {
            ptr2 = ptr2->next;
        }
        while (ptr2)
        {
            if (!ptr2->next)
                break;
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
        ListNode* connectTo = ptr1->next->next;
        ptr1->next = connectTo;
        return dummy->next;
    }
};