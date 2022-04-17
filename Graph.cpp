//
// Created by Савельев Александр on 17.04.2022.
//
#include "Graph.h"

Graph::Graph(size_t n_vertex) :adj_matrix(n_vertex, vector<size_t>(n_vertex, -1)), n_vertex(n_vertex) {}

void Graph::AddEdge(size_t from, size_t to, size_t length) {
    adj_matrix[from][to] = length;
}




