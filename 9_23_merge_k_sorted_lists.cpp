// 2/13/22 first try
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // build merge 2, and then divide and conquer logM
        if (lists.size() == 0)
        {
            return nullptr;
        }
        if (lists.size() == 1)
        {
            return lists[0];
        }
        if (lists.size() == 2)
        {
            return merge(lists[0], lists[1]);
        }
        return mergeRange(lists, 0, lists.size() - 1);
    }
                     
    ListNode* mergeRange(vector<ListNode*>& lists, int left, int right)
    {
        if (left == right)
        {
            return lists[left];
        }
        if (left + 1 == right)
        {
            merge(lists[left], lists[right]);
        }
        int mid = left + (right - left) / 2;
        return merge(mergeRange(lists, 0, mid), mergeRange(lists, mid + 1, lists.size() - 1));
    }
    
    ListNode* merge(ListNode* list1, ListNode* list2)
    {
        if (list1 == nullptr)
            return list2;
        if (list2 == nullptr)
            return list1;
        
        ListNode* res = nullptr;
        ListNode* ptr = nullptr;
        if (list1->val > list2->val)
        {
            // point to list2
            res = list2;
            ptr = res;
            list2 = list2->next;
        }
        else
        {
            // point to list1
            res = list1;
            ptr = res;
            list1 = list1->next;
        }
        
        while (list1 && list2)
        {
            if (list1->val > list2->val)
            {
                ptr->next = list2;
                list2 = list2->next;
            }
            else
            {
                ptr->next = list1;
                list1 = list1->next;
            }
        }
        if (list1 == nullptr && list2 != nullptr)
        {
            ptr->next = list2;
        }
        if (list1 != nullptr && list2 == nullptr)
        {
            ptr->next = list1;
        }
        return res;
    }
};

// after 3 fixes
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
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // build merge 2, and then divide and conquer logM
        if (lists.size() == 0)
        {
            return nullptr;
        }
        if (lists.size() == 1)
        {
            return lists[0];
        }
        if (lists.size() == 2)
        {
            return merge(lists[0], lists[1]);
        }
        return mergeRange(lists, 0, lists.size() - 1);
    }
                     
    ListNode* mergeRange(vector<ListNode*>& lists, int left, int right)
    {
        // cout << "left: " << left << " right: " << right << endl;
        if (left == right)
        {
            return lists[left];
        }
        if (left + 1 == right)
        {
            return merge(lists[left], lists[right]);
        }
        int mid = left + (right - left) / 2;
        return merge(mergeRange(lists, left, mid), mergeRange(lists, mid + 1, right));
    }
    
    ListNode* merge(ListNode* list1, ListNode* list2)
    {
        if (list1 == nullptr)
            return list2;
        if (list2 == nullptr)
            return list1;
        
        ListNode* res = nullptr;
        ListNode* ptr = nullptr;
        if (list1->val > list2->val)
        {
            // point to list2
            res = list2;
            ptr = res;
            list2 = list2->next;
        }
        else
        {
            // point to list1
            res = list1;
            ptr = res;
            list1 = list1->next;
        }
        
        while (list1 != nullptr && list2 != nullptr)
        {
            // cout << "1: " << list1->val;
            // cout << " 2: " << list2->val << endl;
            if (list1->val > list2->val)
            {
                ptr->next = list2;
                list2 = list2->next;
            }
            else
            {
                ptr->next = list1;
                list1 = list1->next;
            }
            ptr = ptr->next;
            cout << ptr->val << endl;
        }
        // cout << "finish\n";
        if (list1 == nullptr && list2 != nullptr)
        {
            ptr->next = list2;
        }
        if (list1 != nullptr && list2 == nullptr)
        {
            ptr->next = list1;
        }
        return res;
    }
};
