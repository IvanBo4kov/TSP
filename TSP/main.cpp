#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
using namespace std;

int N;
float final_res = MAXFLOAT;
vector<float> final_path(N+1);
vector<bool> visited(N);

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
                matrix[i][j] = MAXFLOAT;
            } else {
                matrix[i][j] = dist(points[i], points[j]);
            }
        }
    }
}

void copyToFinalPath(vector<float> curr_path) {
    for (int i = 0; i < N; i++) {
        final_path[i] = curr_path[i];
    }
    final_path[N] = curr_path[0];
}

float min_i(vector<vector<float>> matrix, int i) {
    int min = INT_MAX;
    for (int k = 0; k < N; k++) {
        if(matrix[i][k] < min && i != k) {
            min = matrix[i][k];
        }
    }
    return min;
}

float min_j(vector<vector<float>> matrix, int i) {
    float first = MAXFLOAT;
    float second = MAXFLOAT;
    for (int j = 0; j < N; j++) {
        if (i == j) {
            continue;
        }
        if (matrix[i][j] <= first) {
            second = first;
            first = matrix[i][j];
        }
        else if (matrix[i][j] <= second && matrix[i][j] != first) {
            second = matrix[i][j];
        }
    }
    return second;
}

int main() {
    cin >> N;
    vector<Point> points(N);
    vector<vector<float>> matrix(N, vector<float>(N));
    for (int i = 0; i < N; i++) {
        Point p;
        cin >> p.x >> p.y;
        points[i] = p;
    }
    readInput(matrix, N, points);
    
    return 0;
}
