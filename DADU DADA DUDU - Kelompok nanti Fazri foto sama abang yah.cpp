#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

struct Pemain {
    string nama;
    int totalSkor;
    int selisih;
    int skorTieBreak = 0;
};

// Fungsi random sederhana pengganti rand()
int lemparDadu(int &seed) {
    seed = (seed * 1103515245 + 12345) & 0x7fffffff;
    return (seed % 6) + 1;
}

// Sorting manual karena tidak pakai algorithm
void urutkanRanking(vector<Pemain> &pemain) {
    int n = pemain.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (pemain[i].selisih > pemain[j].selisih ||
                (pemain[i].selisih == pemain[j].selisih && pemain[i].skorTieBreak < pemain[j].skorTieBreak)) {
                swap(pemain[i], pemain[j]);
            }
        }
    }
}

int main() {
    int seed = 123456;
    char lanjut;

    do {
        int jumlahPemain, targetSkor;

        cout << "=============================================" << endl;
        cout << "Selamat Datang Di Game Dadu Kelompok Ya Ya Ya" << endl;
        cout << "=============================================" << endl;
        cout << "NOTE : Pemain Maksimal Berjumlah 5 Orang" << endl << endl;

        do {
            cout << "Masukkan jumlah pemain : ";
            cin >> jumlahPemain;
        } while (jumlahPemain < 1 || jumlahPemain > 5);

        do {
            cout << "Masukkan target skor : ";
            cin >> targetSkor;
        } while (targetSkor < 1 || targetSkor > 18);

        vector<Pemain> pemain(jumlahPemain);
        cin.ignore();
        for (int i = 0; i < jumlahPemain; i++) {
            cout << "Masukkan nama pemain ke-" << i+1 << ": ";
            getline(cin, pemain[i].nama);
            pemain[i].totalSkor = 0;
        }

        for (int putaran = 1; putaran <= 3; putaran++) {
            cout << "\nPutaran ke-" << putaran << endl;
            for (int i = 0; i < jumlahPemain; i++) {
                int lemparan = lemparDadu(seed);
                pemain[i].totalSkor += lemparan;
                cout << "Pemain " << pemain[i].nama
                     << " melempar: " << lemparan
                     << " | Total Skor: " << pemain[i].totalSkor << endl;
            }
        }

        for (int i = 0; i < jumlahPemain; i++) {
            pemain[i].selisih = abs(pemain[i].totalSkor - targetSkor);
        }

        int selisihTerbaik = pemain[0].selisih;
        for (int i = 1; i < jumlahPemain; i++) {
            if (pemain[i].selisih < selisihTerbaik)
                selisihTerbaik = pemain[i].selisih;
        }

        vector<int> kandidatTieBreak;
        for (int i = 0; i < jumlahPemain; i++) {
            if (pemain[i].selisih == selisihTerbaik)
                kandidatTieBreak.push_back(i);
        }

        if (kandidatTieBreak.size() > 1) {
            cout << "\n=============================================" << endl;
            cout << "Selamat datang di game tie breaker" << endl;
            cout << "=============================================" << endl;
            cout << "Peserta tie breaker:\n";
            for (int i = 0; i < kandidatTieBreak.size(); i++) {
                cout << i+1 << ". " << pemain[kandidatTieBreak[i]].nama << endl;
            }
            cout << "Tekan enter untuk melanjutkan...";
            cin.ignore();
            cin.get();

            for (int i = 0; i < kandidatTieBreak.size(); i++) {
                int idx = kandidatTieBreak[i];
                int lemparan = lemparDadu(seed);
                pemain[idx].skorTieBreak = lemparan;
                cout << pemain[idx].nama << " melempar: " << lemparan << endl;
            }
        }

        urutkanRanking(pemain);

        cout << "\nTampilan Akhir\n";
        cout << "Skor Target : " << targetSkor << endl;
        cout << "======================================================" << endl;
        cout << "| " << setw(7) << "Ranking" 
             << " | " << setw(10) << "Nama" 
             << " | " << setw(4) << "Skor" 
             << " | " << setw(12) << "Selisih Skor"
             << " | " << setw(12) << "Skor Tie Break" << " |" << endl;
        cout << "======================================================" << endl;

        for (int i = 0; i < jumlahPemain; i++) {
            cout << "| " << setw(7) << i+1 
                 << " | " << setw(10) << pemain[i].nama 
                 << " | " << setw(4) << pemain[i].totalSkor 
                 << " | " << setw(12) << pemain[i].selisih 
                 << " | " << setw(12) << pemain[i].skorTieBreak << " |" << endl;
        }
        cout << "======================================================" << endl;

        cout << "\nApakah ingin lanjut bermain (Y/T): ";
        cin >> lanjut;
        cin.ignore();

    } while (lanjut == 'Y' || lanjut == 'y');

    cout << "TERIMA KASIH SUDAH MENCOBA GAME KAMI!!!" << endl;
    return 0;
}
