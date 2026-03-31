#include <iostream>
#define MAX 100
using namespace std;
int stack[MAX];
int top = -1; // Menandakan elemen teratas pada stack

void push(int value)
{
    if (top >= MAX - 1)
    {
        cout << "Stack overflow" << endl;
    }
    else
    {
        top++;
        stack[top] = value;
        cout << value << " pushed into stack" << endl;
    }
}

int pop()
{
    if (top < 0)
    {
        cout << "Stack underflow" << endl;
        return -1;
    }
    else
    {
        int value = stack[top];
        top--;
        return value;
    }
}
int peek()
{
    if (top < 0)
    {
        cout << "Stack is empty" << endl;
        return -1;
    }
    else
    {
        return stack[top];
    }
}

bool isEmpty()
{
    return (top < 0);
}

int main()
{
    push(10);
    push(20);
    push(30);
    push(40);
    cout << peek();
    pop();
    cout << peek();
}