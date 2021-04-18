#include <iostream>
#define SIZE 10 //size of the stack array.
class Stack
{
    int position = -1; //position of the pointer in stack.
    int stack[SIZE];   //defining stack array.

  public:
    void push(int);
    int pop();
    bool isEmpty();
    bool isFull();
    int top();
    void display();
};