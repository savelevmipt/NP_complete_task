#include <vector>
#include <cstdint>
using namespace std;
class Graph {
public:
    Graph(size_t n_vertex);
    void AddEdge(size_t from, size_t to, size_t length);


    vector <size_t> GetEdgesFrom(size_t from) const;
private:
    vector<vector<size_t>> adj_matrix; //нумерация вершин с нуля
    size_t n_vertex; //количество вершин
};