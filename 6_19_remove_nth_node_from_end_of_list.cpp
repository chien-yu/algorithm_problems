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

    Solution s;
    s.removeNthFromEnd(head, 2);

    ptr = head;
    while (ptr) {
        cout << " -> " << ptr->val;
        ptr = ptr->next;
    }
    cout << endl;
}