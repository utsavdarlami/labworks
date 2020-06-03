#ifndef SINGLYLINKEDLIST_H_   
#define SINGLYLINKEDLIST_H_   

struct Node {
    int data;
    struct Node *next;
};
typedef struct Node Node;

struct LinkedList {
    struct Node *head;
};
typedef struct LinkedList LinkedList;

int isEmpty(LinkedList l_List);
void addToHead(LinkedList * l_list, int data);
void addToTail(LinkedList * l_list, int data);
void add(int data, Node *predecessor);

void removeFromHead(LinkedList *l_list);
void removeData(LinkedList *l_list, int data);
Node * retrieve(LinkedList *l_list, int data);

int search(LinkedList *l_list, int data);

void traverse(LinkedList l_list);
void freeList(LinkedList *l_list);

#endif //SINGLYLINKEDLIST_H_   
