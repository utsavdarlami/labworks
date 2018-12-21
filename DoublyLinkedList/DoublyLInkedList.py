"""
2. Implement a doubly linked list with the following operations:
(a) isEmpty(): Returns true if the list is empty, and false otherwise
(b) add(data, predecessor): Inserts an element after the given predecessor
node
(c) remove(data): Removes the node with the given data
(d) retrieve(data, outputNodePointer): Returns the pointer to the node
with the requested data
(e) search(data): Returns true if the data exists in the list, and false
otherwise
(f) traverse(): Displays the contents of the list
(g) reverse(): Displays the contents of the list in reverse order
Also, write a test program to check if the implementation works properly.
 """
class Node(object):

    def __init__(self,data):
    
        self.data = data;
        self.next = None;
        self.prev = None;

class LinkedList(object):

    def __init__(self):

        self.head = None;

    def isEmpty(self): 

        if self.head == None:
            return True;
        else :
            return False;

    def add(self,data,predecessor=None):
        newNode = Node(data);
        if self.isEmpty():
            self.head = newNode;
        elif(predecessor==None):
            self.head.prev= newNode;
            newNode.next = self.head;
            self.head=newNode;
        else:
            newNode.prev = predecessor;
            newNode.next = predecessor.next;
            #predecessor.next.prev = newNode;
            predecessor.next=newNode;
           
    def remove(self,data):

        if self.isEmpty():
            print("No Data to Remove")
        else:
            if(self.head.data==data):
                HeadNode  = self.head;        
                self.head =HeadNode.next ;
                del HeadNode.data;
                del HeadNode.next;
            else:
                currentNode =self.head;
                prevNode = None;
                if self.search(data):
                    while currentNode.data != data:
                        prevNode = currentNode;
                        currentNode = currentNode.next;
                    prevNode.next = currentNode.next
                    currentNode.prev = prevNode
                    del currentNode.data;
                    del currentNode.next;
                    del currentNode.prev;
                else:
                    print("No Such Data to Remove")
            
    def retrieve(self,data):

        currentNode =self.head;
        while currentNode != None and currentNode.data != data:
            currentNode = currentNode.next;
        return currentNode;

    def search(self,data):

        counter =0;
        currentNode =self.head;
        while currentNode != None:
            if currentNode.data == data:
                counter +=1;
            currentNode = currentNode.next;
        if counter==0:
            return False;
        else:
            return True;

    def traverse(self):
        currentNode =self.head;
        while currentNode != None:
            print(currentNode.data);
            currentNode = currentNode.next;
    
    def reverse(self):
        currentNode =self.head;
        while currentNode.next != None:
            currentNode = currentNode.next
        while currentNode != self.head:
            print(currentNode.data);
            currentNode = currentNode.prev
        print(currentNode.data);
        
