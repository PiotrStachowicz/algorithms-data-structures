#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <cstdint>


void SUM3(const std::vector<int32_t>& X, int32_t target)
{
    std::unordered_set<int32_t> us{};

    for (int32_t i = 0; i < X.size(); ++i)
    {
        for (int32_t j = i + 1; j < X.size(); ++j)
        {
            if (us.find(target -X[i] - X[j]) != us.end())
            {
                std::cout << "TAK";
                return;
            }
        }

        us.insert(X[i]);
    }

    std::cout << "NIE";
}


void SUM3b(std::vector<int32_t>& X, int32_t target)
{
    std::sort(X.begin(), X.end());

    for (int32_t i = 0; i < X.size() - 2; ++i)
    {
        int32_t start = i + 1;
        int32_t end = (int32_t)X.size() - 1;

        int32_t a = X[i];

        while (start < end)
        {
            int32_t b = X[start];
            int32_t c = X[end];

            if (a + b + c == target)
            {
                std::cout << "TAK";
                return;
            }
            else if (a + b + c < target)
            {
                start += 1;
            }
            else
            {
                end -= 1;
            }
        }

    }

    std::cout << "NIE";
}


int32_t main()
{
    std::vector<int32_t> X = {-4, 1, 2, 3, -8};

    SUM3(X, 0);
    std::cout << "\n";
    SUM3b(X, 0);
    return 0;
}