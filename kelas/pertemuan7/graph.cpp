// Program C + buat nunjukkin Adjacency Matrix
// untuk graph yang undirected (tak berarah) dan unweighted (tak
// berbobot)
#include <iostream>
#include <vector>
using namespace std;

void addEdge(vector<vector<int>> &mat, int i, int j)
{
    mat[i][j] = 1;
    mat[j][i] = 1; // Karena graph-nya undirected, jadi berlaku dua arah
}
void displayMatrix(vector<vector<int>> &mat)
{
    int V = mat.size();
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
            cout << mat[i][j] << " ";
        cout << endl;
    }
}
int main()
{
    // Bikin graph isinya 4 vertex, awalnya belum ada edge
    // Ingat, semua nilainya otomatis diisi 0 dulu
    int V = 4;
    vector<vector<int>> mat(V, vector<int>(V, 0));
    // Sekarang kita tambahin edge-nya satu-satu
    addEdge(mat, 0, 1);
    addEdge(mat, 0, 2);
    addEdge(mat, 1, 2);
    addEdge(mat, 2, 3);
    cout << "Adjacency Matrix Representation" << endl;
    displayMatrix(mat);
    return 0;
}