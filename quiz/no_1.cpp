#include <iostream>
#include <string>
using namespace std;

struct Mahasiswa {
    string nim;
    string nama;
    int nilai;
    Mahasiswa* next;
};

struct LinkedList {
    Mahasiswa* head;
    int size;

    LinkedList() : head(nullptr), size(0) {}

    // Tambah mahasiswa ke akhir list
    void tambah(const string& nim, const string& nama, int nilai) {
        Mahasiswa* baru = new Mahasiswa{nim, nama, nilai, nullptr};
        if (head == nullptr) {
            head = baru;
        } else {
            Mahasiswa* curr = head;
            while (curr->next != nullptr)
                curr = curr->next;
            curr->next = baru;
        }
        size++;
    }

    // Tampilkan semua data mahasiswa
    void tampilkan() {
        if (head == nullptr) {
            cout << "  (Daftar kosong)\n";
            return;
        }
        cout << "  " << string(50, '-') << "\n";
        cout << "  " << left;
        cout.width(12); cout << "NIM";
        cout.width(20); cout << "Nama";
        cout.width(8);  cout << "Nilai" << "\n";
        cout << "  " << string(50, '-') << "\n";
        Mahasiswa* curr = head;
        while (curr != nullptr) {
            cout << "  ";
            cout.width(12); cout << curr->nim;
            cout.width(20); cout << curr->nama;
            cout.width(8);  cout << curr->nilai << "\n";
            curr = curr->next;
        }
        cout << "  " << string(50, '-') << "\n";
    }

    ~LinkedList() {
        Mahasiswa* curr = head;
        while (curr) {
            Mahasiswa* tmp = curr->next;
            delete curr;
            curr = tmp;
        }
    }
};

// dinamic array
struct DynamicArray {
    int* data;
    int capacity;
    int size;

    DynamicArray() : data(nullptr), capacity(0), size(0) {}

    void resize() {
        int newCap = (capacity == 0) ? 4 : capacity * 2;
        int* newData = new int[newCap];
        for (int i = 0; i < size; i++)
            newData[i] = data[i];
        delete[] data;
        data = newData;
        capacity = newCap;
    }

    void push(int val) {
        if (size == capacity) resize();
        data[size++] = val;
    }

    void tampilkan() {
        cout << "  [ ";
        for (int i = 0; i < size; i++) {
            cout << data[i];
            if (i < size - 1) cout << ", ";
        }
        cout << " ]\n";
    }

    ~DynamicArray() { delete[] data; }
};

// insertion sort
void insertionSort(DynamicArray& arr) {
    for (int i = 1; i < arr.size; i++) {
        int key = arr.data[i];
        int j = i - 1;
        while (j >= 0 && arr.data[j] > key) {
            arr.data[j + 1] = arr.data[j];
            j--;
        }
        arr.data[j + 1] = key;
    }
}

// linear search
Mahasiswa* linearSearch(LinkedList& list, const string& nim) {
    Mahasiswa* curr = list.head;
    while (curr != nullptr) {
        if (curr->nim == nim) return curr;
        curr = curr->next;
    }
    return nullptr;
}

// binary search
int binarySearch(DynamicArray& arr, int target) {
    int lo = 0, hi = arr.size - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr.data[mid] == target)      return mid;
        else if (arr.data[mid] < target)  lo = mid + 1;
        else                              hi = mid - 1;
    }
    return -1;
}

int main() {
    LinkedList daftarMahasiswa;
    DynamicArray arrNilai;

    // Input data mahasiswa
    int n;
    cout << "=== SISTEM PENGELOLAAN NILAI MAHASISWA ===\n\n";
    cout << "Masukkan jumlah mahasiswa: ";
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; i++) {
        string nim, nama;
        int nilai;
        cout << "\nMahasiswa ke-" << (i + 1) << ":\n";
        cout << "  NIM   : "; getline(cin, nim);
        cout << "  Nama  : "; getline(cin, nama);
        cout << "  Nilai : "; cin >> nilai;
        cin.ignore();

        daftarMahasiswa.tambah(nim, nama, nilai);
        arrNilai.push(nilai);
    }

    // Tampilkan data awal
    cout << "\n--- Data Mahasiswa (Sebelum Diurutkan) ---\n";
    daftarMahasiswa.tampilkan();

    cout << "\n--- Dynamic Array Nilai (Sebelum Diurutkan) ---\n";
    arrNilai.tampilkan();

    // Insertion Sort
    insertionSort(arrNilai);
    cout << "\n--- Dynamic Array Nilai (Setelah Insertion Sort) ---\n";
    arrNilai.tampilkan();

    // Loop menu
    int pilihan;
    do {
        cout << "\n========= MENU =========\n";
        cout << "1. Cari mahasiswa berdasarkan NIM (Linear Search)\n";
        cout << "2. Cari nilai tertentu (Binary Search)\n";
        cout << "3. Tampilkan semua data mahasiswa\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            string cariNIM;
            cout << "Masukkan NIM yang dicari: ";
            getline(cin, cariNIM);
            Mahasiswa* hasil = linearSearch(daftarMahasiswa, cariNIM);
            if (hasil != nullptr) {
                cout << "  Mahasiswa ditemukan!\n";
                cout << "  NIM  : " << hasil->nim  << "\n";
                cout << "  Nama : " << hasil->nama << "\n";
                cout << "  Nilai: " << hasil->nilai << "\n";
            } else {
                cout << "  Mahasiswa dengan NIM '" << cariNIM << "' tidak ditemukan.\n";
            }

        } else if (pilihan == 2) {
            int cariNilai;
            cout << "Masukkan nilai yang dicari: ";
            cin >> cariNilai;
            int idx = binarySearch(arrNilai, cariNilai);
            if (idx != -1) {
                cout << "  Nilai " << cariNilai
                     << " ditemukan pada indeks ke-" << idx
                     << " (dalam array yang sudah diurutkan).\n";
            } else {
                cout << "  Nilai " << cariNilai << " tidak ditemukan dalam data.\n";
            }

        } else if (pilihan == 3) {
            cout << "\n--- Data Mahasiswa ---\n";
            daftarMahasiswa.tampilkan();
            cout << "--- Nilai Terurut ---\n";
            arrNilai.tampilkan();
        }

    } while (pilihan != 0);

    cout << "\nProgram selesai. Terima kasih!\n";
    return 0;
}