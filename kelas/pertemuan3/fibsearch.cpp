#include <iostream>
using namespace std;

// Fungsi Fibonacci Search
// arr : pointer ke array
// n : jumlah elemen
// target : nilai yang dicari
// return : indeks jika ketemu, -1 jika tidak

int fibonacciSearch(int *arr, int n, int target) {

    // Tiga variabel Fibonacci berturut-turut
    int fib2 = 0; // F(k-2)
    int fib1 = 1; // F(k-1)
    int fib = 1;  // F(k)

    // Naikkan Fibonacci sampai >= n
    while (fib < n) {
        fib2 = fib1;
        fib1 = fib;
        fib = fib1 + fib2;
    }

    int offset = -1; // batas kiri yang sudah dieliminasi

    while (fib > 1) {

        // Tentukan indeks yang akan diperiksa
        int i = offset + fib2;
        if (i >= n)
            i = n - 1;

        if (arr[i] == target)
            return i;

        else if (arr[i] < target) {
            // Cari di sebelah kanan
            fib = fib1;
            fib1 = fib2;
            fib2 = fib - fib1;
            offset = i;
        } 
        else {
            // Cari di sebelah kiri
            fib = fib2;
            fib1 = fib1 - fib2;
            fib2 = fib - fib1;
        }
    }

    // Periksa satu elemen tersisa
    if (fib1 == 1 && arr[offset + 1] == target)
        return offset + 1;

    return -1;
}

int main() {

    int arr[] = {10, 22, 35, 40, 45, 50, 80, 82, 85, 90, 100};
    int n = 11;
    int target;

    cout << "Array: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;

    cout << "Masukkan nilai yang dicari: ";
    cin >> target;

    int hasil = fibonacciSearch(arr, n, target);

    if (hasil != -1)
        cout << "Ditemukan di indeks " << hasil << endl;
    else
        cout << "Tidak ditemukan." << endl;

    return 0;
}