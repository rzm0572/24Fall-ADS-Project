#include "BST.h"
#include<stdio.h>
#include<stdlib.h>
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
void swap(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}
int max(int x,int y){
    return (x>y)?x:y;
}
//creating a node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;//assign data to newNode
    newNode->left = NULL;//initialize left and right child of newNode to NULL
    newNode->right = NULL;
    newNode->pa = NULL;
    newNode->h_left = 0;//initialize height of left and right subtree of newNode to 0
    newNode->h_right = 0;
    newNode->det = 0;
    return newNode;
}
//refresh the height and balance factor of a node
void Refresh(Node *node){
    int maxn=0;//max height of left subtree
    if(node->left){
        if(node->left->h_left>maxn){//update max height of the left subtree of left subtree
            maxn=node->left->h_left;
        }
        if(node->left->h_right>maxn){//update max height of the left subtree of left subtree
            maxn=node->left->h_right;
        }
        maxn++;
    }
    node->h_left=maxn;
    maxn=0;
    if(node->right){//update height and balance factor of right subtree
        if(node->right->h_left>maxn){//update max height of the left subtree of right subtree
            maxn=node->right->h_left;
        }
        if(node->right->h_right>maxn){//update max height of the right subtree of right subtree
            maxn=node->right->h_right;
        }
        maxn++;
    }
    node->h_right=maxn;//update height of right subtree
    node->det = node->h_left - node->h_right;
}
struct AVL{
    Node* root;

    void AVL::init(){
        root = NULL;
    }
    //将自己的右儿子变成根，自己变成左儿子，左旋。
    void AVL::twistL(Node* node){
        Node* temp = node->right;
        //confirm whether the right child of node is not NULL
        if(temp!=NULL){
            node->h_right = temp->h_left;
            temp->h_left = max(node->h_left,node->h_right)+1;
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
            node->right = temp->left;
            if(temp->left){
                temp->left->pa=node;
            }
            
            temp->left = node;
            node->det = node->h_left - node->h_right;
            temp->det = temp->h_left - temp->h_right;
        } 
    }
    //将自己的左儿子变成根，自己变成右儿子，右旋。
    void AVL::twistR(Node* node){//Right rotation
        Node* temp = node->left;//left child
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
    //search the node with the given data and return the node if found, otherwise, return NULL
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
    // };
    //the function to check whether the tree is balanced
    //the function will return 1 if the tree is balanced, otherwise, it will return 0
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
    void printtree(Node* node) {
        if(node==NULL) return;
        if(node){//if node is not null
            // printf("%d %d %d %d %d\n", node->data,node->h_left,node->h_right,node->det,node->pa->data);
            printf("id:%d,son1:%d,son2:%d,balance:%d,parent:%d\n", node->data,node->left?node->left->data:-1,node->right?node->right->data:-1,node->det,node->pa?node->pa->data:-1);
        }    //write the node's information
        printtree(node->left);//print the left subtree
        printtree(node->right);//print the right subtree
    }
    //search the tree in order and check whether the order is same to the given list
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
};

void TestBST(int n, Operation ops[]) {
    AVL myAVL;
    myAVL.init();
    for (int i = 0; i < n; i++) {
        switch (ops[i].optype) {
            case 0: {
                myAVL.ins(ops[i].key);
                break;
            }
            case 1: {
                myAVL.del(ops[i].key);
                break;
            }
        }
        // printf("Operation %d: optype = %d, key = %d\n", i, ops[i].optype, ops[i].key);
        // bst.output();
        // printf("\n");
    }
}
