#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <vector>
#include <tuple>
#include <sstream>
#include <cassert>


using namespace std;

// Funkcja bfs realizująca przeszukiwanie wszerz
// Funkcja valid sprawdza czy punkt nie jest poza planszą
// Funkcja seting_data ładuje dane poczotkowe z pliku
// Funkcja test testuje dla przyładowych danych
// sx, sy - współrzędne startowe
// ex, ey - współrzędne końcowe
// vis - tablica odwiedzin
// dist - tablica odległości
// n, m - wymiary planszy

bool valid(int x, int y,int n, int m) {
    return (x >= 0 && x < n && y >= 0 && y < m);
}

int bfs(int sx, int sy, int ex, int ey, vector<vector<bool>>& vis, vector<vector<int>>& dist, int n, int m) {
    // Stałe zmienne reprezentujące przesunięcie w osiach x i y dla 8 sąsiadów
    const int dx[] = {1, 1, -1, -1, 2, 2, -2, -2};
    const int dy[] = {2, -2, 2, -2, 1, -1, 1, -1};

    int x, y, nx, ny;
    queue<tuple<int, int>> q;
    q.push({sx, sy});
    vis[sx][sy] = true;
    dist[sx][sy] = 0;

    while (!q.empty()) {
        tie(x, y) = q.front();
        q.pop();

        if (x == ex && y == ey) {
            return dist[x][y];
        }

        for (int i = 0; i < 8; ++i) {
            nx = x + dx[i];
            ny = y + dy[i];
            if (valid(nx, ny, n, m) && !vis[nx][ny]) {
                vis[nx][ny] = true;
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }

    return -1;
}
int seting_data(string path){
    int n, m, sx, sy, ex, ey;

    ifstream inputFile(path);
    if (!inputFile) {
        cerr << "Nie można otworzyć pliku!" << endl;
        return -1;
    }

    string line;
    getline(inputFile, line);
    stringstream ss(line);
    ss >> n >> m;

    vector<vector<bool>> vis(n, vector<bool>(m));
    vector<vector<int>> dist(n, vector<int>(m, -1));


    for (int i = 0; i < n; ++i) {
        getline(inputFile, line);
        for (int j = 0; j < m; ++j) {
            if (line[j] == 'z') {
                sx = i;
                sy = j;
            } else if (line[j] == 'n') {
                ex = i;
                ey = j;
            } else if (line[j] == 'x') {
                vis[i][j] = true;
            }
        }
    }

    inputFile.close();
    return bfs(sx, sy, ex, ey, vis, dist, n, m);
}
int test() {
    // Test dla dane1.txt
    string path1 = "../test/dane1.txt";
    assert(seting_data(path1) == 3);

    // Test dla dane2.txt
    string path2 = "../test/dane2.txt";
    assert(seting_data(path2) == -1);

    // Test dla dane3.txt
    string path3 = "../test/dane3.txt";
    assert(seting_data(path3) == 5);

    // Test dla dane4.txt
    string path4 = "../test/dane4.txt";
    assert(seting_data(path4) == -1);

    cout << "Wszystkie testy zakończone sukcesem!" << endl;
    return 0;
}

int main() {

    int ans = seting_data("../dane.txt");
    if (ans == -1) {
        cout << "NIE" << endl;
    } else {
        cout << ans << endl;
    }

    test();
    return 0;
}
