#include <iostream>
using namespace std;

void pause(){
    cout << "Press Enter to continue...";
    cin.ignore(1000, '\n');
    cin.get();
}

struct mahasiswa {

string nama;
    int nim;
    double ipk;
};
struct Node {
    mahasiswa data;
    Node *next;
    Node *prev;
};

int panjangList = 0;

void insertFirst(Node *&head, Node *&tail) {
    cout << "\n[ Tambah data di awal ]" << endl;
    Node *newNode = new Node();
    cout << "Nama: "; cin.ignore(); getline(cin, newNode->data.nama);
    cout << "NIM : "; cin >> newNode->data.nim;
    cout << "IPK : "; cin >> newNode->data.ipk;
    newNode->prev = NULL;
    newNode->next = head;
    if (head == NULL && tail == NULL) {
        head = newNode;
        tail = newNode;
    } else {
        head->prev = newNode;
        head = newNode;
    }
    panjangList++;
    cout << "Data telah tersimpan." << endl;
    pause();
    }

void insertLast(Node *&head, Node *&tail) {
    cout << "\n[ Tambah data di akhir ]" << endl;
    Node *newNode = new Node();
    cout << "Nama: "; cin.ignore(); getline(cin, newNode->data.nama);
    cout << "NIM : "; cin >> newNode->data.nim;
    cout << "IPK : "; cin >> newNode->data.ipk;
    newNode->prev = tail;
    newNode->next = NULL;
    if (head == NULL && tail == NULL) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    panjangList++;
    cout << "Data telah tersimpan." << endl;
    pause();
}

void insertAt(Node *&head, Node *&tail, int posisi) {
    if (posisi < 1 || posisi > panjangList + 1) {
        cout << "Posisi tidak valid!" << endl;
        pause();
        return;
    }
    if (posisi == 1) {
        insertFirst(head, tail);
    } else if (posisi == panjangList + 1) {
        insertLast(head, tail);
    } else {
    cout << "\n[ Tambah data di posisi " << posisi << " ]" << endl;
    Node *newNode = new Node();
    cout << "Nama: "; cin.ignore(); getline(cin, newNode->data.nama);
    cout << "NIM : "; cin >> newNode->data.nim;
    cout << "IPK : "; cin >> newNode->data.ipk;
    Node *temp = head;
    for (int i = 1; i < posisi - 1; i++) {
            temp = temp->next;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        temp->next->prev = newNode;
        temp->next = newNode;

        panjangList++;
        cout << "Data telah tersimpan." << endl;
        pause();
    }
}

void deleteFirst(Node *&head, Node *&tail) {
    if (head == NULL && tail == NULL) {
        cout << "LinkedList Kosong" << endl;
        pause();
    } else if (head->next == NULL) {
        delete head;
        head = NULL;
        tail = NULL;
        panjangList--;
        cout << "Data telah terhapus." << endl;
        pause();
    } else {
        Node *del = head;
        head = head->next;
        head->prev = NULL;
        delete del;
        panjangList--;
        cout << "Data telah terhapus." << endl;
        pause();
    }
}

void deleteLast(Node *&head, Node *&tail) {
    if (head == NULL && tail == NULL) {
        cout << "LinkedList Kosong" << endl;
        pause();
    } else if (head->next == NULL) {
        delete head;
        head = NULL;
        tail = NULL;
        panjangList--;
        cout << "Data telah terhapus." << endl;
        pause();
    } else {
        Node *del = tail;
        tail = tail->prev;
        tail->next = NULL;
        delete del;
        panjangList--;
        cout << "Data telah terhapus." << endl;
        pause();
    }
}

void deleteAt(Node *&head, Node *&tail, int posisi) {
    if (posisi < 1 || posisi > panjangList) {
        cout << "Posisi tidak valid!" << endl;
        pause();
        return;
    }

    if (posisi == 1) {
        deleteFirst(head, tail);
    } else if (posisi == panjangList) {
        deleteLast(head, tail);
    } else {
        Node *temp = head;
        for (int i = 1; i < posisi; i++) {
            temp = temp->next;
        }

        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;

        panjangList--;
        cout << "Data telah terhapus." << endl;
        pause();
    }
}

void printList(Node *head) {
    if (head == nullptr) {
        cout << ">> LinkedList masih kosong <<" << endl;
        return;
    }
    cout << "\nIsi LinkedList:" << endl;
    int i = 1;
    while (head != nullptr) {
        cout << i++ << ". Nama: " << head->data.nama
             << ", NIM: " << head->data.nim
             << ", IPK: " << head->data.ipk << endl;
        head = head->next;
    }
    cout << endl;
}

int main() {
    Node *head = NULL;
    Node *tail = NULL;
    int pilihan, posisi;

    do {
        system("cls || clear");
        cout << "=== MENU DOUBLY LINKED LIST ===" << endl;
        cout << "1. Tambah di awal" << endl;
        cout << "2. Tambah di akhir" << endl;
        cout << "3. Tambah di posisi tertentu" << endl;
        cout << "4. Hapus di awal" << endl;
        cout << "5. Hapus di akhir" << endl;
        cout << "6. Hapus di posisi tertentu" << endl;
        cout << "7. Tampilkan list" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: insertFirst(head, tail); break;
            case 2: insertLast(head, tail); break;
            case 3:
                cout << "Masukkan posisi: "; cin >> posisi;
                insertAt(head, tail, posisi);
                break;
            case 4: deleteFirst(head, tail); break;
            case 5: deleteLast(head, tail); break;
            case 6:
                cout << "Masukkan posisi: "; cin >> posisi;
                deleteAt(head, tail, posisi);
                break;
            case 7:
                printList(head);
                pause();
                break;
            case 0:
                cout << "Program selesai." << endl;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
                pause();
        }
    } while (pilihan != 0);

    return 0;
}