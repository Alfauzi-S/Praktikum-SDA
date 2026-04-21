#include <iostream>
#include <queue>
using namespace std;
// Struktur Node untuk Binary Tree
struct Node
{
    int data;
    Node *left;
    Node *right;
    Node(int val)
    {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};
// Operasi Binary Search Tree (BST)
// Fungsi insert
Node *insert(Node *root, int val)
{
    if (root == nullptr)
    {
        return new Node(val);
    }
    if (val < root->data)
    {
        root->left = insert(root->left, val);
    }
    else if (val > root->data)
    {
        root->right = insert(root->right, val);
    }
    return root;
}
// Fungsi search
Node *search(Node *root, int val)
{
    if (root == nullptr || root->data == val)
    {
        return root;
    }
    if (val < root->data)
    {
        return search(root->left, val);
    }
    return search(root->right, val);
}
// Cari node dengan nilai minimum
Node *findMinValueNode(Node *node)
{
    Node *current = node;
    while (current != nullptr && current->left != nullptr)
    {
        current = current->left;
    }
    return current;
}
// Fungsi delete
Node *deleteNode(Node *root, int val)
{
    if (root == nullptr)
    {
        return root;
    }
    if (val < root->data)
    {
        root->left = deleteNode(root->left, val);
    }
    else if (val > root->data)
    {
        root->right = deleteNode(root->right, val);
    }
    else
    {
        // Node dengan satu atau nol anak
        if (root->left == nullptr)
        {
            Node *temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr)
        {
            Node *temp = root->left;
            delete root;
            return temp;
        }
        // Node dengan dua anak
        Node *temp = findMinValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}
// Traversal In-Order
void inorderTraversal(Node *root)
{
    if (root == nullptr)
        return;
    inorderTraversal(root->left);
    cout << root->data << " ";
    inorderTraversal(root->right);
}
// Traversal Pre-Order
void preorderTraversal(Node *root)
{
    if (root == nullptr)
        return;
    cout << root->data << " ";
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}
// Traversal Post-Order
void postorderTraversal(Node *root)
{
    if (root == nullptr)
        return;

    postorderTraversal(root->left);
    postorderTraversal(root->right);
    cout << root->data << " ";
}
// Traversal Level-Order (BFS)
void bfs(Node *root)
{
    if (root == nullptr)
        return;
    queue<Node *> q;
    q.push(root);
    while (!q.empty())
    {
        Node *current = q.front();
        q.pop();
        cout << current->data << " ";
        if (current->left != nullptr)
            q.push(current->left);
        if (current->right != nullptr)
            q.push(current->right);
    }
}
// Fungsi utama
int main()
{
    Node *root = nullptr;
    cout << "Membangun BST dengan nilai: 50, 30, 70, 20, 40, 60, 80\n";
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 70);
    insert(root, 20);
    insert(root, 40);
    insert(root, 60);
    insert(root, 80);

    cout << "\nIn-Order : ";
    inorderTraversal(root);
    cout << "\nPre-Order : ";
    preorderTraversal(root);
    cout << "\nPost-Order : ";
    postorderTraversal(root);
    cout << "\nLevel-Order: ";
    bfs(root);
    cout << "\n\nPencarian nilai 40: ";
    cout << (search(root, 40) != nullptr ? "Ditemukan" : "Tidakditemukan");
    cout << "\nPencarian nilai 99: ";
    cout << (search(root, 99) != nullptr ? "Ditemukan" : "Tidakditemukan");
    cout << "\n\nHapus node 20\n";
    root = deleteNode(root, 20);
    inorderTraversal(root);
    cout << "\n\nHapus node 30\n";
    root = deleteNode(root, 30);
    inorderTraversal(root);
    cout << "\n\nHapus node 50\n";
    root = deleteNode(root, 50);
    inorderTraversal(root);
return 0;
}