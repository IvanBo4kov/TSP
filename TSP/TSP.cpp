#include "TSP.hpp"

TSP::TSP (vector<vector<float>> matrix) {
    N = matrix.size();
    final_res = MAXFLOAT;
    final_path.resize(N+1);
    visited.resize(N);
    vector<float> curr_path(N+1);
    int curr_bound = 0;
    fill(curr_path.begin(), curr_path.end(), -1);
    fill(visited.begin(), visited.end(), false);
    for (int i = 0; i < N; i++) {
        curr_bound += (min_i(matrix, i) + min_j(matrix, i));
    }
    curr_bound = (curr_bound&1)? curr_bound/2 + 1 : curr_bound/2;
    visited[0] = true;
    curr_path[0] = 0;
    TSPRec(matrix, curr_bound, 0, 1, curr_path);
}

void TSP::copyToFinalPath(vector<float> curr_path) {
    for (int i = 0; i < N; i++) {
        final_path[i] = curr_path[i];
    }
    final_path[N] = curr_path[0];
}

float TSP::min_i(vector<vector<float>> matrix, int i) {
    float min = MAXFLOAT;
    for (int k = 0; k < N; k++) {
        if(matrix[i][k] < min && i != k) {
            min = matrix[i][k];
        }
    }
    return min;
}

float TSP::min_j(vector<vector<float>> matrix, int i) {
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

void TSP::TSPRec(vector<vector<float>> matrix, int curr_bound, int curr_weight, int level, vector<float> curr_path) {
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
            fill(visited.begin(), visited.end(), false);
            for (int j=0; j<=level-1; j++) {
                visited[curr_path[j]] = true;
            }
        }
    }
}
float TSP::getFinalRes () {
    return final_res;
}

vector<float> TSP::getFinalPath() {
    return final_path;
}


