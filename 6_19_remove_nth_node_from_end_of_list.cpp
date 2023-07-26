#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // I don't know full length, O(n) can find out, then just one cut and connect.
        int count = 0;
        ListNode* ptr = head;
        while (ptr) {
            count++;
            ptr = ptr->next;
        }
        if (n > count)
            return head;

        // if count = 5, n = 2
        // 1->2->3->4->5
        //          ^ we need to connect 5-2 = 3 to 3+2
        // if n = 5
        // we return head->next
        if (n == count)
            return head->next;
        // if n = 4
        // connect 1->3
        int nodeToStart = count - n;
        // if nodeToStart = 1, don't need to move
        // don't need while loop
        nodeToStart--;
        ptr = head;
        while(nodeToStart)
        {
            ptr = ptr->next;
            nodeToStart--;
        }

        // ptr now is at where we should connect
        // corner case is n = 1, we don't need to reconnect but just cut
        if (n == 1)
        {
            // we should be on 2th from the end
            ptr->next = nullptr;
            return head;
        }

        // find next 2 and reconnect
        ListNode* nextTwo = ptr->next->next;
        ptr->next = nextTwo;
        return head;
    }
};

class Solution2 {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // we can just run 2 pointers at the same time
        // 1->2->3->4->5
        //       ^ connect
        //             ^ connectTo
        //             ^ n
        //
        // if n =4
        // 1->2->3->4->5
        // ^ connect
        //       ^ connectTo
        //             ^ end
        // so connect and end diff by n
        if (n == 0)
            return head;
        ListNode* dummy = new ListNode(0, head);
        ListNode* ptr1 = dummy;
        ListNode* ptr2 = dummy;
        // d->1->2
        // if n = 2
        // return 2, we need to connect d->2, and return d->next
        for (int i = 0; ptr2 && i < n; i++)
        {
            ptr2 = ptr2->next;
        }
        if (ptr2 == nullptr)
        {
            // n is too large
            return head;
        }
        while (ptr2 && ptr2->next)
        {
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
        ptr1->next = ptr1->next->next;
        return dummy->next;
    }
};

using namespace std;

int main()
{
    ListNode* head = new ListNode(1);
    ListNode* ptr = head;
    ptr->next = new ListNode(2);
    ptr = ptr->next;
    ptr->next = new ListNode(3);
    ptr = ptr->next;
    ptr->next = new ListNode(4);
    ptr = ptr->next;
    ptr->next = new ListNode(5);
    ptr = ptr->next;

    Solution2 s;
    s.removeNthFromEnd(head, 2);

    ptr = head;
    while (ptr) {
        cout << " -> " << ptr->val;
        ptr = ptr->next;
    }
    cout << endl;
}