#include <cstdlib> // Untuk rand() dan srand()
#include <iostream>
#include <unistd.h> // Untuk fungsi sleep

using namespace std;

// Fungsi membersihkan layar
void clearScreen() {
  #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif 
  }

// Fungsi jeda waktu
void sleepSeconds(int seconds) { sleep(seconds); }

// Fungsi pilih level (Validasi dengan Switch Case)
int pilihLevel() {
  char input;
  while (true) {
    cout << "Pilih Level:\n1. Easy\n2. Medium\n3. Hard\nMasukan: ";
    cin >> input;

    switch (input) {
    case '1':
      return 1;
    case '2':
      return 2;
    case '3':
      return 3;
    default:
      cout << "Input salah! Masukkan angka 1, 2, atau 3.\n";
    }
  }
}

// Fungsi pilih kategori (Validasi dengan Switch Case)
int pilihKategori() {
  char input;
  while (true) {
    cout << "Pilih Kategori:\n1. Bilangan\n2. Buah\n3. Hewan\nMasukan: ";
    cin >> input;

    switch (input) {
    case '1':
      return 1;
    case '2':
      return 2;
    case '3':
      return 3;
    default:
      cout << "Input salah! Masukkan angka 1, 2, atau 3.\n";
    }
  }
}

int main() {
  srand(getpid()); // Acak angka berdasarkan PID proses

  string nama;
  int score = 0;
  bool mainLagi = true;

  cout << "Masukkan Nama: ";
  cin >> nama;

  while (mainLagi) {
    clearScreen();
    int level = pilihLevel();
    int kategori = pilihKategori();

    int jumlahItem = (level == 1) ? 6 : (level == 2) ? 9 : 10;

    // Array statis
    int angka[10];
    string soalKata[10];

    // Bank data kata-kata
    string buah[] = {"Apel",   "Jeruk", "Mangga",  "Pisang",
                     "Anggur", "Nanas", "Semangka"};
    string hewan[] = {"Kucing", "Anjing",  "Ayam", "Bebek",
                      "Sapi",   "Kambing", "Kuda"};
    int jumlahBank = 7;

    // Generate Soal
    for (int i = 0; i < jumlahItem; i++) {
      if (kategori == 1) {
        int max = (level == 1) ? 10 : (level == 2) ? 100 : 1000;
        angka[i] = rand() % max + 1;
      } else {
        if (kategori == 2)
          soalKata[i] = buah[rand() % jumlahBank];
        else
          soalKata[i] = hewan[rand() % jumlahBank];
      }
    }

    // Tampilkan Soal
    clearScreen();
    cout << "Level: " << level << " | Score: " << score
         << "\nHafalkan ini!\n\n";

    for (int i = 0; i < jumlahItem; i++) {
      if (kategori == 1)
        cout << angka[i] << " ";
      else
        cout << soalKata[i] << " ";

      if ((i + 1) % 3 == 0)
        cout << endl;
    }
    cout << endl;

    sleepSeconds(5);
    clearScreen();

    // Input Jawaban
    cout << "Masukkan kembali urutannya (gabungkan tanpa spasi):\n";

    string kunciJawaban = "";
    string jawabanUser;

    // Buat Kunci Jawaban
    if (kategori == 1) {
      for (int i = 0; i < jumlahItem; i++) {
        kunciJawaban += to_string(angka[i]); // Gabung angka ke string
      }
    } else {
      for (int i = 0; i < jumlahItem; i++) {
        kunciJawaban += soalKata[i]; // Gabung kata
      }
    }

    cin >> ws; // Hapus whitespace
    cin >> jawabanUser;

    // Cek Jawaban (Case Insensitive Manual)
    bool benar = false;

    // Ubah semua ke huruf kecil untuk perbandingan
    string kunciKecil = "";
    string userKecil = "";

    for (int i = 0; i < kunciJawaban.length(); i++) {
      kunciKecil += tolower(kunciJawaban[i]);
    }
    for (int i = 0; i < jawabanUser.length(); i++) {
      userKecil += tolower(jawabanUser[i]);
    }

    if (kunciKecil == userKecil) {
      benar = true;
    }

    if (benar) {
      score += 10;
      cout << "\nBENAR! Score: " << score << endl;
    } else {
      score -= 5;
      cout << "\nSALAH! Score: " << score << endl;
      cout << "Jawaban: ";
      if (kategori == 1)
        for (int i = 0; i < jumlahItem; i++)
          cout << angka[i] << " ";
      else
        for (int i = 0; i < jumlahItem; i++)
          cout << soalKata[i] << " ";
      cout << endl;
    }

    if (score < 0) {
      cout << "\nGame Over! Score anda minus.\n";
      break;
    }

    cout << "\nLanjut main? (y/n): ";
    char lanjut;
    cin >> lanjut;
    if (lanjut == 'n' || lanjut == 'N')
      mainLagi = false;
  }

  return 0;
}
