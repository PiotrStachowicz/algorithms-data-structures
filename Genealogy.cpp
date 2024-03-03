// Piotr Stachowicz
// 337942
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

// n - node quantity, q - questions quantity, tree - list of edges
int n, q;
std::vector<std::pair<int, int>> tree{};
std::vector<int> pivot;

/**
    Calculates _IN_ & _OUT_ moment vectors of every node _IN_ the descendant tree using DFS
    @param _IN_ In moment vector,
    @param _OUT_ Out moment vector,
    @param _VISITED_ Vector of _VISITED_ nodes
**/
void DeepFirstSearch(std::vector<int> &_IN_, std::vector<int> &_OUT_, std::vector<bool> &_VISITED_) {
    std::stack<int> trace{};
    trace.push(0);
    int counter = 0;

    while (!trace.empty()) {
        int mother = trace.top();

        if (!_VISITED_[mother]) {
            _IN_[mother] = counter++;
            _VISITED_[mother] = true;

            int start_idx = pivot[mother];

            for (int i = start_idx; i < n && tree[i].first == mother; i++) {
                if (!_VISITED_[tree[i].second]) {
                    trace.push(tree[i].second);
                }
            }
        } else {
            _OUT_[mother] = counter++;
            trace.pop();
        }
    }
}

/**
    This approach of solving the ancestor problem is pretty fast and memory efficient,
    we process the information in O(n log n), where the most expensive operation is sorting.
    But the main advantage is that we can answer the queries in θ(1)
 **/
int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    std::cin >> n >> q;

    pivot = std::vector<int>(n, -1);
    std::vector<int> in(n, 0);
    std::vector<int> out(n, 0);
    std::vector<bool> vector(n, false);

    // Build the ancestor Tree (edge list)
    for (int i = 1; i < n; i++) {
        int w;
        std::cin >> w;
        tree.emplace_back(w - 1, i);
    }

    // Sort the edges so that we can traverse through them in good order
    std::sort(tree.begin(), tree.end(), [](std::pair<int, int> &p1, std::pair<int, int> &p2) {
        return p1.first < p2.first;
    });

    int p = -1;
    for (int i = 0; i < n - 1; i++) {
        int mother = tree[i].first;
        if (mother != p) {
            p = mother;
            pivot[mother] = i;
        }
    }

    // Populate moment vectors
    DeepFirstSearch(in, out, vector);

    // Answer questions: O(q*1)
    while (q--) {
        int a, b;
        std::cin >> a >> b;

        if (in[a - 1] <= in[b - 1] && out[a - 1] >= in[b - 1]) std::cout << "TAK\n";
        else std::cout << "NIE\n";
    }

    return 0;
}