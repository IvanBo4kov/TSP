#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include <fstream>
#include <string>

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

void TSPRec(vector<vector<float>> matrix, int curr_bound, int curr_weight, int level, vector<float> curr_path) {
    if (level == N) {
        if (matrix[curr_path[level-1]][curr_path[0]] != 0) {
            int curr_res = curr_weight + matrix[curr_path[level-1]][curr_path[0]];
            if (curr_res < final_res) {
                copyToFinalPath(curr_path);
                final_res = curr_res;
            }
        }
        return;
    }
    for (int i = 0; i < N; i++) {
        if (matrix[curr_path[level-1]][i] != 0 && visited[i] == false) {
            int temp = curr_bound;
            curr_weight += matrix[curr_path[level-1]][i];
            if (level == 1) {
                curr_bound -= ((min_i(matrix, curr_path[level-1]) + min_i(matrix, i))/2);
            } else {
                curr_bound -= ((min_j(matrix, curr_path[level-1]) + min_i(matrix, i))/2);
            }
            if (curr_bound + curr_weight < final_res) {
                curr_path[level] = i;
                visited[i] = true;
                TSPRec(matrix, curr_bound, curr_weight, level+1, curr_path);
            }
            curr_weight -= matrix[curr_path[level-1]][i];
            curr_bound = temp;
            //memset(visited, false, sizeof(visited));
            for (int j=0; j<=level-1; j++) {
                visited[curr_path[j]] = true;
            }
        }
    }
}

void TSP (vector<vector<float>> matrix) {
    vector<float> curr_path(N+1);
    int curr_bound = 0;
    //memset(curr_path, -1, sizeof(curr_path));
    //memset(visited, 0, sizeof(curr_path));
    for (int i = 0; i < N; i++) {
        curr_bound += (min_i(matrix, i) + min_j(matrix, i));
    }
    curr_bound = (curr_bound&1)? curr_bound/2 + 1 : curr_bound/2;
    visited[0] = true;
    curr_path[0] = 0;
    TSPRec(matrix, curr_bound, 0, 1, curr_path);
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
