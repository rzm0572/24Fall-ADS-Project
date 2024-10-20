#include <algorithm>
#include <cmath>
#include <cstdio>

#include "MinHeap.h"

int maxDegree(int n) {
    double cosi = (1 + sqrt(5.0)) / 2.0;
    return (int)floor(log((double)n) / log(cosi)) + 2;
}

template class FibonacciHeap<dist_t>;

template <class T>
void FibonacciHeap<T>::printHeap(int n) {
    printf("Heap: rootLen = %d, size = %d, minNode = %d\n", rootLen, MinHeap<T>::size, minNode == nullptr ? -1 : minNode->data.key);
    // dfs(minNode);
    for (int i = 0; i < n; i++) {
        TreeNode* x = Position[i];
        if (x == nullptr) {
            printf("data: (%d, null)\n", i);
        } else {
            printf("data: (%d, %d), deg: %d, marked: %d, parent: %d, child: %d, left: %d, right: %d\n", x->data.key, x->data.value, x->deg, x->marked, x->parent == nullptr ? -1 : x->parent->data.key, x->child == nullptr ? -1 : x->child->data.key, x->left == nullptr ? -1 : x->left->data.key, x->right == nullptr ? -1 : x->right->data.key);
        }
    }
    printf("\n");
}

template <class T>
void FibonacciHeap<T>::insertRootList(TreeNode* newNode) {
    if (minNode == nullptr) {
        newNode->left = newNode;
        newNode->right = newNode;
        minNode = newNode;
    } else {
        if (newNode->parent != nullptr) {
            if (newNode->parent->deg == 1) {
                newNode->parent->child = nullptr;
            } else {
                if (newNode->parent->child == newNode) {
                    newNode->parent->child = newNode->right;
                }
                newNode->left->right = newNode->right;
                newNode->right->left = newNode->left;
            }
            newNode->parent->deg--;
        }

        newNode->left = minNode->left;
        newNode->right = minNode;
        minNode->left->right = newNode;
        minNode->left = newNode;

        if (newNode->data.value < minNode->data.value)
            minNode = newNode;
    }
    newNode->parent = nullptr;
    rootLen++;
}

template <class T>
bool FibonacciHeap<T>::deleteRootList(TreeNode* deleteNode) {
    if (rootLen == 0) {
        return false;
    }

    if (rootLen == 1) {
        minNode = nullptr;
    } else {
        deleteNode->left->right = deleteNode->right;
        deleteNode->right->left = deleteNode->left;
        minNode = deleteNode->right;
    }

    rootLen--;
    return true;
}

template <class T>
typename FibonacciHeap<T>::TreeNode* FibonacciHeap<T>::heapLink(TreeNode* x, TreeNode* y) {
    if (x->data.value < y->data.value) {
        std::swap(x, y);
    }
    deleteRootList(x);
    x->parent = y;

    if (y->deg == 0) {
        y->child = x;
        x->left = x;
        x->right = x;
    } else {
        x->left = y->child;
        x->right = y->child->right;
        y->child->right->left = x;
        y->child->right = x;
    }
    y->deg++;
    x->marked = false;
    return y;
}

template <class T>
void FibonacciHeap<T>::consolidate() {
    int mxDeg = maxDegree(MinHeap<T>::size);
    TreeNode** A = new TreeNode*[mxDeg];
    std::fill(A, A + mxDeg, nullptr);

    TreeNode* root = minNode;
    int rootNum = rootLen;
    for (int i = 0; i < rootNum; i++) {
        TreeNode* nxtRoot = root->right;

        int curDeg = root->deg;
        TreeNode* curRoot = root;
        while (A[curDeg] != nullptr) {
            TreeNode* collideRoot = A[curDeg];
            A[curDeg] = nullptr;
            curRoot = heapLink(curRoot, collideRoot);
            curDeg++;
        }
        A[curDeg] = curRoot;

        // deleteRootList(root);

        root = nxtRoot;
    }

    minNode = nullptr;
    for (int i = 0; i < mxDeg; i++) {
        if (A[i] == nullptr) {
            continue;
        }
        // insertRootList(A[i]);
        if (minNode == nullptr || A[i]->data.value < minNode->data.value) {
            minNode = A[i];
        }
    }

    delete[] A;
}

template <class T>
void FibonacciHeap<T>::cut(TreeNode* x) {
    TreeNode* p = x->parent;
    if (p->deg == 1) {
        p->child = nullptr;
    } else {
        x->left->right = x->right;
        x->right->left = x->left;
        if (x->data.key == p->child->data.key) {
            p->child = x->right;
        }
    }
    insertRootList(x);
    x->marked = false;
}

template <class T>
void FibonacciHeap<T>::cascadingCut(TreeNode* x) {
    TreeNode* p = x->parent;
    if (p == nullptr) {
        return;
    }

    if (x->marked == false) {
        x->marked = true;
    } else {
        cut(x);
        cascadingCut(p);
    }
}

template <class T>
FibonacciHeap<T>::FibonacciHeap(int n) : MinHeap<T>(0) {
    // size = 0;
    rootLen = 0;
    minNode = nullptr;
    Position = new TreeNode*[n + 1];
}

template <class T>
FibonacciHeap<T>::~FibonacciHeap() {
    delete[] Position;
}

template <class T>
Pair<T> FibonacciHeap<T>::findMin() {
    return (MinHeap<T>::size > 0) ? minNode->data : Pair<T>();
}

template <class T>
bool FibonacciHeap<T>::insert(Pair<T> x) {
    TreeNode* newNode = new TreeNode(x);

    insertRootList(newNode);
    MinHeap<T>::size++;
    Position[x.key] = newNode;

    return true;
}

template <class T>
bool FibonacciHeap<T>::deleteMin() {
    TreeNode* z = minNode;
    if (z == nullptr) {
        return false;
    }

    TreeNode* c = z->child;
    int childNum = z->deg;
    for (int i = 0; i < childNum; i++) {
        TreeNode* nxtChild = c->right;
        insertRootList(c);
        c = nxtChild;
    }

    deleteRootList(z);
    Position[z->data.key] = nullptr;
    delete z;
    MinHeap<T>::size--;

    if (rootLen > 0) {
        consolidate();
    }
    return true;
}

template <class T>
bool FibonacciHeap<T>::decreaseKey(Pair<T> x) {
    TreeNode* node = Position[x.key];
    if (x.value > node->data.value) {
        return false;
    }

    node->data.value = x.value;
    TreeNode* p = node->parent;
    if (p != nullptr && p->data.value > node->data.value) {
        cut(node);
        cascadingCut(p);
    }

    if (node->data.value < minNode->data.value) {
        minNode = node;
    }

    return true;
}

template <class T>
bool FibonacciHeap<T>::checkExist(int key) {
    return Position[key] != nullptr;
}
