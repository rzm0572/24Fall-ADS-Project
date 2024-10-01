# Project 1: Binary Search Trees

先在这个文档里写，到时候我再用 $\LaTeX$ 改写一下.

## Introduction

TODO

## Algorithm Specification
#### AVL树部分报告
##### AVL树插入和删除的实现
###### 声明
```c++
// avltree.h
#ifndef AVLTREE_H
#define AVLTREE_H

#include <stdio.h>
#include <stdlib.h>
void swap(int *x,int *y);
int max(int x,int y);
//定义节点结构
struct Node{
    int data;//data of node
    int h_left;//height of left subtree
    int h_right;//height of right subtree
    // int hei;//height of node
    int det;//balance factor equal to h_left - h_right
    Node* left;//left child
    Node* right;//right child
    Node* pa;//parent node
};
//create Node
Node * createNode(int data);
//renew height and balance factor of node
void Refresh(Node* node);
//class AVL
struct AVL{
    Node* root;
    //init AVL
    void init();
    //left rotate
    void twistL(Node *node);
    //right rotate
    void twistR(Node *node);
    //rebalance
    void balance(Node *temp);
    //insert key x into AVL
    void ins(int x);
    //search key x in AVL, return node if found, else return NULL
    Node * Find(int x);
    //remove node temp from AVL
    void remove_Node(Node* temp);
    //delete key x from AVL, return 1 if success, else return 0
    int del(int x);
};
//check if AVL is balanced return the height of the subtree and res is whether the AVL is balanced, 1 is balannced 0 is not balanced
int checkdepth(Node* node,int *res);
//check if AVL is in order, return 1 if in order, else return 0
int checkorder(Node* node,int List[],int *cnt);
//print AVL node by node
void printtree(Node* node);
#endif
```
使用`<类名称>.ins(<键值>);`插入键值，使用`<类名称>.del(<键值>);`删除键值，使用`<类名称>.Find(<键值>);`查找键值，返回节点指针，如果不存在返回NULL。
###### 左旋的实现
将右子树的左子树作为原来子树的根的右子树，将右子树作为新的根的右子树，将当前节点作为新的根，原先根作为左儿子，并更新父节点的子节点指针。
```c++
void AVL::twistL(Node* node){
    Node* temp = node->right;
    //confirm the right child of node is not null
    if(temp!=NULL){
        node->h_right = temp->h_left;
        temp->h_left = max(node->h_left,node->h_right)+1;
        //update balance factor of node and temp
        if(node->pa){//node is not root
            if(node->pa->left==node){//change the parent's child to temp
                node->pa->left = temp;
            }
            else{
                node->pa->right = temp;
            }   
        }   
        else{
            root = temp;
        }     
        temp->pa = node->pa;
        node->pa = temp;//change the parent as the left child of temp
        node->right = temp->left;//change the right child of node to the left child of temp
        if(temp->left){
            temp->left->pa=node;
        }
        
        temp->left = node;
        node->det = node->h_left - node->h_right;
        temp->det = temp->h_left - temp->h_right;
    } 
}
```
###### 右旋的实现
将左子树的右子树作为原来子树的根的左子树，将左子树作为新的根的左子树，将当前节点作为新的根，原先根作为右儿子，并更新父节点的子节点指针。
```c++
void AVL::twistR(Node* node){//Right rotation
    Node* temp = node->left;//left child
    //confirm the left child of node is not null
    if(temp!=NULL){
        node->h_left = temp->h_right;
        temp->h_right=max(node->h_left,node->h_right)+1;
        if(node->pa){
            if(node->pa->left==node){
                node->pa->left = temp;
            }
            else{
                node->pa->right = temp;
            }
        }
        else{
            root = temp;
        }
        temp->pa = node->pa;
        node->pa = temp;
        node->left = temp->right;
        if(temp->right){
            temp->right->pa=node;
        }
        
        temp->right = node;
        node->det = node->h_left - node->h_right;
        temp->det = temp->h_left - temp->h_right;
    } 
}
```
###### 平衡操作的实现
平衡操作是指当某节点的高度或平衡因子发生变化时，需要对其父节点及祖先节点进行调整，以保持树的平衡性。
若因为右儿子的右儿子过高导致的不平衡，则左旋。若因为左儿子的左儿子过高导致的不平衡，则右旋后左旋。若因为左儿子的右儿子过高导致的不平衡，则右旋。若因为右儿子的左儿子过高导致的不平衡，则左旋后右旋。
```c++
void AVL::balance(Node *temp){
    while(temp){//update the height and balance factor of all nodes in the path from root to temp
        // printf(" %d\n",temp->data);
        Refresh(temp);//update the height and balance factor of temp
        // temp->det = temp->h_left - temp->h_right;
        if(temp->det==2){//if the left subtree is too high
            if(temp->left->det>=0){//if the left subtree of the left subtree is too high
                twistR(temp);
            }
            else{
                twistL(temp->left);//if the left subtree of the left subtree is not too high, perform a left rotation on the left subtree of the left subtree
                twistR(temp);
            }
        }
        if(temp->det==-2){//if the right subtree is too high
            if(temp->right->det<=0){//if the right subtree of the right subtree is too high
                twistL(temp);
            }
            else{//if the right subtree of the right subtree is not too high, perform a right rotation on the right subtree of the right subtree, and then a left rotation on the node
                twistR(temp->right);
                twistL(temp);
            }
        }
        temp = temp->pa;
    }
}
```
###### 插入节点的实现
若插入的节点为根节点，则直接创建该节点为根节点；
若插入的节点不为根节点，则从根节点开始，若插入的节点的键值小于当前节点的键值，则移动到当前节点的左子树；若插入的节点的键值大于等于当前节点的键值，则移动到当前节点的右子树；
当移动到叶子节点时，则创建该节点为叶子节点；
当移动到非叶子节点时，则更新该节点的高度和平衡因子；
当移动到某节点时，若该节点的平衡因子大于1或小于-1，则进行旋转操作，直到该节点的平衡因子恢复正常；
```c++
void AVL::ins(int x) {
    Node* newNode = createNode(x);
    Node* temp = root;
    // printf(" %d\n",root==NULL);
    if(root==NULL){//if the tree is empty, create a new node as the root
        root = newNode;
        // printf("!!!\n");
        return;
    }
    while(1){
        // printf(" %d\n",temp->data);
        if(x<temp->data){//if the data is less than the current node's data
            if(temp->left==NULL){//if the left child of the current node is NULL, create a new node as the left child of the current node
                temp->left = newNode;
                temp->h_left ++;
                temp->det = temp->h_left - temp->h_right;
                newNode->pa = temp;
                break;
            }
            temp = temp->left;//if the left child of the current node is not NULL, move to the left child of the current node
        }
        else{//if the data is greater than or equal to the current node's data
            if(temp->right==NULL){//if the right child of the current node is NULL, create a new node as the right child of the current node
                temp->right = newNode;
                temp->h_right ++;
                temp->det = temp->h_left - temp->h_right;
                newNode->pa = temp;
                break;
            }
            temp = temp->right;//if the right child of the current node is not NULL, move to the right child of the current node
        }
    }
    balance(temp);
}

```
###### 查找节点的实现
从根节点开始，若查找的节点的键值小于当前节点的键值，则移动到当前节点的左子树；若查找的节点的键值大于等于当前节点的键值，则移动到当前节点的右子树；
若查找的节点的键值等于当前节点的键值，则返回当前节点；
```c++
Node * AVL::Find(int x){
    Node* temp = root;
    while(temp!=NULL){//search the node with the given data
        if(temp->data==x){//if the data is found, return the node
            return temp;
        }
        else if(x<temp->data){//if the data is less than the current node's data, move to the left child of the current node
            temp = temp->left;
        }
        else{//if the data is greater than or equal to the current node's data, move to the right child of the current node
            temp = temp->right;
        }
    }
    return NULL;
} 
```
###### 删除单节点
查找节点后，若该节点为叶子节点或者只有右子树，则直接删除该节点；
若该节点有左子树，则用左子树的最大节点替换该节点，并删除该节点；
从该节点到根节点，若该节点的平衡因子大于1或小于-1，则进行旋转操作，直到该节点的平衡因子恢复正常；
```c++
void AVL::remove_Node(Node* temp){
    if(temp->right==NULL){//if the node has no right child, replace the node with its left child
        if(temp->pa){
            if(temp->pa->left==temp){
                temp->pa->left = temp->left;
            }
            else{
                temp->pa->right = temp->left;
            }
            
        }
        else{
            root=temp->left;
        }
        if(temp->left){
            temp->left->pa = temp->pa;
        }
    }
    else{
        if(temp->pa){//if the node has no left child, replace the node with its successor (the smallest node in the right subtree of the node)
            if(temp->pa->left==temp){
                temp->pa->left = temp->right;
            }
            else{
                temp->pa->right = temp->right;
            }
        }
        else{
            root=temp->right;
        }
        if(temp->right){
            temp->right->pa = temp->pa;  
        }
                    
    }
    free(temp);
}
```
###### 删除节点的实现
```c++
int AVL::del(int x){
    Node* temp = Find(x);//find the node with the given data
    if(temp==NULL){//if the node is not found, return 0
        return 0;
    }
    if(temp->left==NULL){//if the node has no left child, replace the node with its right child
        Node *pa=temp->pa;
        remove_Node(temp);
        if(pa){
            balance(pa);
        }          
    }
    else{//if the node has a left child, replace the node with its successor (the biggest node in the left subtree of the node)
        Node* min_node = temp->left;
        while(min_node->right!=NULL){
            min_node = min_node->right;
        }
        temp->data = min_node->data;
        Node *pa=min_node->pa;
        remove_Node(min_node);
        if(pa){
            balance(pa);
        }
        
    }
    return 1;
}
```



##### 正确性验证
###### 思路
1. 首先，我们需要对AVL树的插入和删除操作进行正确性验证。
2. 其次，我们要验证是否为一个平衡二叉树。
###### 正确的插入和删除
我们建立一个列表用朴素方法插入删除，并用中序遍历遍历二叉树并与列表进行比较，如果相同则验证成功。
###### 实现列表的插入和删除
```c++
void List::init(){
    tot=0;
    memset(List,0,sizeof(List));
}
void List::ins(int y){//insert y into the list
    tot++;
    int j;
    for(j=tot;j>1;j--){//find the position to insert y
        if(List[j-1]<=y){
            break;
        }
        List[j]=List[j-1];//shift the elements to the right
    }
    List[j]=y;//insert y into the position j
}
int List::del(int y){//delete the first occurrence of y from the list
    int j;
    for(j=1;j<=tot;j++){//find the position of y
        if(List[j]==y){
            break;
        }
    }
    if(j==tot+1){//y is not in the list
        return 0;
    }
    else{//y is in the list
        for(;j<tot;j++){
            List[j]=List[j+1];
        }
        tot--;
        return 1;
    }
}
```
###### 中序遍历
```c++
int checkorder(Node* node,int List[],int *cnt) {
    if(node==NULL){
        return 1;
    }
    int res=1;
    if(node->left){//check the left subtree
        res&=checkorder(node->left,List,cnt);
    }
    (*cnt)++;
    if(List[*cnt]!=node->data){//check whether the order is same to the given list
        res=0;
    }
    if(node->right){//check the right subtree
        res&=checkorder(node->right,List,cnt);
    }
    return res;
}
```
###### 验证平衡性
我们使用朴素方法深度优先遍历二叉树，并计算每个节点的高度和平衡因子，如果高度差大于1则验证失败。
```c++
int checkdepth(Node* node,int *res) {
    if(node==NULL){
        // *res=1;
        return 0;
    }
    int temp=1,left_height=0,right_height=0;
    if(node->left){//get the height of left subtree
        left_height=checkdepth(node->left,&temp);
    }   
    if(node->right){//get the height of right subtree
        right_height=checkdepth(node->right,&temp);
    }
    if(temp==0||(abs(left_height-right_height)>1)){//if the height difference is greater than 1 or the subtree is not balancesd, the tree is not balanced
        *res=0;        
    }
    return max(left_height,right_height)+1;
}
```
###### 随机数据生成与验证
通过 `rand()` 函数生成随机数据插入，在 `List` 中选择数据，小概率选择 `List` 外数据进行删除，并验证是否正确。
```c++
AVL myavl;// global AVL tree
List a;// global list to store the elements to check the order of the AVL tree
int main() {
    int N=10,M=10;
    srand(time(NULL));
    printf("Enter the turns and the number of elements\n");
    scanf("%d%d", &M,&N);//set the number of turns and the number of elements to generate
    int MM=M;
    while(MM--){
        a.init();//set the list to empty
        myavl.init();//set the AVL tree to empty
        for(int i=0;i<N;i++){
            // printf("%d\n",i);
            // int x,y;
            int x=rand()%4+1,y;
            if(x<=3){//set the operation to insert or delete 3:1
                x=1;
            }
            else{
                x=2;
            }
            if(x==2){//delete elements are mosetly chosen randomly from the list 
                y=rand()%(a.tot+1)+1;
                if(y<=a.tot){
                    y=a.List[y];
                }
                else{
                    y=a.List[a.tot]+3;
                }
            }
            else{
                y=rand()%100+1;
            }
            if(x==1){
                myavl.ins(y);
                a.ins(y);
            }
            else{
                if((myavl.del(y))!=(a.del(y))){//check whether the delete operation is correct if not stop the program
                    printf("Error \n");
                    return 0;
                }   
            }
            int res=1,flag=1;
            checkdepth(myavl.root,&flag);//check the balance of the AVL tree
            if(!flag){
                printf("The AVL tree is not balanced\n");
                return 0;
            }
            int cnt=0;
            flag=checkorder(myavl.root,a.List,&cnt);//check the order of the AVL tree
            if(!flag){
                printf("The AVL tree is not in order\n");
                return 0;
            }            
        }
        printf("finish turn %d of %d\n",M-MM,M);
    }
    
    return 0;
}

```
陆续进行了 1000 轮测试，每一轮测试 10000 组插入删除数据，经过测试，AVL 树均保持平衡并正确的插入和删除数据。


## Testing Results

TODO

## Analysis

TODO
