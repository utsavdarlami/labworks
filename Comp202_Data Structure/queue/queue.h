#include <iostream>
#define SIZE 10 //size of the Queue array.
class Queue
{
    int pfront = -1;        //position of the front pointer in Queue.
    int rear = -1;          //position of the rear pointer in Queue.
    char queue_array[SIZE]; //defining Queue array.

  public:
    void enqueue(char); //assign the char to given Queue position.
    char dequeue();     //access and remove the char to given Queue position
    bool isEmpty();     //Checks if the queue is empty
    bool isFull();      //Checks if the queue is full
    char front();       //to display front element of Queue
    char back();        //to display back element of Queue
    void display();     // to display each element in Queue array.
};