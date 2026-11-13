#include <iostream>
#include <string>
using namespace std;

const int TABLE_SIZE = 20;

enum SlotStatus { EMPTY, OCCUPIED, DELETED };

struct Slot {
    int    nim;
    string nama;
    SlotStatus status;

    Slot() : nim(0), nama(""), status(EMPTY) {}
};

struct HashTable {
    Slot table[TABLE_SIZE];

    // ---- Fungsi Hash ----
    int hash1(int key) { return key % TABLE_SIZE; }
    int hash2(int key) { return 19 - (key % 19); }

    // ---- INSERT ----
    bool insert(int nim, const string& nama) {
        int idx    = hash1(nim);
        int step   = hash2(nim);
        int probes = 0;

        cout << "  [INSERT] NIM=" << nim << " | H1=" << idx << " | H2=" << step << "\n";

        while (probes < TABLE_SIZE) {
            if (table[idx].status == EMPTY || table[idx].status == DELETED) {
                table[idx].nim    = nim;
                table[idx].nama   = nama;
                table[idx].status = OCCUPIED;
                cout << "    -> Ditempatkan di indeks " << idx << "\n";
                return true;
            }
            if (table[idx].status == OCCUPIED && table[idx].nim == nim) {
                cout << "    -> NIM " << nim << " sudah ada (duplikat), insert dibatalkan.\n";
                return false;
            }
            cout << "    -> Collision di indeks " << idx
                 << " (ada NIM " << table[idx].nim << "), probe ke-" << (probes+1) << "\n";
            idx = (idx + step) % TABLE_SIZE;
            probes++;
        }

        cout << "    -> Tabel penuh! Insert gagal.\n";
        return false;
    }

    // ---- SEARCH ----
    int search(int nim) {
        int idx    = hash1(nim);
        int step   = hash2(nim);
        int probes = 0;

        while (probes < TABLE_SIZE) {
            if (table[idx].status == EMPTY) return -1;
            if (table[idx].status == OCCUPIED && table[idx].nim == nim) return idx;
            idx = (idx + step) % TABLE_SIZE;
            probes++;
        }
        return -1;
    }

    // ---- REMOVE ----
    bool remove(int nim) {
        int idx = search(nim);
        if (idx == -1) {
            cout << "  [REMOVE] NIM " << nim << " tidak ditemukan.\n";
            return false;
        }
        cout << "  [REMOVE] NIM " << nim << " (" << table[idx].nama
             << ") dihapus dari indeks " << idx << ".\n";
        table[idx].status = DELETED;
        return true;
    }

    // ---- DISPLAY ----
    void display() {
        cout << "\n  Hash Table (Ukuran " << TABLE_SIZE << "):\n";
        cout << "  " << string(45, '-') << "\n";
        cout << "  Indeks | NIM        | Nama               | Status\n";
        cout << "  " << string(45, '-') << "\n";
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << "  ";
            cout.width(6); cout << i;
            cout << " | ";
            if (table[i].status == OCCUPIED) {
                cout.width(10); cout << table[i].nim;
                cout << " | ";
                cout.width(18); cout << table[i].nama;
                cout << " | OCCUPIED\n";
            } else if (table[i].status == DELETED) {
                cout.width(10); cout << "-";
                cout << " | ";
                cout.width(18); cout << "[DELETED]";
                cout << " | DELETED\n";
            } else {
                cout.width(10); cout << "-";
                cout << " | ";
                cout.width(18); cout << "-";
                cout << " | EMPTY\n";
            }
        }
        cout << "  " << string(45, '-') << "\n";
    }
};

int main() {
    HashTable ht;

    cout << "=== SISTEM HASH TABLE MAHASISWA (DOUBLE HASHING) ===\n\n";
    cout << "Formula:\n";
    cout << "  Hash1(key) = key % 20\n";
    cout << "  Hash2(key) = 19 - (key % 19)\n\n";

    // Data uji: 15 mahasiswa mencakup kondisi collision
    // NIM dipilih agar ada yang hasil hash1-nya sama (collision)
    struct DataUji { int nim; const char* nama; };
    DataUji data[] = {
        {12001, "Andi Saputra"},
        {12021, "Budi Pratama"},   // 12001 % 20 = 1, 12021 % 20 = 1 → collision
        {12041, "Citra Dewi"},     // juga berakhir di kelompok yang sama
        {12002, "Dian Rahayu"},
        {12003, "Eko Susanto"},
        {12004, "Fitri Lestari"},
        {12005, "Gilang Ramadhan"},
        {12006, "Hana Permata"},
        {12007, "Ivan Kurniawan"},
        {12008, "Joko Widodo"},
        {12009, "Kiran Sari"},
        {12010, "Lina Marlina"},
        {12061, "Mira Kesuma"},    // 12061 % 20 = 1 → collision lagi
        {12011, "Naufal Hakim"},
        {12012, "Oriza Panggabean"},
    };

    cout << "--- Memasukkan 15 Data Mahasiswa ---\n";
    for (auto& d : data)
        ht.insert(d.nim, d.nama);

    ht.display();

    // Uji penghapusan
    cout << "\n--- Pengujian Penghapusan ---\n";
    ht.remove(12003);
    ht.remove(99999);  // tidak ada

    // Insert setelah delete (slot DELETED harus bisa dipakai lagi)
    cout << "\n--- Insert Baru Setelah Penghapusan ---\n";
    ht.insert(12013, "Putra Ramadhan");

    ht.display();

    // Menu interaktif
    int pilihan;
    do {
        cout << "\n========= MENU =========\n";
        cout << "1. Insert mahasiswa baru\n";
        cout << "2. Search mahasiswa berdasarkan NIM\n";
        cout << "3. Remove mahasiswa berdasarkan NIM\n";
        cout << "4. Tampilkan seluruh tabel\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            int nim; string nama;
            cout << "NIM  : "; cin >> nim; cin.ignore();
            cout << "Nama : "; getline(cin, nama);
            ht.insert(nim, nama);

        } else if (pilihan == 2) {
            int nim;
            cout << "NIM yang dicari: "; cin >> nim; cin.ignore();
            int idx = ht.search(nim);
            if (idx != -1)
                cout << "  Ditemukan di indeks " << idx
                     << " | Nama: " << ht.table[idx].nama << "\n";
            else
                cout << "  NIM " << nim << " tidak ditemukan.\n";

        } else if (pilihan == 3) {
            int nim;
            cout << "NIM yang dihapus: "; cin >> nim; cin.ignore();
            ht.remove(nim);

        } else if (pilihan == 4) {
            ht.display();
        }

    } while (pilihan != 0);

    cout << "\nProgram selesai. Terima kasih!\n";
    return 0;
}