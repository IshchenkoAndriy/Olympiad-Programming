#include <iostream>
#include <climits>
#include <vector>
#include <stdio.h>

const int MaxColumnsCount = 10;
const int MaxRowsCount = 10;
const int MaxLevelsCount = 1000;

using namespace std;

int main()
{
    unsigned int rows_count;
    unsigned int columns_count;
    unsigned int levels_count;
    unsigned int diff_weight;
    
    char levels[MaxLevelsCount][MaxRowsCount][MaxColumnsCount];
    int level_diffs[MaxLevelsCount + 1][MaxLevelsCount + 1];
    bool used[MaxLevelsCount + 1];
    int min_e[MaxLevelsCount + 1];
    int sel_e[MaxLevelsCount + 1];
    int result_indices[MaxLevelsCount + 1];
    int result_types[MaxLevelsCount + 1];
    long current_result_count = 0;
    
    std::cin >> rows_count;
    std::cin >> columns_count;
    std::cin >> levels_count;
    std::cin >> diff_weight;
    
    for (int i = 0; i < levels_count; i++) {
        used[i] = false;
        min_e[i] = INT_MAX;
        sel_e[i] = -1;
        for (int j = 0; j < rows_count; j++) {
            scanf("%s", levels[i][j]);
        }
    }
    
    used[levels_count] = false;
    min_e[levels_count] = INT_MAX;
    sel_e[levels_count] = -1;
    
    level_diffs[0][0] = INT_MAX;
    int level_weight = rows_count * columns_count;
    for (int i = 0; i < levels_count; i++) {
        level_diffs[i + 1][0] = level_weight;
        level_diffs[0][i + 1] = level_weight;
        for (int j = i; j < levels_count; j++) {
            if (i == j) {
                level_diffs[i + 1][j + 1] = INT_MAX;
                continue;
            }
            
            int level_diff = 0;
            
            for (int k = 0; k < rows_count; k++) {
                for (int l = 0; l < columns_count; l++) {
                    if (levels[i][k][l] != levels[j][k][l]) {
                        level_diff++;
                    }
                }
            }
            
            level_diffs[i+1][j+1] = level_diff * diff_weight;
            level_diffs[j+1][i+1] = level_diff * diff_weight;
        }
    }
    
    level_diffs[1][0] = 0;
    level_diffs[0][1] = 0;
    
    long total_bytes_number = level_weight;
    int levels_graph_size = levels_count +1;
    
    min_e[0] = 0;
    for (int i=0; i<levels_graph_size; ++i) {
        int v = -1;
        for (int j=0; j<levels_graph_size; ++j)
            if (!used[j] && (v == -1 || min_e[j] < min_e[v]))
                v = j;
        
        used[v] = true;
        if (sel_e[v] != -1) {
            result_indices[current_result_count] = v;
            result_types[current_result_count] = sel_e[v];
            current_result_count++;
            total_bytes_number += min_e[v];
        }
        
        for (int to=0; to<levels_graph_size; ++to)
            if (level_diffs[v][to] < min_e[to]) {
                min_e[to] = level_diffs[v][to];
                sel_e[to] = v;
            }
    }
    
    printf("%d\n", total_bytes_number);
    for (int i = 0; i < current_result_count; i++) {
        printf("%d %d\n", result_indices[i], result_types[i]);
    }
    
    return 0;
}