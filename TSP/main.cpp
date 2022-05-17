#include <iostream>
#include <fstream>
#include <filesystem>
#include "TSP.hpp"

using namespace std;
//namespace fs = filesystem;

struct Point {
    float x;
    float y;
};

float dist(Point p1, Point p2) {
    return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}

void readInput (vector<vector<float> >& matrix, const int& N, const vector<Point> points) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) {
                matrix[i][j] = MAXFLOAT;
            } else {
                matrix[i][j] = dist(points[i], points[j]);
            }
        }
    }
    for (int i = 0; i < N; i++) {
        matrix[i][0] = i;
        matrix[0][i] = i;
    }
}

int main() {
    string path = "/Users/ivanbockov/TSPtests";
           auto it = filesystem::directory_iterator(path);
           vector<filesystem::path> array_path;
           copy_if(filesystem::begin(it), filesystem::end(it), std::back_inserter(array_path), [](const auto& entry) {
                   return filesystem::is_regular_file(entry);
           });
    for (auto& p : array_path) {
        ifstream fin;
        fin.open(p.string());
        cout << p.string() << endl;
        int N;
        fin >> N;
        vector<Point> points(N);
        for (int i = 0; i < N; i++) {
            Point p;
            fin >> p.x >> p.y;
            points[i] = p;
        }
        N++;
        vector<vector<float> > matrix(N, vector<float>(N));
        readInput(matrix, N, points);
        TSP tsp(matrix);
        cout << tsp.get_res() << endl;
    }
    return 0;
}
