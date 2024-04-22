#include <iostream>
#include <vector>
using sequence = std::vector<int>;

sequence A = {2, 3, 1, 6, 5, 4, 6 };
sequence B = {1, 3, 5, 6};


void backtrack(const sequence& L, sequence& result, int idx, int v, int len) {
    int j = idx;

    while (B[j - 1] >= v || L[j] != len) {
        j--;
    }

    if (j >= 0) {
        backtrack(L, result, j, B[j - 1], len - 1);
        result.push_back(B[j - 1]);
    }
}


// Time O(mn)
// Space O(m)
sequence LCIS()
{
    sequence L(B.size() + 1, 0);

    for (int i = 1; i <= A.size(); ++i) {
        L[0] = 0;

        for (int j = 1; j <= B.size(); ++j) {
            if (A[i - 1] > B[j - 1] && L[j] > L[0]) {
                L[0] = L[j];
            }

            if (A[i - 1] == B[j - 1]) {
                L[j] = L[0] + 1;
            }
        }
    }

    int length = 0;
    int m_i = 0;

    for(int i = 1; i <= B.size(); ++i) {
        if (L[i] >= length) {
            length = L[i];
            m_i = i;
        }
    }

    sequence result{};
    backtrack(L, result, m_i, INT_MAX, length);

    return result;
}


int main()
{
    sequence result = LCIS();

    for(auto elem : result)
        std::cout << elem << " ";

    std::cout << "\n";

    return 0;
}