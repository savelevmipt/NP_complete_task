#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Graph.h"
using std::cin, std::cout, std::string, std::min;
size_t overlap(string s1, string s2);
string glue (vector<string> strings);

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
    size_t old_i = -1;
    auto ans = graph.TravelingSalesman();
    vector<string> strings_in_right_order (strings.size());
    for (int i = 0; i < strings.size(); i++) {
        strings_in_right_order[i] = strings[ans[i]];
    }
    cout << glue(strings_in_right_order);
}

size_t overlap(string s1, string s2) {
    size_t overlap = 0;
    for (int i = 1; i <= min(s1.length(), s2.length()); i++) {
        if (s1.substr(s1.length() - i, i) == s2.substr(0, i))
            overlap = i;
    }
    return overlap;
}

string glue (vector<string> strings) {
    string glued;
    for (int i = 0; i < strings.size() - 1; i++) {
        glued += strings[i].substr(0, strings[i].size() - overlap(strings[i], strings[i + 1]));
    }
    glued += strings[strings.size() - 1];
    return glued;
}