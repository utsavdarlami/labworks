#include <iostream>
#include "queue.h"
using namespace std;

int main()
{
    Queue q;
    char first_dequeued;
    char front_dat,back_data;
    if (q.isEmpty())
    {
        cout << "THE queue is empty" << endl;
        q.enqueue('U');
    }
    q.enqueue('t');
    q.enqueue('s');
    q.enqueue('a');
    q.enqueue('v');

    first_dequeued = q.dequeue();
    cout << "First dequeued char is ==> " << first_dequeued << endl;
    cout<<"Front Data in the queue ==> "<<q.front()<<endl;
    cout<<"Rear Data in the queue ==> "<<q.back()<<endl;

    if (q.isFull())
    {
        cout << "THE Queue is Full" << endl;
    }
    else
    {
        cout<<"The Queue is Not Full"<<endl;
    }
    q.display();
    return 0;
}