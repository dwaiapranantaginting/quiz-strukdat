#include <iostream>
#include <string>
#include <climits>
using namespace std;

const int V      = 6;
const int INF    = INT_MAX;
const char LABEL[] = {'A', 'B', 'C', 'D', 'E', 'F'};

struct Graph {
    int adj[V][V];

    Graph() {
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                adj[i][j] = 0;
    }

    // Tambah sisi tak berarah berbobot
    void addEdge(int u, int v, int w) {
        adj[u][v] = w;
        adj[v][u] = w;
    }

    void tampilkanMatrix() {
        cout << "  Adjacency Matrix:\n";
        cout << "     ";
        for (int i = 0; i < V; i++) cout << "  " << LABEL[i];
        cout << "\n";
        for (int i = 0; i < V; i++) {
            cout << "  " << LABEL[i] << "  ";
            for (int j = 0; j < V; j++) {
                cout << "  " << adj[i][j];
            }
            cout << "\n";
        }
    }
};

// bfs queue
struct SimpleQueue {
    int data[V];
    int front, rear;
    SimpleQueue() : front(0), rear(0) {}
    bool isEmpty() { return front == rear; }
    void push(int v) { data[rear++] = v; }
    int  pop()       { return data[front++]; }
};

// bfs dari vertex 
void BFS(Graph& g, int src) {
    bool visited[V] = {};
    int  parent[V];
    for (int i = 0; i < V; i++) parent[i] = -1;

    SimpleQueue q;
    visited[src] = true;
    q.push(src);

    cout << "  BFS dari " << LABEL[src] << ": ";

    while (!q.isEmpty()) {
        int u = q.pop();
        cout << LABEL[u];

        for (int v = 0; v < V; v++) {
            if (g.adj[u][v] != 0 && !visited[v]) {
                visited[v] = true;
                parent[v] = u;
                q.push(v);
            }
        }
        if (!q.isEmpty()) cout << " -> ";
    }
    cout << "\n";
}

// dfs
void DFSHelper(Graph& g, int u, bool visited[]) {
    visited[u] = true;
    cout << LABEL[u];
    for (int v = 0; v < V; v++) {
        if (g.adj[u][v] != 0 && !visited[v]) {
            cout << " -> ";
            DFSHelper(g, v, visited);
        }
    }
}

void DFS(Graph& g, int src) {
    bool visited[V] = {};
    cout << "  DFS dari " << LABEL[src] << ": ";
    DFSHelper(g, src, visited);
    cout << "\n";
}

// dijstra
void dijkstra(Graph& g, int src, int dst) {
    int  dist[V];
    bool visited[V] = {};
    int  parent[V];

    for (int i = 0; i < V; i++) {
        dist[i]   = INF;
        parent[i] = -1;
    }
    dist[src] = 0;

    for (int iter = 0; iter < V; iter++) {
        // Pilih vertex dengan jarak terkecil yang belum dikunjungi
        int u = -1;
        for (int i = 0; i < V; i++) {
            if (!visited[i] && (u == -1 || dist[i] < dist[u]))
                u = i;
        }
        if (u == -1 || dist[u] == INF) break;
        visited[u] = true;

        // Relaksasi
        for (int v = 0; v < V; v++) {
            if (g.adj[u][v] != 0 && !visited[v]) {
                int newDist = dist[u] + g.adj[u][v];
                if (newDist < dist[v]) {
                    dist[v]   = newDist;
                    parent[v] = u;
                }
            }
        }
    }

    // Tampilkan hasil
    cout << "  Dijkstra: " << LABEL[src] << " --> " << LABEL[dst] << "\n";
    if (dist[dst] == INF) {
        cout << "  Tidak ada rute yang bisa dilalui.\n";
        return;
    }

    // Rekonstruksi rute
    int path[V], pathLen = 0;
    int curr = dst;
    while (curr != -1) {
        path[pathLen++] = curr;
        curr = parent[curr];
    }

    cout << "  Rute   : ";
    for (int i = pathLen - 1; i >= 0; i--) {
        cout << LABEL[path[i]];
        if (i > 0) cout << " -> ";
    }
    cout << "\n";
    cout << "  Total jarak: " << dist[dst] << "\n";

    // Rincian tiap langkah
    cout << "  Rincian: ";
    for (int i = pathLen - 1; i >= 1; i--) {
        int u = path[i], v = path[i - 1];
        cout << LABEL[u] << " -(" << g.adj[u][v] << ")-> " << LABEL[v];
        if (i > 1) cout << " | ";
    }
    cout << "\n";
}

int main() {
    Graph g;

    // Inisialisasi graf sesuai soal
    // A=0, B=1, C=2, D=3, E=4, F=5
    g.addEdge(0, 1, 4);  // A-B
    g.addEdge(0, 2, 2);  // A-C
    g.addEdge(1, 2, 1);  // B-C
    g.addEdge(1, 3, 5);  // B-D
    g.addEdge(1, 4, 3);  // B-E
    g.addEdge(2, 3, 8);  // C-D
    g.addEdge(2, 4, 6);  // C-E
    g.addEdge(3, 4, 2);  // D-E
    g.addEdge(3, 5, 4);  // D-F
    g.addEdge(4, 5, 3);  // E-F

    cout << "=== SISTEM PENCARIAN RUTE DI LINGKUNGAN KAMPUS ===\n\n";
    g.tampilkanMatrix();

    int pilihan;
    do {
        cout << "\n========= MENU =========\n";
        cout << "1. BFS (Breadth-First Search)\n";
        cout << "2. DFS (Depth-First Search)\n";
        cout << "3. Dijkstra (Jarak Terpendek)\n";
        cout << "4. Tampilkan Adjacency Matrix\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1 || pilihan == 2) {
            char vertexChar;
            cout << "Masukkan vertex awal (A-F): ";
            cin >> vertexChar;
            cin.ignore();
            vertexChar = toupper(vertexChar);
            if (vertexChar < 'A' || vertexChar > 'F') {
                cout << "  Vertex tidak valid.\n";
                continue;
            }
            int src = vertexChar - 'A';
            if (pilihan == 1) BFS(g, src);
            else              DFS(g, src);

        } else if (pilihan == 3) {
            char srcChar, dstChar;
            cout << "Vertex awal  (A-F): "; cin >> srcChar; cin.ignore();
            cout << "Vertex tujuan (A-F): "; cin >> dstChar; cin.ignore();
            srcChar = toupper(srcChar);
            dstChar = toupper(dstChar);
            if (srcChar < 'A' || srcChar > 'F' || dstChar < 'A' || dstChar > 'F') {
                cout << "  Vertex tidak valid.\n";
                continue;
            }
            dijkstra(g, srcChar - 'A', dstChar - 'A');

        } else if (pilihan == 4) {
            g.tampilkanMatrix();
        }

    } while (pilihan != 0);

    cout << "\nProgram selesai. Terima kasih!\n";
    return 0;
}