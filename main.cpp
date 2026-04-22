#include<iostream>
using namespace std;

class Node{
public:
    int data,height;
    Node *left;
    Node *right;
    Node(int val){
        data = val;
        height = 1;
        left = right = NULL;
    }
};

class AVLTree{
public:
    Node *root;
    AVLTree(){
        root = NULL;
    }

    int height(Node *node){
        if(node==NULL)
            return 0;
        return node->height;
    }

    int max(int a,int b){
        return (a>b)?a:b;
    }

    int balanceFactor(Node *node){
        if(node==NULL)
            return 0;
        return height(node->left)-height(node->right);
    }

    Node *rightRotate(Node *y){
        Node *x = y->left;
        Node *T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left),height(y->right))+1;
        x->height = max(height(x->left),height(x->right))+1;

        return x;
    }

    Node *leftRotate(Node *y){
        Node *x = y->right;
        Node *T2 = x->left;

        x->left = y;
        y->right = T2;

        y->height = max(height(y->left),height(y->right))+1;
        x->height = max(height(x->left),height(x->right))+1;

        return x;
    }

    Node *insert(Node *node,int val){
        if(node==NULL)
            return new Node(val);

        if(val<node->data)
            node->left = insert(node->left,val);
        else if(val>node->data)
            node->right = insert(node->right,val);
        else
            return node;

        node->height = 1+max(height(node->left),height(node->right));

        int bal=balanceFactor(node);

        // LL
        if(bal>1 && val<node->left->data)
            return rightRotate(node);

        // RR
        if(bal<-1 && val>node->right->data)
            return leftRotate(node);

        // LR
        if(bal>1 && val>node->left->data){
            node->left=leftRotate(node->left);
            return rightRotate(node);
        }

        // RL
        if(bal<-1 && val<node->right->data){
            node->right=rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    void inorder(Node *root){
        if(root!=NULL){
            inorder(root->left);
            cout<<root->data<<" ";
            inorder(root->right);
        }
    }

    void preorder(Node *root){
        if(root!=NULL){
            cout<<root->data<<" ";
            preorder(root->left);
            preorder(root->right);
        }
    }

    void postorder(Node *root){
        if(root!=NULL){
            postorder(root->left);
            postorder(root->right);
            cout<<root->data<<" ";
        }
    }
};

int main(){
    AVLTree tree;
    int val;

    do{
        cin>>val;
        if(val!=-1)
            tree.root=tree.insert(tree.root,val);
    }while(val!=-1);

    tree.inorder(tree.root);
    cout<<"\n";
    tree.preorder(tree.root);
    cout<<"\n";
    tree.postorder(tree.root);
    return 0;
}