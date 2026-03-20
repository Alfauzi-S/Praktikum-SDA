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

# define maxKereta 100
Kereta kereta[maxKereta];
int jumlah_kereta = 0;

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

    cout << "Masukkan waktu berangkat: ";
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

// iterasi Linear Search:
// 1. Mulai dari indeks pertama (i = 0) dari array.
// 2. Di setiap iterasi, bandingkan 'full_rute' dari elemen saat ini (arr + i) dengan 'rute' yang dicari.
//    'full_rute' didapatkan dengan menggabungkan 'rute_asal' dan 'rute_tujuan' dengan format "asal - tujuan".
// 3. Jika 'full_rute' cocok dengan 'rute' yang dicari, kembalikan indeks 'i' saat ini dan hentikan pencarian.
// 4. Jika tidak cocok, lanjutkan ke elemen berikutnya (i++) dan ulangi langkah 2.
// 5. Jika iterasi selesai (i == n) dan tidak ada kecocokan, kembalikan nilai -1 untuk menandakan tidak ditemukan.

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

// iterasi Jump Search:
// 1. Hitung ukuran lompatan (step) sebagai akar dari jumlah elemen (sqrt(n)).
// 2. Mulai dari indeks 0, lompat sejauh 'step' selama nilai elemen di indeks 'prev' < nilai yang dicari.
// 3. Jika lompatan berikutnya masih kurang dari n dan elemen terakhir dari blok lompatan < nilai yang dicari, maka lakukan lompatan berikutnya.
// 4. Jika tidak, hentikan lompatan dan mulai pencarian linear dari indeks 'prev'.
// 5. Lakukan pencarian linear dalam blok yang telah ditentukan hingga ditemukan atau habis.
// 6. Jika ditemukan, kembalikan indeksnya. Jika tidak, kembalikan -1.

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

// iterasi Merge Sort (mergeByNumber dan mergeSortByNumber):
// Merge Sort bekerja dengan pendekatan divide-and-conquer (pecah dan taklukkan).
// 1. Fungsi mergeSortByNumber membagi array menjadi dua bagian (kiri dan kanan) secara rekursif.
// 2. Pembagian terus berlanjut hingga tinggal satu elemen atau tidak ada elemen.
// 3. Fungsi mergeByNumber kemudian menggabungkan dua sub-array yang sudah terurut menjadi satu array yang terurut.
// 4. Proses penggabungan membandingkan elemen-elemen dari dua array dan menempatkannya secara berurutan.
// 5. Proses ini terus-menerus mengembalikan array yang semakin terurut hingga seluruh array terurut.

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

// iterasi Merge Sort (mergeName dan mergeSortByName):
// Merge Sort bekerja dengan pendekatan divide-and-conquer (pecah dan taklukkan).
// 1. Fungsi mergeSortByName membagi array menjadi dua bagian (kiri dan kanan) secara rekursif.
// 2. Pembagian terus berlanjut hingga tinggal satu elemen atau tidak ada elemen.
// 3. Fungsi mergeName kemudian menggabungkan dua sub-array yang sudah terurut menjadi satu array yang terurut.
// 4. Proses penggabungan membandingkan elemen-elemen dari dua array dan menempatkannya secara berurutan berdasarkan nama kereta.
// 5. Proses ini terus-menerus mengembalikan array yang semakin terurut hingga seluruh array terurut berdasarkan nama kereta (A-Z).

void selectionSort(Kereta* arr, int n) {
    cout << "Proses Selection Sort (Harga Tiket Termurah ke Termahal):\n";
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
            Kereta temp = *(arr + min_idx);
            *(arr + min_idx) = *(arr + i);
            *(arr + i) = temp;
        } else {
            cout << " -> Elemen di indeks " << i << " sudah merupakan yang terkecil, tidak perlu ditukar." << endl;
        }
        cout << " -> Status array setelah iterasi " << i + 1 << ":\n";
        tampilJadwal(arr, n);
    }
    cout << "\nSorting Selesai!\n";
}

// iterasi Selection Sort:
// 1. Loop utama (i) berjalan dari indeks 0 hingga n-2.
// 2. Untuk setiap indeks i, asumsikan elemen di indeks i adalah nilai minimum (min_idx = i).
// 3. Loop dalam (j) memeriksa semua elemen dari i+1 hingga n-1.
// 4. Jika ditemukan elemen di indeks j yang lebih kecil dari elemen di indeks min_idx, perbarui min_idx.
// 5. Setelah loop dalam selesai, jika min_idx != i, maka tukar elemen di indeks i dan min_idx.
// 6. Proses ini berulang hingga semua elemen terurut.

int main()
{
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
            cout << ">>> Selection Sortt <<<" << endl;
            cout << "Data sebelum diurutkan (Selection Sort - Harga Tiket):\n";
            tampilJadwal(kereta, jumlah_kereta);
            selectionSort(kereta, jumlah_kereta);
            cout << "\nData setelah diurutkan (Selection Sort - Harga Tiket Termurah):\n";
            tampilJadwal(kereta, jumlah_kereta);
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