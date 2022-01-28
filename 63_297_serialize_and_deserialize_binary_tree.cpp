class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string out;
        stack<TreeNode*> s;
        //pre-order traversal
        s.push(root);
        while (s.size())
        {
            TreeNode* tmp = s.top();
            s.pop();
            if (tmp)
            {
                out += to_string(tmp->val);
                s.push(tmp->right);
                s.push(tmp->left);
            }
            else
            {
                out += "N";
            }
        }
        cout << out <<endl;
        return out;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data.size() == 0)
            return nullptr;
        if (!isdigit(data[0]))
        {
            return nullptr;
        }
        int idx = 0;
        int v = data[idx++] - '0';
        TreeNode* root = new TreeNode(v);
        stack<TreeNode*> s;
        s.push(root);

        while (s.size() && idx < data.size())
        {
            TreeNode* tmp = s.top();
            s.pop();
            char c = data[idx++];
            if (c - '0' >= 0 && c - '0' <= 9)
            {
                tmp->left = new TreeNode(c - '0');
                s.push(tmp->left);
            }
            c = data[idx++];
            if (c - '0' >= 0 && c - '0' <= 9)
            {
                tmp->right = new TreeNode(c - '0');
                s.push(tmp->right);
            }
        }
        return root;
    }
};
