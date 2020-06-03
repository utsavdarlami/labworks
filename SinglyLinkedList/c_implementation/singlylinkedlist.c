#include<stdio.h>
#include<stdlib.h>
#include "singlylinkedlist.h"

int isEmpty(LinkedList l_List){
    /* isEmpty(): Returns true if the list is empty, and false otherwise*/
    if(l_List.head == NULL){
        return 1;
    }
    return 0;
}

void addToHead(LinkedList *l_list,int data){
    /*Inserts an int data to the beginning of the list*/
    Node *newNode;
    newNode = malloc(sizeof(*newNode));
    newNode->data = data;
    newNode->next = NULL;

    if(isEmpty(*l_list)){
        l_list->head = newNode;
    }
    else{
        newNode->next =  l_list->head;
        l_list->head = newNode;
    }
}

void addToTail(LinkedList * l_list, int data){
    /*Inserts an element to the end of the list*/
    Node *newNode;
    newNode = malloc(sizeof(*newNode));
    newNode->data = data;
    newNode->next = NULL;

    if(isEmpty(*l_list)){
        l_list->head = malloc(sizeof(*newNode));
        l_list->head = newNode;
    }
    else{
        Node *tailNode = l_list->head;
        while(tailNode->next!=NULL){
           tailNode = tailNode->next; 
        }
        tailNode->next = newNode;
    }
}

void add(int data, Node *predecessor){
    /*Inserts an element after the given predecessor node*/
    Node *newNode;
    newNode = malloc(sizeof(*newNode));
    newNode->data = data;
    newNode->next = predecessor->next; 
    predecessor->next = newNode;
}

void removeFromHead(LinkedList *l_list){
    /*Removes the first node in the list*/
    if(isEmpty(*l_list)){
        printf("This List Is Empty\n");
    }
    else{
        Node *headNode = l_list->head;
        l_list->head = headNode->next;
        free(headNode);
    }
}

void removeData(LinkedList *l_list, int data){
    /* Removes the node with the given data*/

    if(isEmpty(*l_list)){
        printf("This List Is Empty\n");
    }
    else if(search(l_list,data)){
        if(l_list->head->data == data){
            removeFromHead(l_list);
        }
        else{
            Node *currentNode = l_list->head;
            Node *previousNode ;
            while(currentNode->data != data){
                previousNode = currentNode;
                currentNode = currentNode->next;
            }
            previousNode->next = currentNode->next;
            free(currentNode);
        }
    }
    else{
        printf("No Such Data to Remove\n");

    }
}

Node * retrieve(LinkedList *l_list, int data){
    /* Returns the pointer to the node with the requested data*/
    if(isEmpty(*l_list)){
        printf("This List Is Empty\n");
        return NULL;
    }
    else if(search(l_list,data)){
        Node *currentNode = l_list->head;
        while(currentNode->data != data){
            currentNode = currentNode->next;
        }
        return currentNode;
    }
    else{
        printf("No Such Data to Retrieve\n");
        return NULL;
    }
}

int search(LinkedList *l_list, int data){
    /*Returns true if the data exists in the list, and false otherwise*/
    if(isEmpty(*l_list)){
        printf("This List Is Empty\n");
        return 0;
    }
    else{
        Node *currentNode = l_list->head;
        while(currentNode->next !=  NULL){
            if(currentNode->data == data){
                return 1;
            }
            currentNode = currentNode->next;
        }
        if(currentNode->data == data){
            return 1;
        }
        return 0;
    }
}

void traverse(LinkedList l_list){
    /*Displays the contents of the list*/
    if(isEmpty(l_list)){
        printf("This List Is Empty\n");
    }
    else{
        Node *currentNode = l_list.head;
        while(currentNode->next != NULL){
            printf("%d, ",currentNode->data);
            currentNode = currentNode->next;
        }
        printf("%d \n",currentNode->data);
    }
}

void freeList(LinkedList *l_list){
    /*Free's the memory allocated to the list*/
    if(isEmpty(*l_list)){
        printf("This List Is Empty\n");
    }
    else{
        while(!isEmpty(*l_list)){
            removeFromHead(l_list);
        }
    }
}


