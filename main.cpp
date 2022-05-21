#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <optional>
#include "Graph.h"
using std::cin, std::cout, std::string, std::min;
size_t overlap(string s1, string s2);
string glue (vector<string> strings);

vector<int> prefix_function (string s) {
    int n = (int) s.length();
    vector<int> pi (n);
    for (int i=1; i<n; ++i) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])  ++j;
        pi[i] = j;
    }
    return pi;
}

vector<int> prefix_function (vector<std::optional<char>> s) {
    int n = (int) s.size();
    vector<int> pi (n);
    for (int i=1; i<n; ++i) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])  ++j;
        pi[i] = j;
    }
    return pi;
}

std::optional<char> x;

bool is_substring (string s1, string s2) {
    vector<std::optional<char>> s;
    for(int i = 0; i < s1.length(); i++) {
        s.push_back(std::optional<char>(s1[i]));
    }
    s.push_back(std::optional<char>());
    for(int i = 0; i < s2.length(); i++){
        s.push_back(std::optional<char>(s2[i]));
    }

    for (auto i : prefix_function(s)) {
        if (i == s1.size())
            return true;
    }
    return false;
}





size_t overlap(string s1, string s2) {
    return prefix_function(s2 + "$" + s1)[s2.length() + s1.length()];
}


int main() {
    int n;
    std::cin >> n;
    vector<string> strings(n);
    for (int i = 0; i < n; i++) {
        cin >> strings[i];
    }

    vector<bool> necessary(n, true);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j)
                continue;
            if (is_substring(strings[i], strings[j])) {
                necessary[i] = false;
            }
        }
    }
    vector<string> necessary_strings;
    for (int i = 0; i < n; i++) {
        if (necessary[i]) {
            necessary_strings.push_back(strings[i]);
        }
    }
    strings = necessary_strings;
    n = strings.size();

    size_t old_i = -1;
    {
        Graph graph (n);
        for (size_t from = 0; from < n; from++) {
            for (size_t to = 0; to < n; to++) {
                if (from == to)
                    continue;
                graph.AddEdge(from, to, overlap(strings[from], strings[to]));
            }
        }
        auto ans = graph.TravelingSalesman();
        vector<string> strings_in_right_order(strings.size());
        for (int i = 0; i < strings.size(); i++) {
            strings_in_right_order[i] = strings[ans[i]];
        }
        cout << "Exact answer: " << std::endl << glue(strings_in_right_order) << std::endl;
    }

    {
        Graph graph (n);
        for (size_t from = 0; from < n; from++) {
            for (size_t to = 0; to < n; to++) {
                graph.AddEdge(from, to, overlap(strings[from], strings[to]));
            }
        }
        string approximate_ans;
        auto cycles = graph.BlumYoungLeeTrompYannakakis();
        for (auto cycle : cycles) {
            approximate_ans += strings[cycle[0]];
            for (int i = 1; i < cycle.size(); i++) {
                approximate_ans += strings[cycle[i]].substr(overlap(strings[cycle[i - 1]], strings[cycle[i]]));
            }
        }
        cout << "Approximate answer: " << std::endl << approximate_ans;
    }
}


size_t overlap_old(string s1, string s2) {
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

