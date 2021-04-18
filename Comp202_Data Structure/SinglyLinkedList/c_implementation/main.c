#include<stdio.h>
#include<stdlib.h>
#include "singlylinkedlist.h"

void listEmpty(LinkedList list){
    if(isEmpty(list)){
        printf("This List Is Empty\n");
    }
    else{
        printf("This List Is Not Empty\n");
    }
}

void searchData(LinkedList *list,int data){
    if(search(list,data)){
        printf("%d is in List \n",data);
    }
    else{
        printf("%d is not in Not List\n",data);
    }
}

int main(){
    LinkedList list;
    
    list.head = NULL; 

    listEmpty(list);

    addToHead(&list,9);

    listEmpty(list);

    addToHead(&list,88);

    addToHead(&list,69);

    addToTail(&list,99);

    searchData(&list,99);

    traverse(list);

    removeFromHead(&list);

    searchData(&list,88);

    traverse(list);

    removeData(&list,9);

    traverse(list);
 
    Node *node88;

    node88 = retrieve(&list,88);

    printf("Node retrieve is : %d\n",node88->data);

    add(77,node88);

    traverse(list);

    freeList(&list);

    return 0;
}
