#include <iostream>
#include <fstream>
#include <filesystem>
#include "TSP.hpp"

using namespace std;
namespace fs = filesystem;

struct Point {
    float x;
    float y;
};

float dist(Point p1, Point p2) {
    return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}

void readInput (vector<vector<float>>& matrix, const int& N, const vector<Point> points) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) {
                matrix[i][j] = 0;
            } else {
                matrix[i][j] = dist(points[i], points[j]);
            }
        }
    }
}

int main() {
    string path = "/Users/ivanbockov/123123123";
           auto it = fs::directory_iterator(path);
           vector<fs::path> array_path;
           copy_if(fs::begin(it), fs::end(it), std::back_inserter(array_path),
               [](const auto& entry) {
                   return fs::is_regular_file(entry);
           });
    for (auto& p : array_path) {
        ifstream fin;
        fin.open(p.string());
        cout << p.string() << endl;
        int N;
        fin >> N;
        vector<Point> points(N);
        vector<vector<float>> matrix(N, vector<float>(N));
        for (int i = 0; i < N; i++) {
            Point p;
            fin >> p.x >> p.y;
            points[i] = p;
        }
        readInput(matrix, N, points);
        TSP tsp(matrix);
        cout << tsp.getFinalRes() << endl;
        /*
        for (int i = 0; i <= N; i++) {
            cout << tsp.getFinalPath()[i] << " ";
        }
        cout << endl;
         */
    }
    return 0;
}
