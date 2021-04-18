#include <iostream>
#include "stack.h" //header file included.

using namespace std;

void Stack::push(int value) //value = user entered value.
{
    if (isFull()) //cannot push element if full.
    {
        cout << "Err...THE STACK IS FULL" << endl;
    }
    else
    {
        position++;              //increase the position of pointer .
        stack[position] = value; //assign the value to given stack position.
    }
}
int Stack::pop()
{
    int result;
    if (isEmpty()) //cannot pull element if empty.
    {
        cout << "Err...THE STACK IS EMPTY" << endl;
        return 0;
    }
    else
    {
        result = stack[position];
        position--; //decrease the position of pointer .
        return result;
    }
}
bool Stack::isEmpty()
{
    if (position == -1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool Stack::isFull()
{
    if (position >= SIZE)
    {
        return true;
    }
    else
    {
        return false;
    }
}
int Stack::top()
{
    if (isEmpty())
    {
        cout << "Err...THE STACK IS EMPTY" << endl;
    }
    else
    {
        return stack[position];
    }
}
void Stack::display() //to display each element of stack
{
    if (isEmpty())
    {
        cout << "Err...THE STACK IS EMPTY" << endl;
    }
    else
    {
        cout << "The Stack is :" << endl;
        for (int i = position; i >=0; i--) //loop to display each element in stack array.
        {
            cout << " " << stack[i] << endl;
        }
    }
}
