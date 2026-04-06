#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cmath>

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

# define maxKereta 100
#define MAX_QUEUE 50
#define MAX_STACK 50

Kereta kereta[maxKereta];
int jumlah_kereta = 0;

Penumpang queue[MAX_QUEUE];
int front = -1, rear = -1;

Transaksi stack[MAX_STACK];
int top = -1;

bool isFull(){
    // Jika posisi rear sudah di indeks terakhir(MAX_QUEUE-1), maka penuh
    return rear == MAX_QUEUE - 1;
}

bool isEmpty(){
    // Kosong jika front masih -1 ATAU front sudah melewati posisi rear (setelah banyak dequeue)
    return front == -1 || front > rear;
}

void enqueue(Penumpang* p){ // Fungsi menerima pointer struct*
    // jika queue full hentikan program
    if(isFull()){
        cout << "Queue overflow! Antrian pembelian tiket penuh." << endl;
        return;
    }
    // Jika elemen pertama masuk, set front ke indeks 0 agar queue aktif
    if(front == -1){
        front = 0;
    }
    rear++; // Geser posisi rear ke kanan untuk tempat elemen baru
    queue[rear] = *p; // Masukkan nilai ke posisi rear yang baru (dereferensi pointer)
    cout << p->nama_penumpang << " (Rute: " << p->rute_yang_dipilih << ") enqueued ke antrian." << endl;
}

Penumpang dequeue(){
    // jika queue kosong hentikan program
    if(isEmpty()){
        cout << "Queue underflow! Tidak ada penumpang dalam antrian." << endl;
        return {"", "", -1}; // Return struct kosong
    }
    // Ambil nilai yang ada di posisi paling depan(front)
    Penumpang value = queue[front];
    // Geser front ke kanan (elemen dianggap "keluar" dari antrean)
    front++;
    // Cek apakah setelah dihapus antrean jadi kosong total
    if(isEmpty()){
        // Jika ya, reset kedua penanda ke posisi awal(-1)
        front = rear = -1;
    }
    cout << value.nama_penumpang << " (Rute: " << value.rute_yang_dipilih << ") dikeluarkan dari antrian (diproses)." << endl;
    return value;
}

int peek_queue(){
    if(isEmpty()){
        cout << "Queue is empty. Tidak ada penumpang di antrian terdepan." << endl;
        return -1;
    }
    // Mengembalikan nilai di posisi front saat ini
    cout << "Penumpang terdepan di antrian: " << queue[front].nama_penumpang << " (Rute: " << queue[front].rute_yang_dipilih << ")" << endl;
    return 0; // Atau return queue[front];
}

void display_queue(){
    if(isEmpty()){
        cout << "Queue is empty." << endl;
        return;
    }
    cout << "Daftar Antrian Pembelian Tiket (Front -> Rear): " << endl;
    // Gunakan pointer arithmetic untuk iterasi array queue
    Penumpang* base_ptr = queue; // Pointer dasar ke array queue
    // Loop mulai dari posisi front sampai ke rear
    for(int i = front; i <= rear; i++){
        Penumpang* current_ptr = base_ptr + i; // Hitung alamat elemen ke-i
        cout << "Indeks " << i << ": Nama: " << current_ptr->nama_penumpang << ", Rute: " << current_ptr->rute_yang_dipilih << ", Harga: Rp " << current_ptr->harga_tiket_pesanan << endl;
    }
    cout << endl;
}

bool isStackFull(){
    return top >= MAX_STACK - 1;
}

bool isStackEmpty(){
    return top < 0;
}

void push(Transaksi* t){ // Fungsi menerima pointer struct*
    if(top >= MAX_STACK - 1){
        cout << "Stack overflow! Riwayat transaksi penuh." << endl;
    } else{
        top++;
        stack[top] = *t; // Dereferensi untuk menyimpan nilai ke array
        cout << t->nama_penumpang << " (Rute: " << t->rute_kereta << ", Harga: Rp " << t->harga_transaksi << ") pushed ke riwayat." << endl;
    }
}

Transaksi pop(){
    if(top < 0){
        cout << "Stack underflow! Tidak ada transaksi untuk dibatalkan." << endl;
        return {"", "", -1, ""};
    } else{
        Transaksi value = stack[top];
        top--;
        cout << "Transaksi terakhir (" << value.nama_penumpang << ", Rute: " << value.rute_kereta << ") dihapus dari riwayat." << endl;
        return value;
    }
}

int peek_stack(){
    if(top < 0){
        cout << "Stack is empty. Tidak ada transaksi terakhir." << endl;
        return -1;
    } else{
        cout << "Transaksi terakhir di riwayat: " << stack[top].nama_penumpang << " (Rute: " << stack[top].rute_kereta << ", Harga: Rp " << stack[top].harga_transaksi << ")" << endl;
        return 0; // Atau return stack[top];
    }
}

void display_stack(){
    if(isStackEmpty()){
        cout << "Stack is empty." << endl;
        return;
    }
    cout << "Isi Riwayat Transaksi (Top -> Bottom): " << endl;
    // Gunakan pointer arithmetic untuk iterasi array stack
    Transaksi* base_ptr = stack; // Pointer dasar ke array stack
    // Loop mundur dari top ke 0
    for(int i = top; i >= 0; i--){
        Transaksi* current_ptr = base_ptr + i; // Hitung alamat elemen ke-i
        cout << "Indeks " << i << ": Nama: " << current_ptr->nama_penumpang << ", Rute: " << current_ptr->rute_kereta << ", Harga: Rp " << current_ptr->harga_transaksi << ", Waktu: " << current_ptr->waktu_transaksi << endl;
    }
    cout << endl;
}

// --- Fung dari kode sebelumnya ---
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

void tambahKereta(Kereta* arr, int& n) {
    if (n >= maxKereta) {
        cout << "Kapasitas kereta penuh!" << endl;
        return;
    }

    cout << "\n>>> TAMBAH DATA KERETA BARU <<<" << endl;
    cout << "Masukkan nomor kereta: ";
    getline(cin, (arr + n)->no_kereta);
    cout << "Masukkan nama kereta: ";
    getline(cin, (arr + n)->nama_kereta);
    cout << "Masukkan rute asal: ";
    getline(cin, (arr + n)->rute_asal);
    cout << "Masukkan rute tujuan: ";
    getline(cin, (arr + n)->rute_tujuan);
    
    // Validasi Input Harga
    string input_harga;
    int harga_tiket_temp;
    bool valid = false;

    while (!valid) {
        cout << "Masukkan harga tiket: ";
        getline(cin, input_harga);

        try {
            // Coba ubah string ke integer
            size_t pos;
            harga_tiket_temp = stoi(input_harga, &pos);
            // stoi akan gagal jika ada karakter non-digit di akhir
            if (pos != input_harga.length()) {
                throw invalid_argument("Input mengandung karakter non-digit.");
            }
            if (harga_tiket_temp < 0) {
                cout << "Harga tidak boleh negatif. Silakan coba lagi." << endl;
                continue;
            }
            valid = true; // Jika tidak ada exception, input valid
        } catch (const invalid_argument& e) {
            cout << "Input tidak valid! Harap masukkan angka saja." << endl;
        } catch (const out_of_range& e) {
            cout << "Input terlalu besar! Harap masukkan angka yang lebih kecil." << endl;
        }
    }
    (arr + n)->harga_tiket = harga_tiket_temp;
    // Akhir Bagian Validasi

    cout << "Maskat: ";
    getline(cin, (arr + n)->waktu_berangkat);

    n++;
    cout << "Data kereta berhasil ditambahkan!" << endl;
}

int linearSearch(Kereta* arr, int n, string rute) {
    cout << "Proses Linear Search:\n";
    for (int i = 0; i < n; i++) {
        string full_rute = (arr + i)->rute_asal + " - " + (arr + i)->rute_tujuan;
        cout << "Iterasi " << i+1 << ": Cek indeks " << i << ", Rute: '" << full_rute << "' ?= '" << rute << "'" << endl;
        if (full_rute == rute) {
            cout << " -> Rute ditemukan di indeks " << i << endl;
            return i;
        }
        cout << " -> Tidak cocok.\n";
    }
    cout << " -> Rute tidak ditemukan setelah " << n << " iterasi.\n";
    return -1;
}

int jumpSearch(Kereta* arr, int n, string no_kereta) {
    int step = static_cast<int>(sqrt(n));
    int prev = 0;

    cout << "Proses Jump Search (mengasumsikan array sudah terurut):\n";
    while (prev < n && (arr + prev)->no_kereta < no_kereta) {
        cout << "Melompat ke indeks ~" << prev << ", No Kereta: " << (arr + prev)->no_kereta << endl;
        int next_step = prev + step;
        if (next_step < n && (arr + next_step - 1)->no_kereta < no_kereta) {
            prev = next_step;
        } else {
            cout << "Berhenti lompat, masuk pencarian linear dari indeks " << prev << endl;
            break;
        }
    }

    int batas = min(prev + step, n);
    for (int i = prev; i < batas; i++) {
        cout << "Pencarian linear di indeks " << i << ", No Kereta: " << (arr + i)->no_kereta << endl;
        if ((arr + i)->no_kereta == no_kereta) {
            cout << " -> Nomor kereta ditemukan di indeks " << i << endl;
            return i;
        }
    }

    cout << " -> Nomor kereta tidak ditemukan dalam blok.\n";
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

// Fungsi swap menggunakan dereferensi pointer
void swapKereta(Kereta* a, Kereta* b) {
    Kereta temp = *a; // Dereferensi a
    *a = *b;          // Dereferensi a dan b
    *b = temp;        // Dereferensi b
}

void selectionSort(Kereta* arr, int n) {
    cout << "Proses Selection Tiket Termurah ke Termahal):\n";
    tampilJadwal(arr, n);
    cout << "\nMulai Sorting...\n";

    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        cout << "\nIterasi " << i + 1 << ": Mencari nilai minimum dari indeks " << i << " ke " << n - 1 << endl;
        for (int j = i + 1; j < n; j++) {
            if ((arr + j)->harga_tiket < (arr + min_idx)->harga_tiket) {
                min_idx = j;
                cout << " -> Harga di indeks " << j << " (" << (arr + j)->harga_tiket << ") lebih kecil dari minimum saat ini." << endl;
            }
        }
        if (min_idx != i) {
            cout << " -> Menukar elemen di indeks " << i << " dan " << min_idx << "." << endl;
            swapKereta((arr + i), (arr + min_idx)); // Gunakan fungsi swap dengan dereferensi
        } else {
            cout << " -> Elemen di indeks " << i << " sudah merupakan yang terkecil, tidak perlu ditukar." << endl;
        }
        cout << " -> Status array setelah iterasi " << i + 1 << ":\n";
        tampilJadwal(arr, n);
    }
    cout << "\nSorting Selesai!\n";
}

int main() {
    // contoh data
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
        cout << "4) jump Search cari berdasarkan nomor kereta" << endl;
        cout << "5) Merge sort urutkan berdasarkan nama kereta (A-Z)" << endl;
        cout << "6) Selection Sort urutkan berdasarkan harga tiket (termurah)" << endl;
        cout << "7) Tambah Penumpang ke Antrian Pembelian Tiket (Queue)" << endl;
        cout << "8) Proses Tiket (Dequeue)" << endl;
        cout << "9) Riwayat Transaksi (Stack)" << endl;
        cout << "10) Batalkan Transaksi Terakhir (Pop)" << endl;
        cout << "11) Riwayat Terakhir (Peek)" << endl;
        cout << "12) Tampil semua antrian" << endl;
        cout << "13) Tampil semua riwayat" << endl;
        cout << "0) Keluar Program" << endl;
        cout << "-------------------------------------------------------------------------------" << endl;
        cout << "Masukan Pilihan: ";
        getline(cin, pilihan);

        if(pilihan == "1") {
            cls();
            tampilJadwal(kereta, jumlah_kereta);
            pause();
        } else if(pilihan == "2") {
            cls();
            tambahKereta(kereta, jumlah_kereta);
            pause();
        } else if(pilihan == "3") {
            string ruteCari;
            cls();
            cout << ">>> Linear Search <<<" << endl;
            cout << "Masukkan rute (asal & tujuan) dengan format 'Asal - Tujuan' (contoh: Jakarta - Surabaya): ";
            getline(cin, ruteCari);

            int indexLinear;
            indexLinear = linearSearch(kereta, jumlah_kereta, ruteCari);
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
            string noKeretaCari;
            cls();
            cout << ">>> Jump Search <<<" << endl;
            cout << "Masukkan nomor kereta: ";
            getline(cin, noKeretaCari);

            int indexJump;
            mergeSortByNumber(kereta, 0, jumlah_kereta - 1);
            cout << "(Array diurutkan berdasarkan No. Kereta untuk pencarian)\n";

            indexJump = jumpSearch(kereta, jumlah_kereta, noKeretaCari);
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
            cout << ">>> Marge Sort <<<" << endl;
            tampilJadwal(kereta, jumlah_kereta);
            mergeSortByName(kereta, 0, jumlah_kereta - 1);
            cout << "\nData setelah diurutkan (Merge Sort - Nama Kereta A-Z):\n";
            tampilJadwal(kereta, jumlah_kereta);
            pause();
        } else if(pilihan == "6") {
            cls();
            cout << ">>> Selection Sort <<<" << endl;
            cout << "Data sebelum diurutkan (Selection Sort - Harga Tiket):\n";
            tampilJadwal(kereta, jumlah_kereta);
            selectionSort(kereta, jumlah_kereta);
            cout << "\nData setelah diurutkan (Selection Sort - Harga Tiket Termurah):\n";
            tampilJadwal(kereta, jumlah_kereta);
            pause();
        } else if(pilihan == "7") { // Enqueue
            cls();
            if (jumlah_kereta == 0) {
                cout << "Belum ada data kereta. Tidak bisa memesan tiket." << endl;
            } else {
                string nama, rute;
                cout << ">>> Tambah Penumpang ke Antrian <<<" << endl;
                cout << "Masukkan nama penumpang: ";
                getline(cin, nama);
                cout << "Daftar Rute Tersedia:" << endl;
                for (int i = 0; i < jumlah_kereta; i++) {
                    cout << "- " << (kereta + i)->rute_asal << " - " << (kereta + i)->rute_tujuan << endl;
                }
                cout << "Masukkan rute yang dipilih (format: Asal - Tujuan): ";
                getline(cin, rute);

                // Cari harga tiket untuk rute yang dipilih
                int harga_pesanan = -1;
                for (int i = 0; i < jumlah_kereta; i++) {
                    if ((kereta + i)->rute_asal + " - " + (kereta + i)->rute_tujuan == rute) {
                        harga_pesanan = (kereta + i)->harga_tiket;
                        break;
                    }
                }

                if (harga_pesanan != -1) {
                    Penumpang p_baru = {nama, rute, harga_pesanan};
                    enqueue(&p_baru); // Kirim pointer ke struct
                } else {
                    cout << "Rute tidak ditemukan dalam daftar kereta!" << endl;
                }
            }
            pause();
        } else if(pilihan == "8") { // Dequeue dan Push ke Stack
            cls();
            Penumpang p_diproses = dequeue();
            if (p_diproses.nama_penumpang != "") { // Jika dequeue berhasil
                 // Simulasikan penambahan ke riwayat transaksi
                 Transaksi t_baru = {p_diproses.nama_penumpang, p_diproses.rute_yang_dipilih, p_diproses.harga_tiket_pesanan, "2026-04-06 15:00"}; // Waktu simulasikan
                 push(&t_baru); // Kirim pointer ke struct
            }
            pause();
        } else if(pilihan == "9") { // Tampil Stack
            cls();
            display_stack();
            pause();
        } else if(pilihan == "10") { // Pop Stack
            cls();
            pop(); // Fungsi pop untuk stack
            pause();
        } else if(pilihan == "11") { // Peek Stack
            cls();
            peek_stack(); // Fungsi peek untuk stack
            pause();
        } else if(pilihan == "12") { // Tampil Queue
            cls();
            display_queue();
            pause();
        } else if(pilihan == "13") { // Tampil Stack (sudah ada di 9)
            cls();
            display_stack();
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