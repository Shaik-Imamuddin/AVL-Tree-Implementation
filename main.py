# Node structure
class Node:
    def __init__(self,val):
        self.data=val
        self.height=1
        self.left=None
        self.right=None

class AVLTree:
    def __init__(self):
        self.root=None

    def height(self,node):
        if node==None:return 0
        return node.height

    def max(self,a,b):
        return a if a>b else b

    def balanceFactor(self,node):
        if node==None:return 0
        return self.height(node.left)-self.height(node.right)

    # Right Rotation (LL case)
    def rightRotate(self,y):
        x=y.left
        T2=x.right

        x.right=y
        y.left=T2

        y.height=self.max(self.height(y.left),self.height(y.right))+1
        x.height=self.max(self.height(x.left),self.height(x.right))+1

        return x

    # Left Rotation (RR case)
    def leftRotate(self,y):
        x=y.right
        T2=x.left

        x.left=y
        y.right=T2

        y.height=self.max(self.height(y.left),self.height(y.right))+1
        x.height=self.max(self.height(x.left),self.height(x.right))+1

        return x

    def insert(self,node,val):
        if node==None:return Node(val)

        if val<node.data:
            node.left=self.insert(node.left,val)
        elif val>node.data:
            node.right=self.insert(node.right,val)
        else:
            return node

        node.height=1+self.max(self.height(node.left),self.height(node.right))

        bal=self.balanceFactor(node)

        # LL
        if bal>1 and val<node.left.data:
            return self.rightRotate(node)

        # RR
        if bal<-1 and val>node.right.data:
            return self.leftRotate(node)

        # LR
        if bal>1 and val>node.left.data:
            node.left=self.leftRotate(node.left)
            return self.rightRotate(node)

        # RL
        if bal<-1 and val<node.right.data:
            node.right=self.rightRotate(node.right)
            return self.leftRotate(node)

        return node

    def inorder(self,root):
        if root!=None:
            self.inorder(root.left)
            print(root.data,end=" ")
            self.inorder(root.right)

    def preorder(self,root):
        if root!=None:
            print(root.data,end=" ")
            self.preorder(root.left)
            self.preorder(root.right)

    def postorder(self,root):
        if root!=None:
            self.postorder(root.left)
            self.postorder(root.right)
            print(root.data,end=" ")

tree=AVLTree()

while True:
    val=int(input())
    if val==-1:
        break
    tree.root=tree.insert(tree.root,val)

tree.inorder(tree.root)
print()
tree.preorder(tree.root)
print()
tree.postorder(tree.root)