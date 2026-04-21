#include <iostream>
#include <vector>
using namespace std;
// Fungsi buat nambahin edge (sambungan) antar dua vertex
void addEdge(vector<vector<int>> &adj, int i, int j)
{
    adj[i].push_back(j);
    adj[j].push_back(i); // Dibikin dua arah, soalnya graph-nya undirected
}
// Fungsi buat nampilin adjacency list-nya
void displayAdjList(const vector<vector<int>> &adj)
{
    for (int i = 0; i < adj.size(); i++)
    {
        cout << i << ": "; // Cetak nomor vertex-nya
        for (int j : adj[i])
        {
            cout << j << " "; // Tampilin tetangga-tetangganya
        }
        cout << endl;
    }
}
// Program utamanya

int main()
{
    // Bikin graph dengan 4 vertex, awalnya masih kosong (belum ada edge)
    int V = 4;
    vector<vector<int>> adj(V);
    // Terus kita tambahin edge-nya satu per satu
    addEdge(adj, 0, 1);
    addEdge(adj, 0, 2);
    addEdge(adj, 1, 2);
    addEdge(adj, 2, 3);
    cout << "Adjacency List Representation:" << endl;
    displayAdjList(adj);
    return 0;
}