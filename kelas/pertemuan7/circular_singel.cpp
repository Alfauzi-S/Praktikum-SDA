#include <iostream>
using namespace std;

struct Mahasiswa {
    string nama;
    int nim;
    double ipk;
};

struct Node {
    Mahasiswa data;
    Node *next;
};

Node* newNode() {
    Node *nodeBaru = new Node();
    cout << "Masukan nama : ";
    cin >> nodeBaru->data.nama;
    cout << "Masukan nim  : ";
    cin >> nodeBaru->data.nim;
    cout << "Masukan ipk  : ";
    cin >> nodeBaru->data.ipk;
    nodeBaru->next = nullptr;
    return nodeBaru;
}

void addFirst(Node *&head) {
    Node *nodeBaru = newNode();
    if (head != nullptr) {
        Node *temp = head;
        while (temp->next != head) {
            temp = temp->next;
        }
        nodeBaru->next = head;
        temp->next = nodeBaru;
        head = nodeBaru;
    } else {
        head = nodeBaru;
        nodeBaru->next = head;
    }
}

void addLast(Node *&head) {
    Node *nodeBaru = newNode();
    if (head != nullptr) {
        Node *temp = head;
        while (temp->next != head) {
            temp = temp->next;
        }
        temp->next = nodeBaru;
        nodeBaru->next = head;
    } else {
        head = nodeBaru;
        nodeBaru->next = head;
    }
}

void display(Node *head) {
    if (head == nullptr) {
        cout << "---------------------------" << endl;
        cout << "Linked List Kosong" << endl;
        cout << "---------------------------" << endl;
        return;
    }

    Node *temp = head;
    cout << "---------------------------" << endl;
    do {
        cout << "Nama: " << temp->data.nama << endl;
        cout << "NIM : " << temp->data.nim << endl;
        cout << "IPK : " << temp->data.ipk << endl;
        cout << "---------------------------" << endl;
        temp = temp->next;
    } while (temp != head);
}

void deleteNode(Node *&head) {
    if (head == nullptr) {
        cout << "---------------------------" << endl;
        cout << "Linked List Kosong" << endl;
        cout << "---------------------------" << endl;
        return;
    }

    int key;
    cout << "Masukan nim yang ingin dihapus : ";
    cin >> key;

    // Jika hanya ada 1 node
    if (head->data.nim == key && head->next == head) {
        delete head;
        head = nullptr;
        cout << "Data berhasil dihapus" << endl;
        return;
    }

    Node *temp = head;
    // Jika menghapus node pertama
    if (head->data.nim == key) {
        while (temp->next != head) {
            temp = temp->next;
        }
        temp->next = head->next;
        delete head;
        head = temp->next;
        return;
    }

    // Menghapus di antara node
    while (temp->next != head && temp->next->data.nim != key) {
        temp = temp->next;
    }

    if (temp->next->data.nim == key) {
        Node *d = temp->next;
        temp->next = d->next;
        delete d;
        cout << "Data berhasil dihapus" << endl;
    } else {
        cout << "NIM tidak ditemukan" << endl;
    }
}

int main() {
    Node *HEAD = nullptr;
    int pilihan;
    while (true) {
        cout << "Program linked list" << endl;
        cout << "1. Add First" << endl;
        cout << "2. Add Last" << endl;
        cout << "3. Delete Node" << endl;
        cout << "4. Display" << endl;
        cout << "9. Exit Program" << endl;
        cout << "Masukan pilihan : ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                addFirst(HEAD);
                break;
            case 2:
                addLast(HEAD);
                break;
            case 3:
                deleteNode(HEAD);
                break;
            case 4:
                display(HEAD);
                break;
            case 9:
                cout << "Exit Program" << endl;
                return 0;
            default:
                cout << "Pilihan tidak ada" << endl;
        }
    }
    return 0;
}