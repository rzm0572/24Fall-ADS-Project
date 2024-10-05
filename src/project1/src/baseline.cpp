#include "BST.h"
#include <cstdio>

// Node structure for Binary Search Tree
struct Node {
    int key;
    int value;
    Node* left;
    Node* right;
    Node* parent;

    Node(int _key = 0, int _value = 0, Node* _left = nullptr, Node* _right = nullptr, Node* _parent = nullptr)
        : key(_key), value(_value), left(_left), right(_right), parent(_parent) {}
};

// Binary Search Tree Class
class BST {
public:
    Node* root;
    int size;

    BST() {
        root = nullptr;
        size = 0;
    }

    bool insert(int key, int value) {
        if (size == 0) {
            root = new Node(key, value);
            size++;
            return true;
        }

        Node* ins = new Node(key, value);
        Node* x = root;
        Node* parent = nullptr;

        while (x != nullptr) {
            parent = x;
            if (key < x->key)
                x = x->left;
            else if (key > x->key)
                x = x->right;
            else {
                // Duplicate keys not allowed
                delete ins;
                return false;
            }
        }

        ins->parent = parent;
        if (key < parent->key) {
            parent->left = ins;
        } else {
            parent->right = ins;
        }

        size++;
        return true;
    }

    bool remove(int key) {
        Node* node = searchNode(key);
        if (node == nullptr)
            return false;

        // Case 1: Node has no children
        if (node->left == nullptr && node->right == nullptr) {
            replaceNodeInParent(node, nullptr);
        }
        // Case 2: Node has one child
        else if (node->left == nullptr) {
            replaceNodeInParent(node, node->right);
        } else if (node->right == nullptr) {
            replaceNodeInParent(node, node->left);
        }
        // Case 3: Node has two children
        else {
            Node* successor = findMin(node->right);
            node->key = successor->key;
            node->value = successor->value;
            replaceNodeInParent(successor, successor->right);
        }

        delete node;
        size--;
        return true;
    }

    void output() {
        if (root == nullptr)
            printf("Empty tree\n");
        else {
            printf("Size: %d\n", size);
            dfs(root);
        }
    }

private:
    Node* searchNode(int key) {
        Node* x = root;
        while (x != nullptr) {
            if (key < x->key)
                x = x->left;
            else if (key > x->key)
                x = x->right;
            else
                return x;
        }
        return nullptr;
    }

    void replaceNodeInParent(Node* node, Node* newNode) {
        if (node->parent == nullptr) {
            root = newNode;
        } else {
            if (node == node->parent->left) {
                node->parent->left = newNode;
            } else {
                node->parent->right = newNode;
            }
        }
        if (newNode != nullptr) {
            newNode->parent = node->parent;
        }
    }

    Node* findMin(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    void dfs(Node* x) {
        if (x == nullptr) return;
        printf("%d: value = %d", x->key, x->value);
        if (x->left != nullptr)
            printf(", left = %d", x->left->key);
        if (x->right != nullptr)
            printf(", right = %d", x->right->key);
        if (x->parent != nullptr)
            printf(", parent = %d", x->parent->key);
        printf("\n");
        dfs(x->left);
        dfs(x->right);
    }
};

// Test function for BST
void TestBST(int n, Operation ops[]) {
    BST bst;
    for (int i = 0; i < n; i++) {
        switch (ops[i].optype) {
            case 0: {
                bst.insert(ops[i].key, ops[i].value);
                break;
            }
            case 1: {
                bst.remove(ops[i].key);
                break;
            }
        }
        // Uncomment to debug
        // printf("Operation %d: optype = %d, key = %d\n", i, ops[i].optype, ops[i].key);
        // bst.output();
        // printf("\n");
    }
}