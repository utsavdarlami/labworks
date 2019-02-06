"""Tasks
1. Implement a Binary Search Tree with the following operations:
(a) isEmpty(): Returns true if the tree is empty, and false otherwise
(b) addBST(newNode): Inserts an element to the BST
(c) removeBST(keyToDelete): Removes the node with the given key
from the BST
(d) searchBST(targetKey): Returns true if the key exists in the tree, and
false otherwise
Also, write a test program to check if the implementation works properly."""

class Node(object):

    def __init__(self,data):
        #self.data = data #for string 
        self.data = int(data) #for integer 
        self.right  = None   
        self.left  = None

    def _deletechild(self,data):
        if self.right.data ==data:
            self.right =None
        elif self.left.data == data:
            self.left=None

    def __str__(self):
        return str(self.data)

class BST(object):
    def __init__(self):
        self.root  = (None)
        self.count = 0

    def isEmpty(self):
        if(self.root==None):
            return True
        else:
            return False
    
    def addBST(self,dvalue):
        newChild = Node(dvalue)
        if(self.isEmpty()):
            self.root = newChild
        else:
            self.insertBST(self.root,newChild)
           
    def insertBST(self,currentNode,newChild):
        if(newChild.data<currentNode.data and currentNode):
            if(currentNode.left==None):
                currentNode.left = newChild
            else:
                self.insertBST(currentNode.left,newChild)
        elif(newChild.data>=currentNode.data):
            if(currentNode.right==None):
                currentNode.right = newChild
            else:
                self.insertBST(currentNode.right,newChild)

    def traverseBST(self):
        show= []
        if self.isEmpty():
            return False
        else:
            self.inorderBST(self.root,show)
            return show

    def inorderBST(self,currentNode,show):
        if currentNode!=None:
            self.inorderBST(currentNode.left,show)
            show.append(currentNode.data)
            self.inorderBST(currentNode.right,show)

    def searchBST(self,targetKey):
        if(self.isEmpty()):
            return False
        else:
           return(self.FindBST(self.root,targetKey))

    def FindBST(self,currentNode,targetKey):
        if (currentNode != None):
            if(currentNode.data == targetKey):
                return True
            elif(targetKey > currentNode.data ):
                return(self.FindBST(currentNode.right,targetKey))
            elif(targetKey<currentNode.data):
                return(self.FindBST(currentNode.left,targetKey))
        else:
            return False
    
    def largestBST(self):
        if(self.isEmpty()):
            return False
        else:
            return(self.findlarge(self.root))
    
    def findlarge(self,currentNode):
        if(currentNode.right == None):
            return(currentNode)
        return(self.findlarge(currentNode.right))

    def removeBST(self,targetKey):

        if (self.searchBST(targetKey)):
            return(self.deleteBST(self.root,self.root,targetKey))
        else:
            return "No Such Item"

    def deleteBST(self,parentNode,currentNode,targetKey):
        if(targetKey > currentNode.data):
            self.deleteBST(parentNode,currentNode.right,targetKey)
        elif(targetKey < currentNode.data):
            self.deleteBST(parentNode,currentNode.left,targetKey)
        else:
            #deleteNode = Node(currentNode.data)
            temp  = Node(None)
            if(currentNode.left==None and currentNode.right==None):
                parentNode._deletechild(targetKey)
                return True
            elif(currentNode.left==None):
                temp = currentNode.right
                currentNode.data  = temp.data
                currentNode.right = temp.right
                currentNode.left = temp.left
                return True
            elif(currentNode.right==None):
                temp = currentNode.left
                currentNode.data  = temp.data
                currentNode.right = temp.right
                currentNode.left = temp.left
                return True
            else:
                deleteNode=currentNode
                largenode = self.findlarge(deleteNode.left)
                deleteNode.data = largenode.data
                return (self.deleteBST(deleteNode.left,largenode,largenode.data))
