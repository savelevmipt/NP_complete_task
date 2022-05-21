//
// Created by Савельев Александр on 17.04.2022.
//
#include "Graph.h"

Graph::Graph(size_t n_vertex) :adj_matrix(n_vertex, vector<int>(n_vertex, INT32_MAX)), n_vertex(n_vertex) {}

void Graph::AddEdge(size_t from, size_t to, int length) {
    adj_matrix[from][to] = length;
}

vector<size_t> Graph::TravelingSalesman() {
    vector<vector<int>> longest_path_len  (1 << n_vertex, vector<int>(n_vertex, INT32_MAX));
    //shortest_path_len[mask][last_vertex] - самый короткий путь, проходящий ровно один раз по каждой из вершин из mask, завершающийся в вершине last_vertex
    vector<vector<size_t>> prev (1 << n_vertex, vector<size_t>(n_vertex, -1));

    for (size_t mask = 1; mask < (1 << n_vertex); mask++) {
        for (size_t last_vertex = 0; last_vertex < n_vertex; last_vertex++) {
            if(((1 << last_vertex) & mask) == 0)
                continue;
            size_t prev_mask = mask - (1 << last_vertex);
            if (prev_mask == 0) {
                longest_path_len[mask][last_vertex] = 0;
                prev[mask][last_vertex] = last_vertex;
                continue;
            }
            for (size_t prev_vertex = 0; prev_vertex < n_vertex; prev_vertex++) {
                if (prev_vertex == last_vertex || ((1 << prev_vertex) & prev_mask) == 0)
                    continue;
                if (longest_path_len[prev_mask][prev_vertex] != -1 && adj_matrix[prev_vertex][last_vertex] != INT32_MAX &&
                    (longest_path_len[prev_mask][prev_vertex] + adj_matrix[prev_vertex][last_vertex] > longest_path_len[mask][last_vertex] || longest_path_len[mask][last_vertex] == INT32_MAX)) {
                    longest_path_len[mask][last_vertex] = longest_path_len[prev_mask][prev_vertex] + adj_matrix[prev_vertex][last_vertex];
                    prev[mask][last_vertex] = prev_vertex;
                }

            }
        }
    }
    size_t final_mask = (1 << n_vertex) - 1;
    size_t best_last_vertex = -1;
    for (size_t last_vertex = 0; last_vertex < n_vertex; last_vertex++) {
        if (longest_path_len[final_mask][last_vertex] == INT32_MAX)
            continue;
        if (best_last_vertex == -1 ||
            longest_path_len[final_mask][best_last_vertex] < longest_path_len[final_mask][last_vertex]) {
            best_last_vertex = last_vertex;
        }
    }
    if (best_last_vertex == -1) {
        return {};
    }
    vector<size_t> ans(n_vertex);
    ans[n_vertex - 1] = best_last_vertex;
    size_t mask = final_mask;
    for(int pos = n_vertex - 2; pos != -1; pos--) {
        ans[pos] = prev[mask][ans[pos + 1]];
        mask -= (1 << ans[pos + 1]);
    }
    return ans;
}

vector<vector<size_t>> Graph::BlumYoungLeeTrompYannakakis() {
    vector <bool> row_avlb(n_vertex, true), column_avlb(n_vertex, true);
    vector <size_t> next_vertex(n_vertex, -1);
    for (int step = 0; step < n_vertex; step++) {
        int max_edge = -1;
        size_t from;
        size_t to;
        for (size_t i = 0; i < n_vertex; i++) {
            for (size_t j = 0; j < n_vertex; j++) {
                if(row_avlb[i] && column_avlb[j]) {
                    max_edge = adj_matrix[i][j];
                    from = i;
                    to = j;

                }
            }
        }
        next_vertex[from] = to;
        row_avlb[from] = false;
        column_avlb[to] = false;
    }
    vector<vector<size_t>> cycle;
    vector<bool> ready(n_vertex, false);
    for (size_t start = 0; start < n_vertex; start++) {
        if(ready[start])
            continue;
        size_t cur_vertex = start;
        vector<size_t> this_cycle;
        int min_edge = 1e9;
        size_t min_edge_to;
        while(cur_vertex != start || min_edge == 1e9) {
            if(min_edge > adj_matrix[cur_vertex][next_vertex[cur_vertex]]) {
                min_edge = adj_matrix[cur_vertex][next_vertex[cur_vertex]];
                min_edge_to = next_vertex[cur_vertex];
            }
            cur_vertex = next_vertex[cur_vertex];
        }
        cur_vertex = min_edge_to;
        while(!ready[cur_vertex]) {
            ready[cur_vertex] = true;
            this_cycle.push_back(cur_vertex);
            cur_vertex = next_vertex[cur_vertex];
        }
        cycle.push_back(this_cycle);
    }
    return cycle;

}
