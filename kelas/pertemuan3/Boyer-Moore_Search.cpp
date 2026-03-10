#include <iostream>
#include <string>
using namespace std;

// Ukuran alfabet (semua karakter ASCII)
#define ALFABET 256

// -------------------------------------------------------
// Buat tabel Bad Character
// Isi tabel: indeks terakhir tiap karakter dalam pattern
// Karakter yang tidak ada di pattern → bernilai -1
// -------------------------------------------------------
void buatTabelBadChar(string &pattern, int m, int tabel[]) {

    // Set semua ke -1 dulu
    for (int i = 0; i < ALFABET; i++)
        tabel[i] = -1;

    // Isi indeks terakhir tiap karakter pattern
    for (int i = 0; i < m; i++)
        tabel[(int)pattern[i]] = i;
}

// -------------------------------------------------------
// Fungsi Boyer-Moore Search
// text : teks yang dicari
// pattern : pola yang ingin ditemukan
// -------------------------------------------------------
void boyerMoore(string &text, string &pattern) {

    int n = (int)text.size();
    int m = (int)pattern.size();

    // Buat tabel bad character
    int badChar[ALFABET];
    buatTabelBadChar(pattern, m, badChar);

    int s = 0; // posisi geser pattern terhadap text
    bool ketemu = false;

    while (s <= n - m) {

        int j = m - 1; // mulai dari karakter paling kanan pattern

        // Cocokkan dari kanan ke kiri
        while (j >= 0 && pattern[j] == text[s + j])
            j--;

        if (j < 0) {
            // Semua karakter cocok → KETEMU
            cout << "Pattern ditemukan di posisi: " << s << endl;
            ketemu = true;

            // Hitung geser berikutnya
            if (s + m < n)
                s += m - badChar[(int)text[s + m]];
            else
                s++;
        }
        else {
            // Ada ketidakcocokan → pakai bad character rule
            int geser = j - badChar[(int)text[s + j]];
            if (geser < 1) 
                geser = 1;

            s += geser;
        }
    }

    if (!ketemu)
        cout << "Pattern tidak ditemukan." << endl;
}

int main() {

    string text, pattern;

    cout << "Masukkan teks : ";
    getline(cin, text);

    cout << "Masukkan pattern : ";
    getline(cin, pattern);

    boyerMoore(text, pattern);

    return 0;
}