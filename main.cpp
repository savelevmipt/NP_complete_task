#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Graph.h"

size_t overlap(string s1, string s2);

int main() {
    int n;
    std::cin >> n;
    vector<string> strings(n);
    for (int i = 0; i < n; i++) {
        cin >> strings[i];
    }
    Graph graph (n);
    for (size_t from = 0; from < n; from++) {
        for (size_t to = 0; to < n; to++) {
            if (from == to)
                continue;
            graph.AddEdge(from, to, overlap(strings[from], strings[to]));
        }
    }
    for (auto i : graph.TravelingSalesman()) {
        cout << strings[i] << " ";
    }
}

size_t overlap(string s1, string s2) {
    size_t overlap = 0;
    for (int i = 1; i <= min(s1.length(), s2.length()); i++) {
        if (s1.substr(s1.length() - i, i) == s2.substr(0, i))
            overlap = i;
    }
    return overlap;
}
