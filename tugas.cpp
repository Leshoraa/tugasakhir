#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>
#include <string>

// Syntax perbedaan perintah sistem antara Windows dan Linux
#ifdef _WIN32
#include <windows.h>
void sleep_seconds(int seconds) { Sleep(seconds * 1000); }
#else
#include <unistd.h>
void sleep_seconds(int seconds) { sleep(seconds); }
#endif

// Helper untuk to_string jika compiler tidak support C++11
template <typename T> std::string to_string_custom(const T &value) {
  std::stringstream ss;
  ss << value;
  return ss.str();
}

using namespace std;

int main() {
  srand(time(0));
  string nama;
  int level = 0;
  int kategori = 0;
  int score = 0;
  bool running = true;

  // Input nama pemain
  cout << "Masukkan Nama: ";
  cin >> nama;

  while (running) {
    // --- Menu Pemilihan Level ---
    cout << "Pilih Level:\n1. Easy\n2. Medium\n3. Hard\n";
    cin >> level;
    cout << "exp " << level << endl;
    sleep_seconds(1);
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    bool selectingCategory = true;
    while (selectingCategory) {
      // --- Menu Pemilihan Kategori ---
      cout << "Pilih Kategori:\n1. Bilangan\n2. Buah\n3. Hewan\n";
      cin >> kategori;
      cout << "exp " << kategori << endl;
      sleep(1);
#ifdef _WIN32
      system("cls");
#else
      system("clear");
#endif

      bool playing = true;
      while (playing) {
        int jumlahItem = 0;
        int numbers[50];
        string words[50];

        // Array kategori Buah dan Hewan
        string buahBank[] = {"Apel",   "Jeruk",    "Mangga",   "Pisang",
                             "Anggur", "Nanas",    "Semangka", "Melon",
                             "Durian", "Rambutan", "Salak",    "Pepaya",
                             "Jambu",  "Leci",     "Kelapa"};
        string hewanBank[] = {"Kucing", "Anjing",  "Ayam",  "Bebek",
                              "Sapi",   "Kambing", "Kuda",  "Gajah",
                              "Singa",  "Macan",   "Ular",  "Burung",
                              "Ikan",   "Kelinci", "Monyet"};

        // Menentukan jumlah item berdasarkan level kesulitan
        if (level == 1)
          jumlahItem = 6;
        else if (level == 2)
          jumlahItem = 9;
        else if (level == 3)
          jumlahItem = 10;

        cout << "Level: " << level << " | Score: " << score << endl;
        cout << "Hafalkan urutan berikut!" << endl << endl;

        // Generate item acak (angka atau kata) sesuai kategori
        for (int i = 0; i < jumlahItem; i++) {
          if (kategori == 1) {
            if (level == 1)
              numbers[i] = rand() % 10 + 1;
            else if (level == 2)
              numbers[i] = rand() % 900 + 10;
            else
              numbers[i] = rand() % 9000 + 1000;
          } else if (kategori == 2) {
            words[i] = buahBank[rand() % 15];
          } else {
            words[i] = hewanBank[rand() % 15];
          }
        }
\
        // Level 1: Tampil vertikal satu per satu
        if (level == 1) {
          for (int i = 0; i < jumlahItem; i++) {
            if (kategori == 1)
              cout << numbers[i] << endl;
            else
              cout << words[i] << endl;
          }
          // Level 2: Tampil grid (3 kolom)
        } else if (level == 2) {
          int cols = 3;
          for (int i = 0; i < jumlahItem; i++) {
            if (kategori == 1)
              cout << numbers[i] << " ";
            else
              cout << words[i] << " ";

            if ((i + 1) % cols == 0)
              cout << endl;
          }
          // Level 3: Tampil pola segitiga terbalik
        } else if (level == 3) {
          int currentLine = 0;
          int itemsInLine = 4;
          int printedInLine = 0;

          for (int i = 0; i < jumlahItem; i++) {
            if (kategori == 1)
              cout << numbers[i] << " ";
            else
              cout << words[i] << " ";

            printedInLine++;
            if (printedInLine == itemsInLine) {
              cout << endl;
              itemsInLine--;
              printedInLine = 0;
            }
          }
          cout << endl;
        }

        sleep_seconds(5);
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        // --- Logika Input dan Validasi ---
        cout << "Masukkan input sesuai urutan sebelumnya:" << endl;
        bool benar = true;

        if (kategori == 1) {
          string expected = "";
          for (int i = 0; i < jumlahItem; i++) {
            expected += to_string_custom(numbers[i]);
          }

          string input;
          cin >> ws;
          getline(cin, input);
          input.erase(remove(input.begin(), input.end(), ' '), input.end());

          if (input != expected) {
            benar = false;
          }
        } else {
          string expected = "";
          for (int i = 0; i < jumlahItem; i++) {
            expected += words[i];
          }

          string input;
          cin >> ws;
          getline(cin, input);
          input.erase(remove(input.begin(), input.end(), ' '), input.end());

          transform(expected.begin(), expected.end(), expected.begin(),
                    ::tolower);
          transform(input.begin(), input.end(), input.begin(), ::tolower);

          if (input != expected) {
            benar = false;
          }
        }

        // Cek jawaban dan update skor
        if (benar) {
          score += 10;
          cout << "Benar! Point anda: " << score << endl;

          // Menu navigasi setelah menyelesaikan level
          cout << "Menu:\n";
          if (level < 3)
            cout << "1. Next Level\n";
          if (level > 1)
            cout << "2. Previous Level\n";
          cout << "3. Ulangi Level Ini\n";
          cout << "4. Ganti Mode (Kategori)\n";
          cout << "5. Kembali ke Menu Awal (Level)\n";
          cout << "6. Keluar\n";

          int menu;
          cin >> menu;

          if (menu == 1 && level < 3)
            level++;
          else if (menu == 2 && level > 1)
            level--;
          else if (menu == 4) {
            playing = false;
          } else if (menu == 5) {
            playing = false;
            selectingCategory = false;
          } else if (menu == 6) {
            playing = false;
            selectingCategory = false;
            running = false;
          }

        } else {
          score -= 5;
          cout << "Salah!" << endl;
          cout << "Jawaban yang benar:" << endl;
          for (int i = 0; i < jumlahItem; i++) {
            if (kategori == 1)
              cout << numbers[i] << " ";
            else
              cout << words[i] << " ";
          }
          cout << endl;
          cout << "Point anda sekarang: " << score << endl;

          if (score < 0) {
            cout << "Game Over! Point tidak cukup untuk melanjutkan" << endl;
            playing = false;
            selectingCategory = false;
            running = false;
          } else {
            cout << "Menu:\n";
            cout << "1. Ulangi Level Ini\n";
            cout << "2. Ganti Mode (Kategori)\n";
            cout << "3. Kembali ke Menu Awal (Level)\n";
            cout << "4. Keluar\n";

            int menu;
            cin >> menu;
            if (menu == 2) {
              playing = false;
            } else if (menu == 3) {
              playing = false;
              selectingCategory = false;
            } else if (menu == 4) {
              playing = false;
              selectingCategory = false;
              running = false;
            }
          }
        }

        if (playing) {
#ifdef _WIN32
          system("cls");
#else
          system("clear");
#endif
        }
      }
      if (!running)
        break;
    }
    if (!running)
      break;
  }

  return 0;
}
