#include <vector>
#include <cstdint>
using namespace std;
class Graph {
public:
    Graph(size_t n_vertex);
    void AddEdge(size_t from, size_t to, size_t length);

    vector <int> GetEdgesFrom(size_t from) const;
private:
    vector<vector<int>> adj_matrix;
};