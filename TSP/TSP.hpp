#ifndef TSP_hpp
#define TSP_hpp

#include <stdio.h>
#include <vector>
#include <cmath>

using namespace std;

class TSP {
private:
    int N;
    float final_res;
    vector<float> final_path;
    vector<bool> visited;
public:
    TSP (vector<vector<float> > matrix);
    void TSPRec(vector<vector<float> > matrix, int curr_bound, int curr_weight, int level, vector<float> curr_path);
    float min_j(vector<vector<float> > matrix, int i);
    float min_i(vector<vector<float> > matrix, int i);
    void copyToFinalPath(vector<float> curr_path);
    float getFinalRes ();
    vector<float> getFinalPath();
};

#endif
