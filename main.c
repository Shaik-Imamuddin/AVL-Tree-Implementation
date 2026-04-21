#include<stdio.h>
#include<stdlib.h>

struct Node{
    int data,height;
    struct Node *left;
    struct Node *right;
};

struct Node*createNode(int val){
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = val;
    newNode->height = 1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

int height(struct Node*node){
    if(node==NULL)
        return 0;
    return node->height;
}

int max(int a,int b){
    return (a>b)?a:b;
}

int balanceFactor(struct Node*node){
    if(node==NULL)
        return 0;
    return height(node->left)-height(node->right);
}

/*
Right Rotation
Used when left subtree is heavier (LL case)

Steps:
1. y is unbalanced node
2. x = y->left
3. T2 = x->right
4. Perform rotation:
   x becomes new root
   y becomes right child of x
   T2 becomes left child of y
5. Update heights
*/

struct Node *rightRotate(struct Node *y){
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left),height(y->right))+1;
    x->height = max(height(x->left),height(x->right))+1;

    return x;
}

/*
Left Rotation
Used when right subtree is heavier (RR case)

Steps:
1. y is unbalanced node
2. x = y->right
3. T2 = x->left
4. Perform rotation:
   x becomes new root
   y becomes left child of x
   T2 becomes right child of y
5. Update heights
*/

struct Node *leftRotate(struct Node *y){
    struct Node *x = y->right;
    struct Node *T2 = x->left;

    x->left = y;
    y->right = T2;

    y->height = max(height(y->left),height(y->right))+1;
    x->height = max(height(x->left),height(x->right))+1;

    return x;
}

/*
Insert into AVL Tree

Steps:
1. Perform normal BST insertion
2. Update height
3. Calculate balance factor
4. Apply rotations if unbalanced:
   LL, RR, LR, RL
*/

struct Node *insert(struct Node *node,int val){
    if(node==NULL)
        return createNode(val);

    if(val<node->data)
        node->left = insert(node->left,val);
    else if(val>node->data)
        node->right = insert(node->right,val);
    else 
        return node;

    node->height = 1+max(height(node->left),height(node->right));

    int bal = balanceFactor(node);

    // LL case
    if(bal>1 && val<node->left->data)
        return rightRotate(node);

    // RR case
    if(bal<-1 && val>node->right->data)
        return leftRotate(node);

    // LR case
    if(bal>1 && val>node->left->data){
        node->left=leftRotate(node->left);
        return rightRotate(node);
    }

    // RL case
    if(bal<-1 && val<node->right->data){
        node->right=rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

void inorder(struct Node*root){
    if(root!=NULL){
        inorder(root->left);
        printf("%d ",root->data);
        inorder(root->right);
    }
}

void preorder(struct Node*root){
    if(root!=NULL){
        printf("%d ",root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(struct Node*root){
    if(root!=NULL){
        postorder(root->left);
        postorder(root->right);
        printf("%d ",root->data);
    }
}

int main(){
    struct Node*root=NULL;
    int val;

    do{
        scanf("%d",&val);
        if(val!=-1)
            root=insert(root,val);
    }while(val!=-1);

    inorder(root);
    printf("\n");
    preorder(root);
    printf("\n");
    postorder(root);
    return 0;
}