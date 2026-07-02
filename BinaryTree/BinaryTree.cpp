#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

class Node
{
public:
    int data;
    Node *left;
    Node *right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

static int idx = -1;

Node *buildtree(vector<int> &preOrder)
{
    idx++;
    if (preOrder[idx] == -1)
    {
        return nullptr;
    }

    Node *root = new Node(preOrder[idx]);
    root->left = buildtree(preOrder);
    root->right = buildtree(preOrder);

    return root;
}

void preorder(Node *root)
{
    if (root == nullptr)
    {
        return;
    }
    cout << root->data << "\t";
    preorder(root->left);
    preorder(root->right);
}

void inorder(Node *root)
{
    if (root == nullptr)
    {
        return;
    }
    inorder(root->left);
    cout << root->data << "\t";
    inorder(root->right);
}

void postOrder(Node *root)
{
    if (root == nullptr)
    {
        return;
    }
    postOrder(root->left);
    postOrder(root->right);
    cout << root->data << " ";
}

void levelorder(Node *root)
{
    queue<Node *> q;
    q.push(root);
    q.push(nullptr);
    while (!q.empty())
    {
        Node *temp = q.front();
        q.pop();
        if (temp == nullptr)
        {
            if (!q.empty())
            {
                cout << "\n";
                q.push(nullptr);
                continue;
            }
            else
            {
                break;
            }
        }

        cout << temp->data << " ";
        if (temp->left)
            q.push(temp->left);

        if (temp->right)
            q.push(temp->right);
    }
}

int height(Node *root)
{
    if (root == nullptr)
    {
        return 0;
    }

    int left = height(root->left);
    int right = height(root->right);

    return max(left, right) + 1;
}
int count(Node *root)
{
    if (root == nullptr)
    {
        return 0;
    }

    int left = count(root->left);
    int right = count(root->right);

    return left + right + 1;
}
int diameter(Node *root)
{
    if (root == nullptr)
    {
        return 0;
    }
    int leftDia = diameter(root->left);
    int rightDia = diameter(root->right);
    int currDia = height(root->left) + height(root->right);

    return max(currDia, max(rightDia, leftDia));
}

int sum(Node *root)
{
    if (root == nullptr)
    {
        return 0;
    }

    int left = sum(root->left);
    int right = sum(root->right);

    return left + right + root->data;
}

void topView(Node *root)
{
    queue<pair<Node *, int>> q;
    map<int, int> m;
    q.push({root, 0});

    while (!q.empty())
    {
        Node *curr = q.front().first;
        int currHd = q.front().second;

        q.pop();
        if (m.find(currHd) == m.end())
        {
            m[currHd] = curr->data;
        }
        if (curr->left)
        {
            q.push({curr->left, currHd - 1});
        }
        if (curr->right)
        {
            q.push({curr->right, currHd + 1});
        }
    }

    for (auto it : m)
    {
        cout << it.second << " ";
    }
    cout << endl;
}

void bottomView(Node *root)
{
    queue<pair<Node *, int>> q;
    map<int, int> m;
    q.push({root, 0});

    while (!q.empty())
    {
        Node *curr = q.front().first;
        int currHd = q.front().second;

        q.pop();
        m[currHd] = curr->data;
        if (curr->left)
        {
            q.push({curr->left, currHd - 1});
        }
        if (curr->right)
        {
            q.push({curr->right, currHd + 1});
        }
    }

    for (auto it : m)
    {
        cout << it.second << " ";
    }
    cout << endl;
}

void kthLevelNodes(Node *root, int k)
{
    if (root == nullptr || k < 1)
    {
        return;
    }
    if (k == 1)
    {
        cout << root->data << " \t";
        return;
    }
    kthLevelNodes(root->left, k - 1);
    kthLevelNodes(root->right, k - 1);
}

int sumTree(Node *root)
{
    if (root == nullptr)
    {
        return 0;
    }
    root->data = root->data + sumTree(root->left) + sumTree(root->right);
    return root->data;
}

int main()
{

    vector<int> preOrder{1, 2, 6, -1, -1, -1, 3, 4, -1, -1, 5, -1, 7, -1, -1};
    Node *root = buildtree(preOrder);
    sumTree(root);
    preorder(root);
    cout << '\n';
    inorder(root);
    return 0;
}
