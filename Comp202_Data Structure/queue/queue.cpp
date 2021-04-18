#include <iostream>
#include "queue.h" //header file included.

using namespace std;

void Queue::enqueue(char element) //element = user entered value.
{
    if (isFull()) //cannot push element if full.
    {
        cout << "Err...THE Queue IS FULL" << endl;
    }
    else if (isEmpty())
    {
        rear = 0;
        pfront = 0;
        queue_array[rear] = element; //assign the value to given Queue position.
    }
    else
    {
        rear++;                      //increase the position of pointer . & enqueue always from front.
        queue_array[rear] = element; //assign the value to given Queue position.
    }
}
char Queue::dequeue()
{
    int result;
    if (isEmpty()) //cannot pull element if empty.
    {
        cout << "Err...THE Queue IS EMPTY" << endl;
        return 0;
    }
    else
    {
        result = queue_array[pfront];   //dequeue always from front.
        for (int i = 0; i <= rear; i++) //loop to display each element in Queue array.
        {
            queue_array[i] = queue_array[i + 1];
        }
        rear--; //decrease the rear value since queue decreases after dequeue.
        return result;
    }
}
bool Queue::isEmpty()
{
    if (pfront < 0 || pfront > rear)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool Queue::isFull()
{
    if (rear >= SIZE)
    {
        return true;
    }
    else
    {
        return false;
    }
}
char Queue::front() //to display front element of Queue
{
    if (isEmpty())
    {
        cout << "Err...THE Queue IS EMPTY" << endl;
    }
    else
    {
        return queue_array[pfront];
    }
}
char Queue::back() //to display rear element of Queue
{
        if (isEmpty())
        {
            cout << "Err...THE Queue IS EMPTY" << endl;
        }
        else
        {
            return queue_array[rear];
        }
}
void Queue::display() //to display each element of Queue
{
    if (isEmpty())
    {
        cout << "Err...THE Queue IS EMPTY" << endl;
    }
    else
    {
        cout << "The Queue is :" << endl;
        for (int i = 0; i <= rear; i++) //loop to display each element in Queue array.
        {
            cout << " " << queue_array[i] << "  ";
        }
    }
}
