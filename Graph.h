#include <vector>
#include <cstdint>
using std::vector;
class Graph {
public:
    Graph(size_t n_vertex);
    void AddEdge(size_t from, size_t to, int length);
    vector<size_t> GetEdgesFrom(size_t from) const;
    vector<size_t> TravelingSalesman();
    vector<vector<size_t>> BlumYoungLeeTrompYannakakis();
private:
    vector<vector<int>> adj_matrix; //нумерация вершин с нуля
    size_t n_vertex; //количество вершин
};