#include <iostream>
#include <vector>
#include <algorithm>

int n;
std::vector<std::pair<int, int>> I{};

// O(nlogn)
int main() {
    std::cin >> n;
    int q = n;

    int res = 0;

    while(q--) {
        int a, b;
        std::cin >> a >> b;

        if(a > b) {
            int c = a;
            a = b;
            b = c;
        }

        I.emplace_back(a, b);
    }

    std::sort(I.begin(), I.end(), [](std::pair<int, int>& p1, std::pair<int, int>& p2) {
        return p1.second < p2.second;
    });

    int U = 0;

    for(auto& odc : I) {
        if(odc.first >= U) {
            ++res;
            U = odc.second;
        }
    }

    std::cout << res;


    return 0;
}