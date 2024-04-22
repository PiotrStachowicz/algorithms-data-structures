#include <iostream>
#include <vector>
// Collaborated /w Jakub Malczak
using std::string;
using std::vector;
using std::max;

int n = 9;
int lcs = 4;
string S = "DIRTYROOM";
string T = "DORMITORY";

vector<int> len(n + 2, 0);
vector<int> rev(n + 2, 0);

// Time O(n^2)
// Space O(n)
string LCS(int l, int beginS, int endS, int beginT, int endT) {
    if (l == 0) return "";
    if (l == 1) {
        for (int i = beginS; i <= endS; ++i) {
            for (int j = beginT; j <= endT; ++j) {
                if (S[i - 1] == T[j - 1]) {
                    string s;
                    s += S[i - 1];
                    return s;
                }
            }
        }
    }

    fill(len.begin(), len.end(), 0);
    for (int i = beginS; i <= (endS + beginS + 1) / 2 - 1; ++i) {
        int prev = 0;
        for (int j = beginT; j <= endT; ++j) {
            int temp = len[j];
            if (S[i - 1] == T[j - 1]) len[j] = 1 + prev;
            else len[j] = max(len[j], len[j - 1]);
            prev = temp;
        }
    }

    fill(rev.begin(), rev.end(), 0);
    for (int i = endS; i >= (endS + beginS + 1) / 2; --i) {
        int prev = 0;
        for (int j = endT; j >= beginT; --j) {
            int temp = rev[j];
            if (S[i - 1] == T[j - 1]) rev[j] = 1 + prev;
            else rev[j] = max(rev[j], rev[j + 1]);
            prev = temp;
        }
    }

    int r = -1, max_len = -1;
    for (int i = 0; i <= n; ++i) {
        if (len[i] + rev[i + 1] > max_len) {
            r = i;
            max_len = len[i] + rev[i + 1];
        }
    }

    int r1 = len[r], r2 = rev[r + 1];

    return LCS(r1, beginS, (endS + beginS + 1) / 2 - 1, beginT, r) +
           LCS(r2, (endS + beginS + 1) / 2, endS, r + 1, endT);
}


int main() {

    std::cout << LCS(lcs, 1, n, 1, n) << '\n';
}