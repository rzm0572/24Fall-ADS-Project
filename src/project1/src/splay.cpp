#include <cstdio>
#include "BST.h"

// Node structure
// key: The key of the node.
// value: The value of the node.
// left: The left child of the node.
// right: The right child of the node.
// parent: The parent of the node.
// pos: If this node is the root of the tree, pos = 0; otherwise, pos = 1 if it is the left child of its parent, pos = -1 if it is the right child of its parent.
struct Node {
    int key;
    int value;
    Node* left;
    Node* right;
    Node* parent;
    int pos;

    // Constructor
    Node(int _key = 0, int _value = 0, Node* _left = nullptr, Node* _right = nullptr, Node* _parent = nullptr, int _pos = 0) : key(_key), value(_value), left(_left), right(_right), parent(_parent), pos(_pos) {}
};

// Splay tree structure
// root: The root of the tree.
// size: The number of nodes in the tree.
struct SplayTree {
    Node* root;
    int size;

    // Constructor
    SplayTree() {
        root = nullptr;
        size = 0;
    }

    // Left rotation on the right child of p
    void rotateLeft(Node* p) {
        if (p == nullptr || p->right == nullptr) return;
        Node *x = p->right;
        if (p->pos == 1) {
            p->parent->left = x;
        }
        else if (p->pos == -1) {
            p->parent->right = x;
        }
        else {
            root = x;
        }

        if (x->left != nullptr) {
            x->left->pos = -1;
            x->left->parent = p;
        }
        p->right = x->left;
        x->left = p;
        x->parent = p->parent;
        p->parent = x;

        x->pos = p->pos;
        p->pos = 1;
    }

    // Right rotation on the left child of p
    void rotateRight(Node* p) {
        if (p == nullptr || p->left == nullptr) return;
        Node *x = p->left;
        if (p->pos == 1) {
            p->parent->left = x;
        } else if (p->pos == -1) {
            p->parent->right = x;
        } else {
            root = x;
        }

        if (x->right != nullptr) {
            x->right->pos = 1;
            x->right->parent = p;
        }
        p->left = x->right;
        x->right = p;
        x->parent = p->parent;
        p->parent = x;
        x->pos = p->pos;
        p->pos = -1;
    }

    // Splay the node x to the root
    void splay(Node* x) {
        while (x != nullptr && x != root) {
            Node* p = x->parent;
            
            if (p == root) {
                // zig case
                if (x->pos == 1)
                    rotateRight(p);
                else if (x->pos == -1)
                    rotateLeft(p);
            } else {
                Node* g = p->parent;
                if (p->pos == 1 && x->pos == 1) {
                    // zig-zig case
                    rotateRight(g);
                    rotateRight(p);
                }
                else if (p->pos == -1 && x->pos == -1) {
                    // zig-zig case
                    rotateLeft(g);
                    rotateLeft(p);
                }
                else if (p->pos == 1 && x->pos == -1) {
                    // zig-zag case
                    rotateLeft(p);
                    rotateRight(g);
                }
                else if (p->pos == -1 && x->pos == 1) {
                    // zig-zag case
                    rotateRight(p);
                    rotateLeft(g);
                }
            }
        }
    }

    // Find the node with the given key
    bool select(int key) {
        Node* x = root;
        // Same as search operation in standard BST
        while (x != nullptr) {
            if (key == x->key)
                break;
            else if (key < x->key)
                x = x->left;
            else if (key > x->key)
                x = x->right;
        }
        // If found, splay the node to the root
        if (x != nullptr)
            splay(x);
        
        // Return true if found, false otherwise
        return x != nullptr;
    }

    // Insert a new node with the given key and value
    bool insert(int key, int value) {
        // If the tree is empty, create a new node as the root
        if (size == 0) {
            root = new Node(key, value);
            size++;
            return true;
        }

        // Create a new node with the given key and value
        Node* ins = new Node(key, value);
        Node* x = root;

        // Same as insert operation in standard BST
        while (x != nullptr) {
            if (key < x->key) {
                // If the key is smaller than the current node's key, insert it to the left child
                if (x->left == nullptr) {
                    // If the left child is empty, insert the new node to the left child
                    x->left = ins;
                    ins->parent = x;
                    ins->pos = 1;
                    size++;
                    break;
                } else {
                    // If the left child is not empty, move to the left child
                    x = x->left;
                }
            } else {
                // If the key is larger than or equal to the current node's key, insert it to the right child
                if (x->right == nullptr) {
                    // If the right child is empty, insert the new node to the right child
                    x->right = ins;
                    ins->parent = x;
                    ins->pos = -1;
                    size++;
                    break;
                } else {
                    // If the right child is not empty, move to the right child
                    x = x->right;
                }
            }
        }

        // Splay the new node to the root
        if (x != nullptr) {
            splay(ins);
        }

        // Return true if inserted, false otherwise
        return x != nullptr;
    }

    // Remove the node with the given key
    bool remove(int key) {
        // If the tree is empty, return false
        if (size == 0) {
            return false;
        }
        // If the tree has only one node, remove it and set the root to nullptr
        if (size == 1) {
            if (key != root->key) {
                return false;
            }
            size--;
            delete root;
            root = nullptr;
            return true;
        }

        // Select the node to be removed with the given key
        // If the key is found, splay the node to be removed to the root
        // If the key is not found, return false
        if (!select(key)) {
            return false;
        }

        Node* x = root;

        // If x has no left child, replace it with its right child
        if (x->left == nullptr) {
            root = x->right;
            root->parent = x->parent;
            root->pos = 0;
            delete x;
            size--;
            return true;
        }
        // If x has no right child, replace it with its left child
        if (x->right == nullptr) {
            root = x->left;
            root->parent = x->parent;
            root->pos = 0;
            delete x;
            size--;
            return true;
        }

        // If x has two children, replace it with its successor (the biggest node in the left subtree)
        x = root->left;
        while (x->right != nullptr)
            x = x->right;
        x->right = root->right;
        root->right->parent = x;
        root->right->pos = 1;
        x->pos = 0;
        delete root;
        root = x;
        size--;
        return true;
    }

    // Output the tree in inorder
    void output() {
        if (root == nullptr)
            printf("Empty tree\n");
        else {
            printf("Size: %d\n", size);
            dfs(root);
        }
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

// Test the efficiency of the splay tree
void TestBST(int n, Operation ops[]) {
    SplayTree bst;
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
        // printf("Operation %d: optype = %d, key = %d\n", i, ops[i].optype, ops[i].key);
        // bst.output();
        // printf("\n");
    }
}
