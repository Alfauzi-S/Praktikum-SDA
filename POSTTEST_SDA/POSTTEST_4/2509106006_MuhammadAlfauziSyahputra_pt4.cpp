#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <ctime>

#ifdef _WIN32
#include <windows.h>
#else
#include <cstdlib>
#include <unistd.h>
#endif

using namespace std;

void cls() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pause() {
#ifdef _WIN32
    system("pause");
#else
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
#endif
}

void clearInputBuffer() {
    cin.clear();
    cin.ignore(10000, '\n');
}

string getInput(const string& prompt) {
    cout << prompt;
    string input;
    getline(cin, input);
    return input;
}

int getValidInt(const string& prompt) {
    string input;
    int value;
    bool valid = false;

    while (!valid) {
        cout << prompt;
        getline(cin, input);

        try {
            size_t pos;
            value = stoi(input, &pos);
            if (pos != input.length()) {
                throw invalid_argument("Input mengandung karakter non-digit.");
            }
            if (value < 0) {
                cout << "Nilai tidak boleh negatif. Silakan coba lagi." << endl;
                continue;
            }
            valid = true;
        } catch (const invalid_argument& e) {
            cout << "Input tidak valid! Harap masukkan angka saja." << endl;
        } catch (const out_of_range& e) {
            cout << "Input terlalu besar! Harap masukkan angka yang lebih kecil." << endl;
        }
    }
    return value;
}

struct Kereta {
    string no_kereta;
    string nama_kereta;
    string rute_asal;
    string rute_tujuan;
    int harga_tiket;
    string waktu_berangkat;
};

struct Penumpang {
    string nama_penumpang;
    string rute_yang_dipilih;
    int harga_tiket_pesanan;
};

struct Transaksi {
    string nama_penumpang;
    string rute_kereta;
    int harga_transaksi;
    string waktu_transaksi;
};

struct NodePenumpang {
    Penumpang data;
    NodePenumpang* next;
};

struct NodeTransaksi {
    Transaksi data;
    NodeTransaksi* next;
};

#define maxKereta 100

Kereta kereta[maxKereta];
int jumlah_kereta = 0;

NodePenumpang* head_queue = nullptr;
NodePenumpang* tail_queue = nullptr;

NodeTransaksi* top_stack = nullptr;

bool isEmptyQueue() {
    return head_queue == nullptr;
}

int size_queue() {
    int count = 0;
    NodePenumpang* current = head_queue;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

void enqueue(Penumpang* p) {
    NodePenumpang* newNode = new NodePenumpang;
    newNode->data = *p;
    newNode->next = nullptr;

    if (tail_queue == nullptr) {
        head_queue = tail_queue = newNode;
    } else {
        tail_queue->next = newNode;
        tail_queue = newNode;
    }
    cout << "Penumpang " << p->nama_penumpang << " (Rute: " << p->rute_yang_dipilih 
         << ", Harga: Rp " << p->harga_tiket_pesanan << ") ditambahkan ke antrian." << endl;
}

Penumpang dequeue() {
    if (isEmptyQueue()) {
        cout << "Queue underflow! Tidak ada penumpang dalam antrian." << endl;
        return {"", "", -1};
    }
    NodePenumpang* temp = head_queue;
    Penumpang value = head_queue->data;
    head_queue = head_queue->next;
    if (head_queue == nullptr) {
        tail_queue = nullptr;
    }
    delete temp;
    cout << "Penumpang " << value.nama_penumpang << " (Rute: " << value.rute_yang_dipilih 
         << ", Harga: Rp " << value.harga_tiket_pesanan << ") diproses dan dikeluarkan dari antrian." << endl;
    return value;
}

int peek_queue() {
    if (isEmptyQueue()) {
        cout << "Queue is empty. Tidak ada penumpang di antrian terdepan." << endl;
        return -1;
    }
    cout << "Penumpang terdepan di antrian: " << head_queue->data.nama_penumpang 
         << " (Rute: " << head_queue->data.rute_yang_dipilih << ")" << endl; 
    return 0;
}

void display_queue() {
    if (isEmptyQueue()) {
        cout << "Antrian kosong." << endl;
        return;
    }
    cout << "Daftar Antrian Pembelian Tiket (Total: " << size_queue() << " orang):" << endl;
    cout << "--------------------------------------------------------------------------" << endl;
    NodePenumpang* current = head_queue;
    int position = 1;
    while (current != nullptr) {
        cout << "Posisi " << position << ": Nama: " << current->data.nama_penumpang 
             << ", Rute: " << current->data.rute_yang_dipilih 
             << ", Harga: Rp " << current->data.harga_tiket_pesanan << endl; 
        current = current->next;
        position++;
    }
    cout << "--------------------------------------------------------------------------" << endl;
}

bool isStackEmpty() {
    return top_stack == nullptr;
}

int size_stack() {
    int count = 0;
    NodeTransaksi* current = top_stack;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

void push(Transaksi* t) {
    NodeTransaksi* newNode = new NodeTransaksi;
    newNode->data = *t;
    newNode->next = top_stack;
    top_stack = newNode;
    cout << "Transaksi untuk " << t->nama_penumpang << " (Rute: " << t->rute_kereta 
         << ", Harga: Rp " << t->harga_transaksi << ") ditambahkan ke riwayat." << endl;
}

Transaksi pop() {
    if (isStackEmpty()) {
        cout << "Stack underflow! Tidak ada transaksi untuk dibatalkan." << endl;
        return {"", "", -1, ""};
    }
    NodeTransaksi* temp = top_stack;
    Transaksi value = top_stack->data;
    top_stack = top_stack->next;
    delete temp;
    cout << "Transaksi terakhir (" << value.nama_penumpang << ", Rute: " << value.rute_kereta << ", Harga: Rp " << value.harga_transaksi << ") dihapus dari riwayat." << endl;
    return value;
}

int peek_stack() {
    if (isStackEmpty()) {
        cout << "Stack is empty. Tidak ada transaksi terakhir." << endl;
        return -1;
    }
    cout << "Transaksi terakhir di riwayat: " << top_stack->data.nama_penumpang 
         << " (Rute: " << top_stack->data.rute_kereta << ", Harga: Rp " << top_stack->data.harga_transaksi << ")" << endl; 
    return 0;
}

void display_stack() {
    if (isStackEmpty()) {
        cout << "Riwayat transaksi kosong." << endl;
        return;
    }
    cout << "Isi Riwayat Transaksi (Total: " << size_stack() << " transaksi):" << endl;
    cout << "----------------------------------------------------------------------------------------" << endl;
    NodeTransaksi* current = top_stack;
    int position = 1;
    while (current != nullptr) {
        cout << "Posisi " << position << ": Nama: " << current->data.nama_penumpang 
             << ", Rute: " << current->data.rute_kereta 
             << ", Harga: Rp " << current->data.harga_transaksi 
             << ", Waktu: " << current->data.waktu_transaksi << endl; 
        current = current->next;
        position++;
    }
    cout << "----------------------------------------------------------------------------------------" << endl;
}

void tampilJadwal(Kereta*arr, int n) {
    cout << "\n>>> DAFTAR JADWAL KERETA API <<<" << endl;
    cout << "--------------------------------------------------------------------------------------------------" << endl;
    cout << left << setw(10) << "NO KERETA" << setw(15) << "NAMA KERETA" << setw(15) << "ASAL" << setw(15) << "TUJUAN" << setw(12) << "HARGA (Rp)" << "WAKTU BERANGKAT" << endl;
    cout << "--------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < n; i++) {
        cout << left << setw(10) << (arr + i)->no_kereta
            << setw(15) << (arr + i)->nama_kereta
            << setw(15) << (arr + i)->rute_asal
            << setw(15) << (arr + i)->rute_tujuan
            << setw(12) << (arr + i)->harga_tiket
            << (arr + i)->waktu_berangkat << endl;
    }
    cout << "--------------------------------------------------------------------------------------------------" << endl;
}

bool cekDuplikasiNoKereta(string no_kereta_baru) {
    for (int i = 0; i < jumlah_kereta; i++) {
        if (kereta[i].no_kereta == no_kereta_baru) {
            return true;
        }
    }
    return false;
}

void tambahKereta(Kereta* arr, int& n) {
    if (n >= maxKereta) {
        cout << "Kapasitas kereta penuh!" << endl;
        return;
    }

    cout << "\n>>> TAMBAH DATA KERETA BARU <<<" << endl;
    string no_kereta_baru;
    do {
        no_kereta_baru = getInput("Masukkan nomor kereta: ");
        if (cekDuplikasiNoKereta(no_kereta_baru)) {
            cout << "Nomor kereta '" << no_kereta_baru << "' sudah ada! Silakan masukkan nomor kereta yang berbeda." << endl;
        }
    } while (cekDuplikasiNoKereta(no_kereta_baru));

    (arr + n)->no_kereta = no_kereta_baru;
    (arr + n)->nama_kereta = getInput("Masukkan nama kereta: ");
    string rute_asal_input, rute_tujuan_input;
    do {
        rute_asal_input = getInput("Masukkan rute asal: ");
        rute_tujuan_input = getInput("Masukkan rute tujuan: ");
        if (rute_asal_input == rute_tujuan_input) {
            cout << "Rute asal dan tujuan tidak boleh sama! Silakan masukkan kembali." << endl;
        }
    } while (rute_asal_input == rute_tujuan_input);
    
    (arr + n)->rute_asal = rute_asal_input;
    (arr + n)->rute_tujuan = rute_tujuan_input;
    (arr + n)->harga_tiket = getValidInt("Masukkan harga tiket: ");
    (arr + n)->waktu_berangkat = getInput("Masukkan waktu berangkat: ");

    n++;
    cout << "Data kereta berhasil ditambahkan!" << endl;
}

void updateKereta(Kereta* arr, int n) {
    if (n == 0) {
        cout << "Tidak ada data kereta untuk diupdate!" << endl;
        return;
    }

    string no_kereta_cari = getInput("Masukkan nomor kereta yang ingin diupdate: ");
    int index = -1;
    for (int i = 0; i < n; i++) {
        if ((arr + i)->no_kereta == no_kereta_cari) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Nomor kereta tidak ditemukan!" << endl;
        return;
    }

    cout << "\n>>> UPDATE DATA KERETA <<<" << endl;
    cout << "Data lama:" << endl;
    cout << "No Kereta: " << (arr + index)->no_kereta << endl;
    cout << "Nama: " << (arr + index)->nama_kereta << endl;
    cout << "Asal: " << (arr + index)->rute_asal << endl;
    cout << "Tujuan: " << (arr + index)->rute_tujuan << endl;
    cout << "Harga: Rp " << (arr + index)->harga_tiket << endl;
    cout << "Waktu: " << (arr + index)->waktu_berangkat << endl;

    (arr + index)->nama_kereta = getInput("Masukkan nama kereta baru: ");
    string rute_asal_baru, rute_tujuan_baru;
    do {
        rute_asal_baru = getInput("Masukkan rute asal baru: ");
        rute_tujuan_baru = getInput("Masukkan rute tujuan baru: ");
        if (rute_asal_baru == rute_tujuan_baru) {
            cout << "Rute asal dan tujuan tidak boleh sama! Silakan masukkan kembali." << endl;
        }
    } while (rute_asal_baru == rute_tujuan_baru);
    
    (arr + index)->rute_asal = rute_asal_baru;
    (arr + index)->rute_tujuan = rute_tujuan_baru;
    (arr + index)->harga_tiket = getValidInt("Masukkan harga tiket baru: ");
    (arr + index)->waktu_berangkat = getInput("Masukkan waktu berangkat baru: ");

    cout << "Data kereta berhasil diupdate!" << endl;
}

void hapusKereta(Kereta* arr, int& n) {
    if (n == 0) {
        cout << "Tidak ada data kereta untuk dihapus!" << endl;
        return;
    }

    string no_kereta_hapus = getInput("Masukkan nomor kereta yang ingin dihapus: ");
    int index = -1;
    for (int i = 0; i < n; i++) {
        if ((arr + i)->no_kereta == no_kereta_hapus) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Nomor kereta tidak ditemukan!" << endl;
        return;
    }

    cout << "\nData yang akan dihapus:" << endl;
    cout << "No Kereta: " << (arr + index)->no_kereta << endl;
    cout << "Nama: " << (arr + index)->nama_kereta << endl;
    cout << "Asal: " << (arr + index)->rute_asal << endl;
    cout << "Tujuan: " << (arr + index)->rute_tujuan << endl;
    cout << "Harga: Rp " << (arr + index)->harga_tiket << endl;
    cout << "Waktu: " << (arr + index)->waktu_berangkat << endl;

    string konfirmasi_str = getInput("Apakah Anda yakin ingin menghapus data ini? (y/n): ");
    char konfirmasi = konfirmasi_str.empty() ? 'n' : konfirmasi_str[0];

    if (konfirmasi == 'y' || konfirmasi == 'Y') {
        for (int i = index; i < n - 1; i++) {
            *(arr + i) = *(arr + i + 1);
        }
        n--;
        cout << "Data kereta berhasil dihapus!" << endl;
    } else {
        cout << "Penghapusan dibatalkan." << endl;
    }
}

void mergeByNumber(Kereta* arr, int l, int m, int r);
void mergeSortByNumber(Kereta* arr, int l, int r);
void selectionSort(Kereta* arr, int n);

int jumpSearch(Kereta* arr, int n, string no_kereta) {
    mergeSortByNumber(arr, 0, n - 1);
    int step = static_cast<int>(sqrt(n));
    int prev = 0;

    while (prev < n && (arr + prev)->no_kereta < no_kereta) {
        int next_step = prev + step;
        if (next_step < n && (arr + next_step - 1)->no_kereta < no_kereta) {
            prev = next_step;
        } else {
            break;
        }
    }

    int batas = min(prev + step, n);
    for (int i = prev; i < batas; i++) {
        if ((arr + i)->no_kereta == no_kereta) {
            return i;
        }
    }

    return -1;
}

int linearSearch(Kereta* arr, int n, string rute) {
    string rute_terbalik = "";
    size_t pos = rute.find(" - ");
    if (pos != string::npos) {
        string asal = rute.substr(0, pos);
        string tujuan = rute.substr(pos + 3);
        rute_terbalik = tujuan + " - " + asal;
    }

    for (int i = 0; i < n; i++) {
        string full_rute = (arr + i)->rute_asal + " - " + (arr + i)->rute_tujuan;
        if (full_rute == rute || full_rute == rute_terbalik) {
            return i;
        }
    }
    return -1;
}

void mergeByNumber(Kereta* arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    Kereta* L = new Kereta[n1];
    Kereta* R = new Kereta[n2];

    for (int i = 0; i < n1; i++)
        L[i] = *(arr + l + i);
    for (int j = 0; j < n2; j++)
        R[j] = *(arr + m + 1 + j);

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i].no_kereta <= R[j].no_kereta) {
            *(arr + k) = L[i];
            i++;
        } else {
            *(arr + k) = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        *(arr + k) = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        *(arr + k) = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void mergeSortByNumber(Kereta* arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSortByNumber(arr, l, m);
        mergeSortByNumber(arr, m + 1, r);

        mergeByNumber(arr, l, m, r);
    }
}

void mergeName(Kereta* arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    Kereta* L = new Kereta[n1];
    Kereta* R = new Kereta[n2];

    for (int i = 0; i < n1; i++)
        L[i] = *(arr + l + i);
    for (int j = 0; j < n2; j++)
        R[j] = *(arr + m + 1 + j);

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i].nama_kereta <= R[j].nama_kereta) {
            *(arr + k) = L[i];
            i++;
        } else {
            *(arr + k) = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        *(arr + k) = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        *(arr + k) = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void mergeSortByName(Kereta* arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSortByName(arr, l, m);   
        mergeSortByName(arr, m + 1, r); 

        mergeName(arr, l, m, r);
    }
}

void swapKereta(Kereta* a, Kereta* b) {
    Kereta temp = *a;
    *a = *b;       
    *b = temp;      
}

void bubbleSort(Kereta* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if ((arr + j)->harga_tiket > (arr + j + 1)->harga_tiket) {
                swapKereta((arr + j), (arr + j + 1));
            }
        }
    }
}

void selectionSort(Kereta* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if ((arr + j)->harga_tiket < (arr + min_idx)->harga_tiket) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            swapKereta((arr + i), (arr + min_idx)); 
        }
    }
}

void swapDataNodePenumpang(NodePenumpang* node1, NodePenumpang* node2) {
    if (node1 == nullptr || node2 == nullptr) {
        cout << "Error: Salah satu atau kedua node adalah nullptr. Tidak bisa ditukar." << endl;
        return;
    }
    Penumpang temp_data = node1->data;
    node1->data = node2->data;
    node2->data = temp_data;
    cout << "Data penumpang antara dua node berhasil ditukar menggunakan dereferensi pointer." << endl;
}

void cobaSwapDuaAntrianPertama() {
    if (head_queue == nullptr || head_queue->next == nullptr) {
        cout << "Tidak cukup antrian untuk menukar dua data pertama (antrian kosong atau hanya satu elemen)." << endl;
        return;
    }
    cout << "Sebelum swap dua antrian pertama:" << endl;
    display_queue();

    swapDataNodePenumpang(head_queue, head_queue->next);

    cout << "\nSetelah swap dua antrian pertama:" << endl;
    display_queue();
}

int main() {
    kereta[0] = {"KA003", "Bima", "Jakarta", "Mataram", 420000, "20:00"};
    kereta[1] = {"KA001", "Argo Bromo", "Jakarta", "Surabaya", 350000, "06:00"};
    kereta[2] = {"KA002", "Gajayana", "Bandung", "Malang", 280000, "08:30"};
    jumlah_kereta = 3;

    string pilihan;
    while(pilihan != "0") {
        cls();
        cout << "================== Sistem manajemen keberangkatan Kereta Api ==================" << endl;
        cout << "1) Tampil jadwal semua kereta (menggunakan pointer)" << endl;
        cout << "2) Tambah data kereta baru" << endl;
        cout << "3) Linear Search cari berdasarkan rute (asal & tujuan)" << endl;
        cout << "4) Jump Search cari berdasarkan nomor kereta" << endl;
        cout << "5) Merge sort urutkan berdasarkan nama kereta (A-Z)" << endl;
        cout << "6) Bubble Sort urutkan berdasarkan harga tiket (termurah)" << endl;
        cout << "7) Selection Sort urutkan berdasarkan harga tiket (termurah)" << endl;
        cout << "8) Update data kereta" << endl;
        cout << "9) Hapus data kereta" << endl;
        cout << "10) Tambah Penumpang ke Antrian Pembelian Tiket (Queue - Linked List)" << endl;
        cout << "11) Proses Tiket (Dequeue - Linked List)" << endl;
        cout << "12) Batalkan Transaksi Terakhir (Pop - Linked List)" << endl;
        cout << "13) Penumpang Terdepan (Peek - Linked List)" << endl;
        cout << "14) Tampil semua antrian (Linked List)" << endl;
        cout << "15) Tampil semua riwayat (Linked List)" << endl;
        cout << "16) Swap Dua Data Antrian Pertama (Dereferensi Pointer)" << endl;
        cout << "0) Keluar Program" << endl;
        cout << "-------------------------------------------------------------------------------" << endl;
        pilihan = getInput("Masukan Pilihan: ");

        if(pilihan == "1") {
            cls();
            tampilJadwal(kereta, jumlah_kereta);
            pause();
        } else if(pilihan == "2") {
            cls();
            tambahKereta(kereta, jumlah_kereta);
            pause();
        } else if(pilihan == "3") {
            cls();
            cout << ">>> Linear Search <<<" << endl;
            string ruteCari = getInput("Masukkan rute (asal & tujuan) dengan format 'Asal - Tujuan' (contoh: Jakarta - Surabaya): ");

            int indexLinear = linearSearch(kereta, jumlah_kereta, ruteCari);
            if (indexLinear != -1) {
                cout << "-----------------------------------------------------------" << endl;
                cout << "Data ditemukan di indeks: " << indexLinear << endl;
                cout << "No Kereta: " << (kereta + indexLinear)->no_kereta << endl;
                cout << "Nama: " << (kereta + indexLinear)->nama_kereta << endl;
                cout << "Rute: " << (kereta + indexLinear)->rute_asal << " - " << (kereta + indexLinear)->rute_tujuan << endl;
                cout << "Harga: Rp " << (kereta + indexLinear)->harga_tiket << endl;
                cout << "Waktu: " << (kereta + indexLinear)->waktu_berangkat << endl;
                cout << "-----------------------------------------------------------" << endl;
            } else {
                cout << "-----------------------------------------------------------" << endl;
                cout << "Data tidak ditemukan!" << endl;
            }
            pause();
        } else if(pilihan == "4") {
            cls();
            cout << ">>> Jump Search <<<" << endl;
            string noKeretaCari = getInput("Masukkan nomor kereta: ");

            int indexJump = jumpSearch(kereta, jumlah_kereta, noKeretaCari);
            if (indexJump != -1) {
                cout << "-----------------------------------------------------------" << endl;
                cout << "Data ditemukan di indeks: " << indexJump << endl;
                cout << "No Kereta: " << (kereta + indexJump)->no_kereta << endl;
                cout << "Nama: " << (kereta + indexJump)->nama_kereta << endl;
                cout << "Rute: " << (kereta + indexJump)->rute_asal << " - " << (kereta + indexJump)->rute_tujuan << endl;
                cout << "Harga: Rp " << (kereta + indexJump)->harga_tiket << endl;
                cout << "Waktu: " << (kereta + indexJump)->waktu_berangkat << endl;
                cout << "-----------------------------------------------------------" << endl;
            } else {
                cout << "-----------------------------------------------------------" << endl;
                cout << "Data tidak ditemukan!" << endl;
            }
            pause();
        } else if(pilihan == "5") {
            cls();
            cout << ">>> Merge Sort <<<" << endl;
            tampilJadwal(kereta, jumlah_kereta);
            mergeSortByName(kereta, 0, jumlah_kereta - 1);
            cout << "\nData setelah diurutkan (Merge Sort - Nama Kereta A-Z):\n";
            tampilJadwal(kereta, jumlah_kereta);
            pause();
        } else if(pilihan == "6") {
            cls();
            cout << ">>> Bubble Sort <<<" << endl;
            cout << "Data sebelum diurutkan (Bubble Sort - Harga Tiket):\n";
            tampilJadwal(kereta, jumlah_kereta);
            bubbleSort(kereta, jumlah_kereta);
            cout << "\nData setelah diurutkan (Bubble Sort - Harga Tiket Termurah):\n";
            tampilJadwal(kereta, jumlah_kereta);
            pause();
        } else if(pilihan == "7") {
            cls();
            cout << ">>> Selection Sort <<<" << endl;
            cout << "Data sebelum diurutkan (Selection Sort - Harga Tiket):\n";
            tampilJadwal(kereta, jumlah_kereta);
            selectionSort(kereta, jumlah_kereta);
            cout << "\nData setelah diurutkan (Selection Sort - Harga Tiket Termurah):\n";
            tampilJadwal(kereta, jumlah_kereta);
            pause();
        } else if(pilihan == "8") {
            cls();
            updateKereta(kereta, jumlah_kereta);
            pause();
        } else if(pilihan == "9") {
            cls();
            hapusKereta(kereta, jumlah_kereta);
            pause();
        } else if(pilihan == "10") {
            cls();
            if (jumlah_kereta == 0) {
                cout << "Belum ada data kereta. Tidak bisa memesan tiket." << endl;
            } else {
                string nama = getInput("Masukkan nama penumpang: ");
                
                cout << "Daftar Rute Tersedia:" << endl;
                for (int i = 0; i < jumlah_kereta; i++) {
                    cout << "- " << (kereta + i)->rute_asal << " - " << (kereta + i)->rute_tujuan << endl;
                }
                
                string rute = getInput("Masukkan rute yang dipilih (format: Asal - Tujuan): ");

                int harga_pesanan = -1;
                for (int i = 0; i < jumlah_kereta; i++) {
                    if ((kereta + i)->rute_asal + " - " + (kereta + i)->rute_tujuan == rute) {
                        harga_pesanan = (kereta + i)->harga_tiket;
                        break;
                    }
                }

                if (harga_pesanan != -1) {
                    Penumpang p_baru = {nama, rute, harga_pesanan};
                    enqueue(&p_baru);
                } else {
                    cout << "Rute tidak ditemukan dalam daftar kereta!" << endl;
                }
            }
            pause();
        } else if(pilihan == "11") {
            cls();
            Penumpang p_diproses = dequeue();
            if (p_diproses.nama_penumpang != "" && p_diproses.harga_tiket_pesanan != -1) {
                 time_t now = time(0);
                 char buffer[100];
                 strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M", localtime(&now));
                 string waktu_sekarang = buffer;
        
                 Transaksi t_baru = {p_diproses.nama_penumpang, p_diproses.rute_yang_dipilih, 
                                   p_diproses.harga_tiket_pesanan, waktu_sekarang};
                 push(&t_baru);
            }
            pause();
        } else if(pilihan == "12") {
            cls();
            pop();
            pause();
        } else if(pilihan == "13") {
            cls();
            peek_queue();
            pause();
        } else if(pilihan == "14") {
            cls();
            display_queue();
            pause();
        } else if(pilihan == "15") {
            cls();
            display_stack();
            pause();
        }else if(pilihan == "16") {
            cls();
            cobaSwapDuaAntrianPertama();
            pause();
        } else if(pilihan == "0") {
            cout << "Terima kasih telah menggunakan sistem informasi kereta api!" << endl;
            break;
        } else {
            cout << "Pilihan tidak valid!" << endl;
            pause();
        }
    }
    return 0;
}