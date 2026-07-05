#include <iostream>
using namespace std;

class TreeNode
{

public:
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int val) : val(val), left(nullptr), right(nullptr) {};
};
TreeNode *insert(TreeNode *root, int val)
{
    if (root == nullptr)
        return new TreeNode(val);
    if (val <= root->val)
    {
        root->left = insert(root->left, val);
    }
    else
    {
        root->right = insert(root->right, val);
    }
    return root;
}
void inorder(TreeNode *root)
{
    if (root == nullptr)
    {
        return;
    }
    inorder(root->left);
    cout << root->val << "\t";
    inorder(root->right);
}

TreeNode *buildtree(vector<int> arr)
{
    TreeNode *root = nullptr;
    for (int num : arr)
    {
        root = insert(root, num);
    }
    return root;
}

TreeNode *searchBst(TreeNode *root, int val)
{
    if (root == nullptr)
        return root;

    if (val == root->val)
    {
        return root;
    }
    else if (val < root->val)
    {
        return searchBst(root->left, val);
    }
    else
    {
        return searchBst(root->right, val);
    }
}

TreeNode *getIS(TreeNode *root)
{
    TreeNode *node = root;
    while (node->left != nullptr)
    {
        node = node->left;
    }
    return node;
}

TreeNode *deleteNode(TreeNode *root, int val)
{
    if (root == nullptr)
    {
        return nullptr;
    }
    if (val < root->val)
    {
        root->left = deleteNode(root->left, val);
    }
    else if (val > root->val)
    {
        root->right = deleteNode(root->right, val);
    }
    else if (root->val == val)
    {
        if (root->left == nullptr)
        {
            TreeNode *temp = root->right;
            delete (root);
            return temp;
        }
        else if (root->right == nullptr)
        {
            TreeNode *temp = root->left;
            delete (root);
            return temp;
        }
        else
        {
            TreeNode *inorderSuccessor = getIS(root->right);
            root->val = inorderSuccessor->val;
            root->right = deleteNode(root->right, inorderSuccessor->val);
        }
    }
    return root;
}

int main()
{
    TreeNode *root = buildtree({3, 5, 1, 2, 4, 7});
    inorder(root);
    TreeNode *temp = searchBst(root, 7);
    cout << "\n"
         << temp->val << "\n";
    temp = searchBst(root, 8);
    if (temp == nullptr)
    {
        cout << "not found\n";
    }
    root = deleteNode(root, 3);
    inorder(root);
    root = deleteNode(root, 4);
    inorder(root);
    return 0;
}
