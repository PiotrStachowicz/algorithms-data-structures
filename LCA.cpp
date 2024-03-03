// Piotr Stachowicz
// 337942
#include <iostream>
#include <vector>
#include <stack>
#include <fstream>

struct node {
    std::vector<int> kids;
    int father;
};

// Global declaration
int n, q;
std::vector<node> tree;
std::vector<int> LCA;
std::vector<int> height;

// DFS for calculating LCA
void DFS() {
    std::stack<int> stack{};
    stack.push(0);

    while (!stack.empty()) {
        int v = stack.top();
        stack.pop();

        if (v != 0) {
            height[v] = height[tree[v].father] + 1;
            if (!(height[v] & 1)) LCA[v] = tree[v].father;
            else LCA[v] = LCA[tree[v].father];
        }

        for (int edge: tree[v].kids) stack.push(edge);
    }
}


int answer(int x, int y) {
    while (LCA[x] != LCA[y]) {
        if (height[x] > height[y]) x = LCA[x];
        else y = LCA[y];
    }

    while(x != y) {
        if(height[x] > height[y]) x = tree[x].father;
        else y = tree[y].father;
    }

    return x;
}

// This method's speed is:
// Build tree, LCA & height: O(n)
// Answer question: O(sqrt(n))
int main() {
    std::ifstream F{R"(C:\Users\pansm\CLionProjects\AISD\Pracownia\test.txt)"};
    std::ifstream ANS{R"(C:\Users\pansm\CLionProjects\AISD\Pracownia\out.txt)"};
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
    F >> n >> q;

    std::vector<std::string> odp{};
    std::string ans;

    while (ANS >> ans) {
        odp.push_back(ans);
    }

    tree = std::vector<node>(n, node());
    LCA = std::vector<int>(n, 0);
    height = std::vector<int>(n, 0);

    // Initialize tree
    for (int i = 1; i < n; i++) {
        int w;
        F >> w;

        tree[i].father = w - 1;
        tree[w - 1].kids.push_back(i);
    }

    // Calculate LCA & height of every node (The Least Common Ancestor) in O(n)
    DFS();

    // Answer queries in O(q*sqrt(n))
    // Is a the ascendant of b?
    // It will happen iff LCA(a,b) = a
    int i = 0;
    while (q--) {
        int a, b;
        F >> a >> b;

        if(answer(a - 1, b - 1) == (a - 1)) {
            std::cout << "BLAD\n!";
        }
        else std::cout << "BLAD\n!";

        i++;
    }

    tree.clear();
    return 0;
}