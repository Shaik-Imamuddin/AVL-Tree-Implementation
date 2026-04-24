import java.util.Scanner;

class Node{
    int data,height;
    Node left,right;

    Node(int val){
        data = val;
        height = 1;
        left = right = null;
    }
}

class AVLTree{

    Node root;

    AVLTree(){
        root=null;
    }

    int height(Node node){
        if(node==null)
            return 0;
        return node.height;
    }

    int max(int a,int b){
        return (a>b)?a:b;
    }

    int balanceFactor(Node node){
        if(node==null)
            return 0;
        return height(node.left)-height(node.right);
    }

    /*
    
    Right rotation performed when the left subtree becomes heavier than the right subtree.

    Steps for Right rotation.

        Step-1:identify the Nodes

            check the unbalanced Node make it as y.
            x = y.left
            T2 = x.right

        Step-2:Rotate

            x becomes new root
            y becomes right child of x
            t2 becomes left child of y

        At the end update heights of x and y and return new root Node

    */

    Node rightRotate(Node y){
        Node x = y.left;
        Node T2 = x.right;

        x.right = y;
        y.left = T2;

        y.height = Math.max(height(y.left),height(y.right))+1;
        x.height = Math.max(height(x.left),height(x.right))+1;

        return x;
    }

    /*
    
    Left rotation is performed when the right subtree becomes heavier than the left subtree.

    Steps for Left Rotation

    Step-1: Identify the Nodes

        Check the unbalanced node and make it y.
        x = y.right
        T2 = x.left

    Step-2: Rotate
        x becomes the new root
        y becomes the left child of x
        T2 becomes the right child of y

    At the end update heights of x and y and return new root Node

    */

    Node leftRotate(Node y){
        Node x = y.right;
        Node T2 = x.left;

        x.left = y;
        y.right = T2;

        y.height = Math.max(height(y.left),height(y.right))+1;
        x.height = Math.max(height(x.left),height(x.right))+1;

        return x;
    }

    Node insert(Node node,int val){
        if(node==null)
            return new Node(val);

        if(val < node.data)
            node.left = insert(node.left,val);
        else if(val > node.data)
            node.right = insert(node.right,val);
        else
            return node;

        //after inserting a newNode update height
        node.height = 1+max(height(node.left),height(node.right));

        //check balanced factor
        int bal = balanceFactor(node);

        //LL
        if(bal>1 && val<node.left.data)
            return rightRotate(node);

        //RR
        if(bal<-1 && val>node.right.data)
            return leftRotate(node);

        //LR
        if(bal>1 && val>node.left.data){
            node.left = leftRotate(node.left);
            return rightRotate(node);
        }

        //RL
        if(bal<-1 && val<node.right.data){
            node.right = rightRotate(node.right);
            return leftRotate(node);
        }
        return node;
    }

    void inorder(Node root){
        if(root!=null){
            inorder(root.left);
            System.out.print(root.data+" ");
            inorder(root.right);
        }
    }

    void preorder(Node root){
        if(root!=null){
            System.out.print(root.data+" ");
            preorder(root.left);
            preorder(root.right);
        }
    }

    void postorder(Node root){
        if(root!=null){
            postorder(root.left);
            postorder(root.right);
            System.out.print(root.data+" ");
        }
    }

}

public class Main{
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        AVLTree tree = new AVLTree();

        int val;
        do{
            val=sc.nextInt();
            if(val!=-1)
                tree.root = tree.insert(tree.root,val);
        }while(val!=-1);
        tree.inorder(tree.root);
        System.out.println();
        tree.preorder(tree.root);
        System.out.println();
        tree.postorder(tree.root);
    }
}