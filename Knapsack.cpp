// Piotr Stachowicz
// 337942
#include <iostream>
#include <climits>
#include <vector>

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int F, C;

    std::cin >> F >> C;

    std::vector<long long int> weight(C);
    std::vector<long long int> price(C);
    std::vector<long long int> dp(F + 1, INT_MAX);
    std::vector<long long int> btrck(F + 1, -1);
    std::vector<long long int> ans(C, 0);

    for (int i = 0; i < C; ++i) {
        int p, w;

        std::cin >> p >> w;

        weight[i] = w;
        price[i] = p;
    }

    dp[0] = 0;

    for (int i = 1; i <= F; ++i) {
        for (int j = 0; j < C; ++j) {

            if (weight[j] <= i && dp[i - weight[j]] != INT_MAX) {
                long long int prev = dp[i];
                long long int curr = price[j] + dp[i - weight[j]];

                if (curr < prev) {
                    dp[i] = curr;
                    btrck[i] = j;
                }
            }

        }
    }

    long long int v = dp[F];

    if (v == INT_MAX) {
        std::cout << "NIE";
        return 0;
    }

    int w = F;
    int fc = btrck[F];

    while (v > 0 && w > 0) {
        ans[fc]++;
        v -= price[fc];
        w -= weight[fc];
        fc = btrck[w];
    }

    std::cout << "TAK\n";

    std::cout << dp[F] << "\n";

    for (int i = 0; i < C; ++i)
        std::cout << ans[i] << " ";

    
    std::fill_n(ans.begin(), C, 0);
    std::fill_n(dp.begin(), F + 1, -1);
    std::fill_n(btrck.begin(), F + 1, -1);

    dp[0] = 0;

    for (int i = 1; i <= F; ++i) {
        for (int j = 0; j < C; ++j) {

            if (weight[j] <= i && dp[i - weight[j]] != -1) {
                long long int prev = dp[i];
                long long int curr = price[j] + dp[i - weight[j]];

                if (curr > prev) {
                    dp[i] = curr;
                    btrck[i] = j;
                }
            }

        }
    }

    v = dp[F];
    w = F;
    fc = btrck[F];

    while (v > 0 && w > 0) {
        ans[fc]++;
        v -= price[fc];
        w -= weight[fc];
        fc = btrck[w];
    }

    std::cout << "\n" << dp[F] << "\n";

    for (int i = 0; i < C; ++i)
        std::cout << ans[i] << " ";

    return 0;
}