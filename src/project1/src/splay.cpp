#include <cstdio>
#include "BST.h"

// Node structure
// pos: If this node is the root of the tree, pos = 0; otherwise, pos = 1 if it is the left child of its parent, pos = -1 if it is the right child of its parent.
struct Node {
    int key;
    int value;
    Node* left;
    Node* right;
    Node* parent;
    int pos;

    Node(int _key = 0, int _value = 0, Node* _left = nullptr, Node* _right = nullptr, Node* _parent = nullptr, int _pos = 0) : key(_key), value(_value), left(_left), right(_right), parent(_parent), pos(_pos) {}
};
struct SplayTree {
    Node* root;
    int size;

    SplayTree() {
        root = nullptr;
        size = 0;
    }

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

    void splay(Node* x) {
        while (x != nullptr && x != root) {
            Node* p = x->parent;
            
            if (p == root) {
                if (x->pos == 1)
                    rotateRight(p);
                else if (x->pos == -1)
                    rotateLeft(p);
            } else {
                Node* g = p->parent;
                if (p->pos == 1 && x->pos == 1) {
                    rotateRight(g);
                    rotateRight(p);
                }
                else if (p->pos == -1 && x->pos == -1) {
                    rotateLeft(g);
                    rotateLeft(p);
                }
                else if (p->pos == 1 && x->pos == -1) {
                    rotateLeft(p);
                    rotateRight(g);
                }
                else if (p->pos == -1 && x->pos == 1) {
                    rotateRight(p);
                    rotateLeft(g);
                }
            }
        }
    }

    bool select(int key) {
        Node* x = root;
        while (x != nullptr) {
            if (key == x->key)
                break;
            else if (key < x->key)
                x = x->left;
            else if (key > x->key)
                x = x->right;
        }
        if (x != nullptr)
            splay(x);
        return x != nullptr;
    }

    bool insert(int key, int value) {
        if (size == 0) {
            root = new Node(key, value);
            size++;
            return true;
        }

        Node* ins = new Node(key, value);
        Node* x = root;

        while (x != nullptr) {
            if (key < x->key) {
                if (x->left == nullptr) {
                    x->left = ins;
                    ins->parent = x;
                    ins->pos = 1;
                    size++;
                    break;
                } else {
                    x = x->left;
                }
            } else {
                if (x->right == nullptr) {
                    x->right = ins;
                    ins->parent = x;
                    ins->pos = -1;
                    size++;
                    break;
                } else {
                    x = x->right;
                }
            }
        }

        if (x != nullptr) {
            splay(ins);
        }

        return x != nullptr;
    }

    bool remove(int key) {
        if (size == 0) return false;
        if (size == 1) {
            size--;
            delete root;
            root = nullptr;
            return true;
        }

        if (!select(key)) return false;

        Node* x = root;

        if (x->left == nullptr) {
            root = x->right;
            root->parent = x->parent;
            root->pos = 0;
            delete x;
            size--;
            return true;
        }
        if (x->right == nullptr) {
            root = x->left;
            root->parent = x->parent;
            root->pos = 0;
            delete x;
            size--;
            return true;
        }

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
