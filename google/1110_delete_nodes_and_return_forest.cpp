#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    vector<TreeNode*> ans;

    TreeNode* delNodesInternal(TreeNode* root, vector<int>& to_delete) {
        if (!root)
            return nullptr;

        cout << "processing " << root->val << endl;

        TreeNode* left = root->left;
        TreeNode* right = root->right;

        auto it = find(to_delete.begin(), to_delete.end(), root->val);
        bool deleted = (it != to_delete.end());

        auto leftNode = delNodesInternal(left, to_delete);
        if (!leftNode)
        {
            cout << "cut " << root->val << " left\n";
            root->left = nullptr;
        }
        auto rightNode = delNodesInternal(right, to_delete);
        if (!rightNode)
        {
            cout << "cut " << root->val << " right\n";
            root->right = nullptr;
        }

        // how to determine if this is a new root?
        // if delete, then my children are answer
        if (deleted)
        {
            cout << "del " << *it << endl;

            if (left && leftNode)
            {
                cout << "ans add: " << left->val << endl;
                ans.push_back(left);
            }

            if (right && rightNode)
            {
                cout << "ans add: " << right->val << endl;
                ans.push_back(right);
            }
        }
        // if not, then children are not in answer
        else
        {
            // empty
        }

        return deleted ? nullptr : root;
    }
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        if (!root)
            return ans;

        auto node = delNodesInternal(root, to_delete);
        auto it = find(to_delete.begin(), to_delete.end(), root->val);
        bool deleted = (it != to_delete.end());
        if (deleted)
        {
            // no connection to cut
        }
        else
        {
            ans.push_back(root);
        }
        return ans;
    }

    // just recursive now
    // vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
    //     vector<TreeNode*> ans;
    //     if (!root)
    //     {
    //         return ans;
    //     }

    //     auto it = find(to_delete.begin(), to_delete.end(), root->val);
    //     if (it != to_delete.end())
    //     {
    //         TreeNode* left = root->left;
    //         root->left = nullptr;
    //         auto a1 = delNodes(left, to_delete);
    //         if (a1.size())
    //             ans.insert(ans.end(), a1.begin(), a1.end());
    //         TreeNode* right = root->right;
    //         root->right = nullptr;
    //         auto a2 = delNodes(right, to_delete);
    //         if (a2.size())
    //             ans.insert(ans.end(), a2.begin(), a2.end());
    //     }
    //     return ans;
    // }
    // queue<TreeNode*> mainQ; // store a root, must add to answer, but need to check child connection
    // queue<TreeNode*> subQ; // store just traversal node, must not add to answer
    // void process(TreeNode* node, vector<int>& to_delete)
    // {
    //     auto it = find(to_delete.begin(), to_delete.end(), node->val);
    //     if (it != to_delete.end())
    //     {
    //         // need to cut connection, and children add to mainQ
    //         to_delete.erase(it);
    //         if (node->left)
    //         {
    //             mainQ.push(node->left);
    //             node->left = nullptr;
    //         }
    //         if (node->right)
    //         {
    //             mainQ.push(node->right);
    //             node->right = nullptr;
    //         }
    //     }
    //     else
    //     {
    //         if (node->left)
    //             subQ.push(node->left);
    //         if (node->right)
    //             subQ.push(node->right);
    //     }
    // }
    // vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
    //     vector<TreeNode*> ans;
    //     if (!root)
    //         return ans;

    //     // process a possible ans node
    //     TreeNode* node = root;
    //     process(root, to_delete);

    //     while (subQ.size() || mainQ.size())
    //     {
    //         process();
    //     }
    // }


    // void check_before_push_children(queue<TreeNode*> q, TreeNode* node, vector<int>& to_delete)
    // {
    //     if (node->left)
    //     {
    //         auto it = find(to_delete.begin(), to_delete.end(), node->left->val);
    //         if (it != to_delete.end())
    //         {
    //             q.push(node->left);
    //             node->left = nullptr;
    //         }
    //     }

    //     if (node->right)
    //     {
    //         auto it = find(to_delete.begin(), to_delete.end(), node->right->val);
    //         if (it != to_delete.end())
    //         {
    //             q.push(node->right);
    //             node->right = nullptr;
    //         }
    //     }
    // }

    // vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
    //     // Input: root = [1,2,3,4,5,6,7], to_delete = [3,5]
    //     //          1
    //     //       2      3
    //     //     4   5  6   7
    //     // Output: [[1,2,null,4],[6],[7]]
    //     // either bfs or dfs
    //     // put 1 to mainQ
    //     // 1 ->
    //     // add 2,3 to subQ
    //     // -> 2
    //     // add 4,5 to subQ
    //     // -> 3
    //     // add 6,7 to mainQ
    //     // -> 4
    //     // -> 5, queue finish
    //     vector<TreeNode*> ans;
    //     queue<TreeNode*> mainQ; // store potential root, but we need to pop to check
    //     queue<TreeNode*> subQ; // store just traversal node, must not add to answer
    //     mainQ.push(root);
    //     while (mainQ.size() || subQ.size())
    //     {
    //         while (subQ.size())
    //         {
    //             TreeNode* node = subQ.back();
    //             subQ.pop();
    //             if (node == nullptr)
    //             {
    //                 continue;
    //             }
    //             auto it = find(to_delete.begin(), to_delete.end(), node->val);
    //             if (it != to_delete.end())
    //             {
    //                 to_delete.erase(it);
    //                 check_before_push_children(mainQ, node, to_delete);
    //             }
    //             else
    //             {
    //                 check_before_push_children(subQ, node, to_delete);
    //             }
    //         }

    //         // how many to process at once?
    //         while (mainQ.size())
    //         {
    //             TreeNode* node = mainQ.back();
    //             mainQ.pop();
    //             if (node == nullptr)
    //             {
    //                 continue;
    //             }
    //             // could be add if not deleted

    //             auto it = find(to_delete.begin(), to_delete.end(), node->val);
    //             if (it != to_delete.end())
    //             {
    //                 to_delete.erase(it);
    //                 check_before_push_children(mainQ, node, to_delete);
    //             }
    //             // no need to delete
    //             else
    //             {
    //                 ans.push_back(node);
    //                 check_before_push_children(subQ, node, to_delete);
    //             }
    //         }
    //     }
    //     return ans;
    // }
};