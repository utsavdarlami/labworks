"""
\Implement a singly linked list with the following operations:
(a) isEmpty(): Returns true if the list is empty, and false otherwise
(b) addToHead(data): Inserts an element to the beginning of the list
(c) addToTail(data): Inserts an element to the end of the list
(d) add(data, predecessor): Inserts an element after the given predecessor
node
(e) removeFromHead(): Removes the first node in the list
(f) remove(data): Removes the node with the given data
(g) retrieve(data, outputNodePointer): Returns the pointer to the node
with the requested data
(h) search(data): Returns true if the data exists in the list, and false
otherwise
(i) traverse(): Displays the contents of the list
Also, write a test program to check if the implementation works properly.
"""
class Node(object):

    def __init__(self,data):
    
        self.data = data;
        self.next = None;
class LinkedList(object):

    def __init__(self):

        self.head = None;

    def isEmpty(self): 

        if self.head == None:
            return True;
        else :
            return False;

    def addToHead(self,data):
        
        newNode = Node(data);
        if self.isEmpty():
            self.head=newNode;
        else:
            newNode.next = self.head;
            self.head = newNode;

    def addToTail(self,data):

        newNode = Node(data);
        if self.isEmpty():
            self.addToHead(data);
        else:
            tailNode = self.head;
            while tailNode.next != None:
                tailNode = tailNode.next
            tailNode.next=newNode;

    def add(self,data,predecessor):

        newNode = Node(data);
        newNode.next = predecessor.next;
        predecessor.next = newNode;

    def removeFromHead(self):

        if self.isEmpty():
            print("No Head to Remove")
        else:
            HeadNode  = self.head;        
            self.head =HeadNode.next ;
            del HeadNode.data;
            del HeadNode.next;

    def remove(self,data):

        if self.isEmpty():
            print("No Data to Remove")
        else:
            if(self.head.data==data):
                self.removeFromHead();
            else:
                currentNode =self.head;
                prevNode = None;
                if self.search(data):
                    while currentNode.data != data:
                        prevNode = currentNode;
                        currentNode = currentNode.next;
                    prevNode.next = currentNode.next
                    del currentNode.data;
                    del currentNode.next;
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