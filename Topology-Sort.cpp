#include <iostream>
#include <vector>
#include <queue>

using list = std::vector<int>;
using Graph = std::vector<std::pair<list, list>>;


// We assume Graph is acyclic and directed
list topology_sort(Graph& D) {
    list deg = list(D.size(), 0);
    std::queue<int> queue{};

    list res{};

    for(int i = 0; i < D.size(); i++) {
        if (D[i].first.empty()) queue.push(i);
        deg[i] = D[i].first.size();
    }

    while (!queue.empty()) {
        int v = queue.front();
        queue.pop();

        res.push_back(v);

        for(int i : D[v].second) {
            if (--deg[i] == 0) queue.push(i);
        }
    }

    return res;
}

/*
    Topology sort of acyclic digraph D(V,E)
 */
int main() {
    Graph D = Graph(3, std::pair<list, list>(list{}, list{}));
    D[0].first.push_back(1);
    D[1].first.push_back(0);
    D[1].second.push_back(0);
    D[2].second.push_back(1);

    auto res = topology_sort(D);

    for(int i : res) std::cout << i << " < ";

    return 0;
}