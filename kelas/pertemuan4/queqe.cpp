#include <iostream>
#define MAX 100
using namespace std;
int queue[MAX];
int front = -1, rear = -1;

bool isFull()
{
    // Jika posisi rear sudah di indeks terakhir (MAX-1), maka penuh
    return rear == MAX - 1;
}
bool isEmpty()
{
    // Kosong jika front masih -1 ATAU front sudah melewati
    // posisi rear (setelah banyak dequeue)
    return front == -1 || front > rear;
}

void enqueue(int value)
{
    // jika queue full hentikan program
    if (isFull())
    {
        cout << "Queue overflow" << endl;
        return;
    }
    // Jika elemen pertama masuk, set front
    // ke indeks 0 agar queue aktif
    if (front == -1)
    {
        front = 0;
    }
    rear++;              // Geser posisi rear ke kanan untuk tempat elemen baru
    queue[rear] = value; // Masukkan nilai ke posisi rear yang baru
    cout << value << " enqueued into queue" << endl;
}

int dequeue()
{
    // jika queue kosong hentikan program
    if (isEmpty())
    {
        cout << "Queue underflow" << endl;
        return -1;
    }
    // Ambil nilai yang ada di posisi paling depan (front)
    int value = queue[front];
    // Geser front ke kanan (elemen dianggap "keluar" dari antrean)
    front++;
    // Cek apakah setelah dihapus antrean jadi kosong total
    if (isEmpty())
    {
        // Jika ya, reset kedua penanda ke posisi awal (-1)
        front = rear = -1;
    }
    return value;
}

int peek()
{
    if (isEmpty())
    {
        cout << "Queue is empty" << endl;
        return -1;
    }
    // Mengembalikan nilai di posisi front saat ini
    return queue[front];
}

void display()
{
    if (isEmpty())
    {
        cout << "Queue is empty" << endl;
        return;
    }
    cout << "Queue elements: ";
    // Loop mulai dari posisi front sampai ke rear
    for (int i = front; i <= rear; i++)
    {
        cout << queue[i] << " ";
    }
    cout << endl;
}

int main()
{
    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);    
    display();
    cout << peek() << endl;
    dequeue();
    display();
    cout << peek();
}