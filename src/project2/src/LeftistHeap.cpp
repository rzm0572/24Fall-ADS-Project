#include <cstdio>

#include "MinHeap.h"

template class LeftistHeap<dist_t>;

/*
初始化左式堆
n: 堆的大小
新建一个空的数组 Position，大小为 n+1，Position[i] 表示指向键值为 i 的结点的指针，初始值为 nullptr
*/

template <class T>
LeftistHeap<T>::LeftistHeap(int n) {
    size = 0;
    root = nullptr;
    Position = new TreeNode*[n + 1];
    for (int i = 0; i <= n; i++) {
        Position[i] = nullptr;
    }
    // printf("LeftistHeap created\n");
}

template <class T>
LeftistHeap<T>::~LeftistHeap() {
    delete[] Position;
}

/*
合并两棵左式堆
参数：
    T1: 左式堆 1 的根的指针
    T2: 左式堆 2 的根的指针
返回值：
    合并后的左式堆根的指针
*/
template <class T>
typename LeftistHeap<T>::TreeNode* LeftistHeap<T>::Merge(TreeNode* T1, TreeNode* T2) {
    if (T1 == nullptr) {  // T1 为空，返回 T2
        return T2;
    }
    if (T2 == nullptr) {  // T2 为空，返回 T1
        return T1;
    }
    if (T2->value < T1->value) {  // 确保 T1 的根值小于 T2 的根值
        TreeNode* temp = T1;      // 否则交换 T1 和 T2
        T1 = T2;
        T2 = temp;
    }
    T1->right = Merge(T1->right, T2);                                   // 合并 T1 的右子树和 T2
    T1->right->parent = T1;                                             // 更新 T1 的右子树的父节点为 T1
    if (T1->left == nullptr || T1->left->height < T1->right->height) {  // 确保 T1 的左子树高度大于 T1 的右子树高度
        TreeNode* temp = T1->left;                                      // 否则交换 T1 的左子树和右子树
        T1->left = T1->right;
        T1->right = temp;
    }
    if (T1->right != nullptr) {              // 更新 T1 的高度
        T1->height = T1->right->height + 1;  // 如果 T1 的右子树不为空，则 T1 的高度为 T1 的右子树高度加 1
    } else {
        T1->height = 1;  // 否则 T1 的高度为 1
    }
    return T1;
}
/*
查找最小值
返回值：
    最小值的（键值，距离）对
*/

template <class T>
Pair<T> LeftistHeap<T>::findMin() {
    // TODO
    return root->value;  // 返回根节点的值
}
/*
插入一个元素
参数：
    x: 待插入的元素
返回值：
    插入成功返回 true，如果元素存在则返回 false
*/
template <class T>
bool LeftistHeap<T>::insert(Pair<T> x) {
    if (checkExist(x.key)) {  // 如果元素存在，则返回 false
        return false;
    }
    TreeNode* temp = NewNode(x);  // 新建一个结点
    Position[x.key] = temp;
    size++;
    root = Merge(root, temp);  // 将节点作为一个左式堆合并
    return true;
}

/*
删除最小元素
返回值：
    删除成功返回 true，否则返回 false
*/

template <class T>
bool LeftistHeap<T>::deleteMin() {
    // TODO
    if (size == 0) {  // 如果堆为空，则返回 false
        return false;
    }
    Position[root->value.key] = nullptr;    // 将根节点的位置置空
    size--;                                 // 减少堆的大小
    root = Merge(root->left, root->right);  // 合并根节点的左右子树，更新根节点的指针
    return true;
}
/*
修改节点的大小
参数：
    x: 待修改的元素
返回值：
    修改成功返回 true，否则返回 false
*/
template <class T>
bool LeftistHeap<T>::decreaseKey(Pair<T> x) {
    if (!checkExist(x.key) || Position[x.key]->value < x) {  // 如果元素不存在或待修改的元素小于当前元素，则返回 false
        return false;
    }
    Position[x.key]->value = x;                                             // 修改元素的值
    TreeNode* temp = Position[x.key];                                       // 指向待修改元素的指针
    while (temp->parent != nullptr && temp->value < temp->parent->value) {  // 向上交换元素，直到父节点的值小于子节点的值
        Position[temp->parent->value.key] = temp;                           // 更新父节点的位置
        Position[temp->value.key] = temp->parent;                           // 更新子节点的位置

        Pair<T> temp_value = temp->parent->value;  // 交换父节点和子节点的值
        temp->parent->value = temp->value;
        temp->value = temp_value;
        temp = temp->parent;
    }

    return true;
}

/*
获得堆的大小
*/

template <class T>
int LeftistHeap<T>::getSize() {
    return size;
}
/*
创建一个新的结点
参数：
    x: 待插入的元素
返回值：
    新建的结点的指针
*/
template <class T>
typename LeftistHeap<T>::TreeNode* LeftistHeap<T>::NewNode(Pair<T> x) {
    TreeNode* temp = new TreeNode();
    temp->value = x;
    temp->left = nullptr;
    temp->right = nullptr;
    temp->parent = nullptr;
    temp->height = 1;
    return temp;
}
/*
判断元素是否存在
参数：
    key: 待判断的元素的键值
返回值：
    存在返回 true，否则返回 false
*/
template <class T>
bool LeftistHeap<T>::checkExist(int key) {
    return Position[key] != nullptr;
}