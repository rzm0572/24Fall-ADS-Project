#include "MinHeap.h"
#include <cstdio>

template class LeftistHeap<dist_pair>;

template<class T>
LeftistHeap<T>::LeftistHeap(int n) {
    size = 0;
    root = NULL;
    Position = (TreeNode**)malloc((n+1) * sizeof(TreeNode*));
    for(int i=0;i<=n;i++){
        Position[i] = NULL;
    }
    // printf("LeftistHeap created\n");
}

template<class T>
typename LeftistHeap<T>::TreeNode* LeftistHeap<T>::Merge(TreeNode* T1, TreeNode* T2) {
    if (T1 == NULL) {
        return T2;
    }
    if(T2==NULL){
        return T1;
    }
    if(T2->value<T1->value){
        TreeNode* temp = T1;
        T1 = T2;
        T2 = temp;
    }
    T1->right = Merge(T1->right, T2);
    T1->right->parent = T1;
    if(T1->left==NULL || T1->left->height < T1->right->height){
        TreeNode* temp = T1->left;
        T1->left = T1->right;
        T1->right = temp;
    }
    if(T1->right!=NULL){
        T1->height = T1->right->height + 1;
    }
    else{
        T1->height = 1;
    }
    return T1;
}
template<class T>
Pair<T> LeftistHeap<T>::findMin() {
    // TODO
    return root->value;
}

template<class T>
bool LeftistHeap<T>::insert(Pair<T> x) {
    if(checkExist(x.key)){
        return false;
    }
    TreeNode* temp = NewNode(x);
    Position[x.key] = temp;
    size++;
    root = Merge(root, temp);
    return true;
}

template<class T>
bool LeftistHeap<T>::deleteMin() {
    // TODO
    if(size==0){
        return false;
    }
    Position[root->value.key] = NULL;
    size--;
    root = Merge(root->left, root->right);
    return true;
}

template<class T>
bool LeftistHeap<T>::decreaseKey(Pair<T> x) {
    if(!checkExist(x.key)||Position[x.key]->value<x){
        return false;
    }
    Position[x.key]->value=x;
    TreeNode* temp = Position[x.key];
    while(temp->parent!=NULL && temp->value<temp->parent->value){
        Position[temp->parent->value.key] = temp;
        Position[temp->value.key] = temp->parent;
        
        Pair<T> temp_value = temp->parent->value;
        temp->parent->value = temp->value;
        temp->value = temp_value;
        temp = temp->parent;
    }


    return true;
}

template<class T>
int LeftistHeap<T>::getSize() {
    // TODO
    return size;
}

template<class T>
typename LeftistHeap<T>::TreeNode* LeftistHeap<T>::NewNode(Pair<T> x){
    TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
    temp->value = x;
    temp->left = NULL;
    temp->right = NULL;
    temp->parent = NULL;
    temp->height = 1;
    return temp;
}

template <class T>
bool LeftistHeap<T>::checkExist(int key) {
    return Position[key] != NULL;
}