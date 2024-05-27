#include <iostream>
#include <vector>
#include <unordered_set>

void SUM2(const std::vector<int>& X, int target)
{
    std::unordered_set<int> us{};
    for (int j = 0; j < X.size(); ++j)
    {
        if (us.find(target -X[j]) != us.end())
        {
            std::cout << "TAK";
            return;
        }

        us.insert(X[j]);
    }

    std::cout << "NIE";
}



int main()
{
    std::vector<int> X = {-4, 1, 2, 1, -8};

    SUM2(X, 0);
    return 0;
}