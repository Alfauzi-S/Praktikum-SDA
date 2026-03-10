#include <iostream>
#include <cmath> // untuk sqrt()
using namespace std;

// Fungsi Jump Search
// arr : pointer ke array terurut
// n : jumlah elemen
// target : nilai yang dicari

int jumpSearch(int *arr, int n, int target) {

    int step = (int)sqrt((double)n); // ukuran satu lompatan
    int prev = 0; // awal blok saat ini

    // === FASE 1: LOMPAT antar blok ===
    // Lompat selama ujung blok masih < target
    while (arr[step - 1] < target) {
        prev = step;
        step += (int)sqrt((double)n);

        if (prev >= n)
            return -1; // sudah melewati semua elemen
    }

    // === FASE 2: LINEAR SEARCH dalam blok ===
    // Cari satu per satu dari prev sampai ujung blok
    int batas = step;
    if (batas > n)
        batas = n; // jangan lewati akhir array

    while (prev < batas) {
        if (arr[prev] == target)
            return prev; // KETEMU
        prev++;
    }

    return -1; // TIDAK KETEMU
}

int main() {

    int arr[] = {1, 3, 5, 7, 9, 11, 19, 25, 30, 36, 50};
    int n = 11;
    int target;

    cout << "Array: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;

    cout << "Masukkan nilai yang dicari: ";
    cin >> target;

    int hasil = jumpSearch(arr, n, target);

    if (hasil != -1)
        cout << "Ditemukan di indeks " << hasil << endl;
    else
        cout << "Tidak ditemukan." << endl;

    return 0;
}