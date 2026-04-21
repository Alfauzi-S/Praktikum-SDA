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
    Node *prev;
};

Node* newNode() {
    Node *nodeBaru = new Node();
    cout << "Masukan nama : ";
    cin >> nodeBaru->data.nama;
    cout << "Masukan nim  : ";
    cin >> nodeBaru->data.nim;
    cout << "Masukan ipk  : ";
    cin >> nodeBaru->data.ipk;
    nodeBaru->next = nodeBaru;
    nodeBaru->prev = nodeBaru;
    return nodeBaru;
}

void addFirst(Node *&head, Node *&tail) {
    Node *nodeBaru = newNode();
    if (head != nullptr) {
        nodeBaru->next = head;
        nodeBaru->prev = tail;
        head->prev = nodeBaru;
        tail->next = nodeBaru;
        head = nodeBaru;
    } else {
        head = nodeBaru;
        tail = nodeBaru;
    }
}

void addLast(Node *&head, Node *&tail) {
    Node *nodeBaru = newNode();
    if (head != nullptr) {
        nodeBaru->prev = tail;
        nodeBaru->next = head;
        tail->next = nodeBaru;
        head->prev = nodeBaru;
        tail = nodeBaru;
    } else {
        head = nodeBaru;
        tail = nodeBaru;
    }
}

void display(Node *head, bool isHeadToTail) {
    if (head == nullptr) {
        cout << "---------------------------" << endl;
        cout << "Linked List Kosong" << endl;
        cout << "---------------------------" << endl;
        return;
    }

    Node *temp = (isHeadToTail) ? head : head->prev;
    cout << "---------------------------" << endl;
    do {
        cout << "Nama: " << temp->data.nama << endl;
        cout << "NIM : " << temp->data.nim << endl;
        cout << "IPK : " << temp->data.ipk << endl;
        cout << "---------------------------" << endl;
        temp = (isHeadToTail) ? temp->next : temp->prev;
    } while (temp != head);
}

void deleteNode(Node *&head, Node *&tail) {
    if (head == nullptr) {
        cout << "---------------------------" << endl;
        cout << "Linked List Kosong" << endl;
        cout << "---------------------------" << endl;
        return;
    }

    int key;
    cout << "Masukan nim yang ingin dihapus : ";
    cin >> key;

    // Jika hanya ada satu node
    if (head->data.nim == key && head->next == head) {
        delete head;
        head = nullptr;
        tail = nullptr;
        cout << "Data berhasil dihapus" << endl;
        return;
    }

    Node *temp = head;

    // Jika yang ingin dihapus adalah node pertama
    if (head->data.nim == key) {
        tail->next = head->next;
        head->next->prev = tail;
        delete head;
        head = tail->next;
        return;
    }

    // Menghapus di antara node
    while (temp->next != head && temp->next->data.nim != key) {
        temp = temp->next;
    }

    if (temp->next->data.nim == key) {
        Node *d = temp->next;
        temp->next = d->next;
        d->next->prev = temp;
        delete d;
        cout << "Data berhasil dihapus" << endl;
    } else {
        cout << "NIM tidak ditemukan" << endl;
    }
}

int main() {
    Node *HEAD = nullptr;
    Node *TAIL = nullptr;
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
                addFirst(HEAD, TAIL);
                break;
            case 2:
                addLast(HEAD, TAIL);
                break;
            case 3:
                deleteNode(HEAD, TAIL);
                break;
            case 4: {
                cout << "Display" << endl;
                cout << "1. HEAD to TAIL" << endl;
                cout << "2. TAIL to HEAD" << endl;
                cout << "Masukan pilihan : ";
                cin >> pilihan;
                if (pilihan == 1) {
                    display(HEAD, true);
                } else if (pilihan == 2) {
                    display(HEAD, false);
                } else {
                    cout << "Pilihan tidak ada" << endl;
                }
                break;
            }
            case 9:
                cout << "Exit Program" << endl;
                return 0;
            default:
                cout << "Pilihan tidak ada" << endl;
        }
    }
    return 0;
}