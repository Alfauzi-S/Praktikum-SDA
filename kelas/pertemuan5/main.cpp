#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node *next;
};

void transversal(Node *head)
{
    if (head == nullptr)
    {
        cout << "Linked list kosong" << endl;
        return;
    }

    Node *temp = head;
    while (temp != nullptr)
    {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "nullptr" << endl;
}

void addFirst(Node *&head, int databaru)
{
    Node *nodeBaru = new Node;
    nodeBaru->data = databaru;
    nodeBaru->next = head;
    head = nodeBaru;
}

void addMiddle(Node *&head, int databaru, int posisi)
{
    if (posisi <= 1)
    {
        addFirst(head, databaru);
        return;
    }

    Node *temp = head;
    int hitung = 1;
    while (temp != nullptr && hitung < posisi - 1)
    {
        temp = temp->next;
        hitung++;
    }
    if (temp == nullptr)
    {
        cout << ">> Posisi tidak boleh melebihi panjang list <<" <<

            endl;

        return;
    }
    else
    {
        Node *nodeBaru = new Node;
        nodeBaru->data = databaru;
        nodeBaru->next = temp->next;
        temp->next = nodeBaru;
    }
}

void addLast(Node *&head, int databaru)
{
    Node *nodeBaru = new Node;
    nodeBaru->data = databaru;
    nodeBaru->next = nullptr;
    // jika linked list kosong
    if (head == nullptr)
    {
        head = nodeBaru;
        return;
    }
    // jika tidak, traversal ke node terakhir
    Node *temp = head;
    while (temp->next != nullptr)
    {
        temp = temp->next;
    }
    temp->next = nodeBaru;
}

void deleteFirst(Node *&head)
{
    if (head == nullptr)
    {
        cout << ">> LinkedList masih kosong <<" << endl;
        return;
    }
    Node *temp = head;
    head = head->next;
    delete temp;
}

// Hapus data di tengah (posisi ke-n)
void deleteMiddle(Node *&head, int posisi)
{
    if (head == nullptr)
    {
        cout << ">> LinkedList masih kosong <<" << endl;
        return;
    }
    if (posisi <= 1)
    {
        deleteFirst(head);
        return;
    }
    Node *temp = head;
    int hitung = 1;
    while (temp->next != nullptr && hitung < posisi - 1)
    {
        temp = temp->next;
        hitung++;
    }
    if (temp->next == nullptr)
    {
        cout << ">> Posisi tidak valid <<" << endl;
    }
    else
    {
        Node *hapus = temp->next;
        temp->next = hapus->next;
        delete hapus;
    }
}

void deleteLast(Node *&head)
{
    if (head == nullptr)
    {
        cout << ">> LinkedList masih kosong <<" << endl;
        return;
    }
    if (head->next == nullptr)
    {
        delete head;
        head = nullptr;
        return;
    }
    Node *temp = head;
    while (temp->next->next != nullptr)
    {
        temp = temp->next;
    }
    delete temp->next;
    temp->next = nullptr;
}

void editData(Node *&head, int posisi, int dataBaru)
{
    if (head == nullptr)
    {
        cout << ">> LinkedList masih kosong <<" << endl;
        return;
    }
    Node *temp = head;
    int hitung = 1;
    while (temp != nullptr && hitung < posisi)
    {
        temp = temp->next;
        hitung++;
    }
    if (temp == nullptr)
    {
        cout << ">> Posisi tidak valid <<" << endl;
    }
    else
    {
        cout << "Data lama: " << temp->data << endl;
        temp->data = dataBaru;
        cout << "Data berhasil diubah menjadi: " << temp->data << endl;
    }
}

int main()
{
    Node *head = nullptr;
    addFirst(head, 10);
    addFirst(head, 11);
    addFirst(head, 12);
    addFirst(head, 13);
    addFirst(head, 14);
    addLast(head, 15);
    addMiddle(head, 18, 3);
    transversal(head);
    deleteFirst(head);
    deleteMiddle(head, 3);
    deleteLast(head);
    transversal(head);
    editData(head, 3, 99);
    transversal(head);
    return 0;
}