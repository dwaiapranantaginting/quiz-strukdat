#include <iostream>
#include <string>
using namespace std;


struct QueueNode {
    string nama;
    QueueNode* next;
};

struct Queue {
    QueueNode* front;
    QueueNode* rear;
    int size;

    Queue() : front(nullptr), rear(nullptr), size(0) {}

    bool isEmpty() { return front == nullptr; }

    void enqueue(const string& nama) {
        QueueNode* baru = new QueueNode{nama, nullptr};
        if (rear == nullptr) {
            front = rear = baru;
        } else {
            rear->next = baru;
            rear = baru;
        }
        size++;
        cout << "  [QUEUE] '" << nama << "' masuk antrean.\n";
    }

    string dequeue() {
        if (isEmpty()) return "";
        QueueNode* tmp = front;
        string nama = tmp->nama;
        front = front->next;
        if (front == nullptr) rear = nullptr;
        delete tmp;
        size--;
        cout << "  [QUEUE] '" << nama << "' dilayani (keluar antrean).\n";
        return nama;
    }

    void tampilkan() {
        if (isEmpty()) { cout << "  Antrean kosong.\n"; return; }
        cout << "  Antrean: ";
        QueueNode* curr = front;
        while (curr) {
            cout << "[" << curr->nama << "]";
            if (curr->next) cout << " -> ";
            curr = curr->next;
        }
        cout << "\n";
    }

    ~Queue() {
        while (!isEmpty()) dequeue();
    }
};

// lifo
struct StackNode {
    string info;   // "<nama> mengembalikan buku ID <id>"
    StackNode* next;
};

struct Stack {
    StackNode* top;
    int size;

    Stack() : top(nullptr), size(0) {}

    bool isEmpty() { return top == nullptr; }

    void push(const string& info) {
        StackNode* baru = new StackNode{info, top};
        top = baru;
        size++;
        cout << "  [STACK] Riwayat disimpan: \"" << info << "\"\n";
    }

    string pop() {
        if (isEmpty()) return "";
        StackNode* tmp = top;
        string info = tmp->info;
        top = top->next;
        delete tmp;
        size--;
        return info;
    }

    void tampilkan() {
        if (isEmpty()) { cout << "  Riwayat kosong.\n"; return; }
        cout << "  Riwayat Pengembalian (terbaru di atas):\n";
        StackNode* curr = top;
        int i = 1;
        while (curr) {
            cout << "    " << i++ << ". " << curr->info << "\n";
            curr = curr->next;
        }
    }

    ~Stack() {
        while (!isEmpty()) pop();
    }
};

// binary search
struct BSTNode {
    int id;
    BSTNode* left;
    BSTNode* right;
    BSTNode(int val) : id(val), left(nullptr), right(nullptr) {}
};

struct BST {
    BSTNode* root;

    BST() : root(nullptr) {}

    BSTNode* insert(BSTNode* node, int val) {
        if (node == nullptr) return new BSTNode(val);
        if (val < node->id)       node->left  = insert(node->left,  val);
        else if (val > node->id)  node->right = insert(node->right, val);
        else cout << "  [BST] ID " << val << " sudah ada, diabaikan.\n";
        return node;
    }

    void insert(int val) {
        root = insert(root, val);
        cout << "  [BST] ID buku " << val << " ditambahkan.\n";
    }

    bool search(BSTNode* node, int val) {
        if (node == nullptr) return false;
        if (val == node->id)      return true;
        if (val < node->id)       return search(node->left,  val);
        return search(node->right, val);
    }

    bool search(int val) { return search(root, val); }

    void preOrder(BSTNode* node) {
        if (node == nullptr) return;
        cout << node->id << " ";
        preOrder(node->left);
        preOrder(node->right);
    }

    void inOrder(BSTNode* node) {
        if (node == nullptr) return;
        inOrder(node->left);
        cout << node->id << " ";
        inOrder(node->right);
    }

    void postOrder(BSTNode* node) {
        if (node == nullptr) return;
        postOrder(node->left);
        postOrder(node->right);
        cout << node->id << " ";
    }

    void tampilkanTraversal() {
        cout << "  Pre-Order  : "; preOrder(root);  cout << "\n";
        cout << "  In-Order   : "; inOrder(root);   cout << "\n";
        cout << "  Post-Order : "; postOrder(root); cout << "\n";
    }

    void destroy(BSTNode* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    ~BST() { destroy(root); }
};


int main() {
    Queue antrean;
    Stack riwayat;
    BST   bstBuku;

    cout << "=== SISTEM ANTREAN & PENGELOLAAN BUKU PERPUSTAKAAN ===\n\n";

    // --- Isi BST dengan beberapa ID buku awal ---
    cout << "--- Inisialisasi BST ID Buku ---\n";
    int idAwal[] = {50, 30, 70, 20, 40, 60, 80};
    for (int id : idAwal) bstBuku.insert(id);

    int pilihan;
    do {
        cout << "\n=========== MENU ===========\n";
        cout << "1. Tambah mahasiswa ke antrean peminjaman\n";
        cout << "2. Layani mahasiswa (dequeue)\n";
        cout << "3. Kembalikan buku (push riwayat)\n";
        cout << "4. Lihat riwayat pengembalian\n";
        cout << "5. Pop riwayat terbaru\n";
        cout << "6. Tambah ID buku ke BST\n";
        cout << "7. Cari ID buku di BST\n";
        cout << "8. Tampilkan traversal BST\n";
        cout << "9. Tampilkan antrean saat ini\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            string nama;
            cout << "Nama mahasiswa: ";
            getline(cin, nama);
            antrean.enqueue(nama);

        } else if (pilihan == 2) {
            string dilayani = antrean.dequeue();
            if (dilayani.empty())
                cout << "  Tidak ada mahasiswa dalam antrean.\n";

        } else if (pilihan == 3) {
            string nama;
            int idBuku;
            cout << "Nama peminjam   : ";
            getline(cin, nama);
            cout << "ID buku dikembalikan: ";
            cin >> idBuku;
            cin.ignore();
            riwayat.push(nama + " mengembalikan buku ID " + to_string(idBuku));

        } else if (pilihan == 4) {
            cout << "\n--- Riwayat Pengembalian ---\n";
            riwayat.tampilkan();

        } else if (pilihan == 5) {
            string info = riwayat.pop();
            if (info.empty()) cout << "  Riwayat kosong.\n";
            else cout << "  Dihapus dari riwayat: \"" << info << "\"\n";

        } else if (pilihan == 6) {
            int id;
            cout << "Masukkan ID buku: ";
            cin >> id;
            cin.ignore();
            bstBuku.insert(id);

        } else if (pilihan == 7) {
            int id;
            cout << "Masukkan ID buku yang dicari: ";
            cin >> id;
            cin.ignore();
            if (bstBuku.search(id))
                cout << "  ID buku " << id << " DITEMUKAN dalam BST.\n";
            else
                cout << "  ID buku " << id << " TIDAK ditemukan dalam BST.\n";

        } else if (pilihan == 8) {
            cout << "\n--- Traversal BST ---\n";
            bstBuku.tampilkanTraversal();

        } else if (pilihan == 9) {
            cout << "\n--- Antrean Saat Ini ---\n";
            antrean.tampilkan();
        }

    } while (pilihan != 0);

    cout << "\nProgram selesai. Terima kasih!\n";
    return 0;
}