#include <iostream>
#include "stack.h"
using namespace std;
int main()
{
    int removed;
    cout << "Hello STACK user" << endl;
    Stack s;
    if (s.isEmpty())//checking isEmpty function
    {
        cout << "Stack is empty." << endl;
    }
    else
    {
        cout << "Stack is not empty." << endl;
    }                                                      //object of stack is created.
    s.push(5);                                             //5 is pushed in stack s.
    s.push(10);                                            //10 is pushed
    cout << "top element in stack  = " << s.top() << endl; //top element of stack is displayed
    s.push(15);                                            //15 is pushed to stack
    removed = s.pop();                                     //top is popped and stored to variable removed.
    cout << removed << " is removed ." << endl;
    s.push(20);  //20 is pushed
    s.display(); //whole element in stack is displayed.
    if (s.isEmpty())
    {
        cout << "Stack is empty." << endl;
    }
    else
    {
        cout << "Stack is not empty." << endl;
    }                                                      
    return 0;
}