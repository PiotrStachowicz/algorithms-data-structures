// 337942
// Piotr Stachowicz
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <tuple>

using Point = std::pair<int, int>;
using P4 = std::tuple<float, Point, Point, Point>;

float dist(const Point &p1, const Point &p2) {
    return (float) sqrt(
            (p1.first - p2.first) * (p1.first - p2.first) + (p1.second - p2.second) * (p1.second - p2.second));
}

float circuit(const Point &p1, const Point &p2, const Point &p3) {
    return dist(p1, p2) + dist(p1, p3) + dist(p2, p3);
}

P4 check_strip(std::vector<Point> &strip, float c);

P4 divide_conquer(std::vector<Point> &tab);

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int n;

    std::cin >> n;

    std::vector<Point> X{};

    for (int i = 0; i < n; i++) {
        int x, y;

        std::cin >> x >> y;

        X.emplace_back(x, y);
    }

    std::sort(X.begin(), X.end(), [](Point &p1, Point &p2) {
        return p1.first < p2.first;
    });

    P4 dq = divide_conquer(X);

    std::cout << std::get<1>(dq).first << " " << std::get<1>(dq).second << "\n"
              << std::get<2>(dq).first << " " << std::get<2>(dq).second << "\n"
              << std::get<3>(dq).first << " " << std::get<3>(dq).second;

    return 0;
}

P4 check_strip(std::vector<Point> &strip, float c) {
    float min = c;
    P4 result = {std::numeric_limits<float>::max(), {}, {}, {}};

    std::sort(strip.begin(), strip.end(), [](Point &p1, Point &p2) {
        return p1.second < p2.second;
    });

    for (int i = 0; i < (int) strip.size(); i++) {

        for (int j = i + 1; j < (int) strip.size() && (float) (strip[j].second - strip[i].second) < min; ++j) {

            for (int k = j + 1; k < (int) strip.size() && (float) (strip[k].second - strip[j].second) < min; k++) {

                float cc = circuit(strip[i], strip[j], strip[k]);

                if (cc < min) {
                    min = cc;
                    result = {min, strip[i], strip[j], strip[k]};
                }
            }
        }
    }

    return result;
}


P4 divide_conquer(std::vector<Point> &tab) {
    if (tab.size() == 3) return {circuit(tab[0], tab[1], tab[2]), tab[0], tab[1], tab[2]};
    if (tab.size() < 3) return {std::numeric_limits<float>::max(), tab[0], tab[0], tab[0]};

    int mid = (int) (tab.size() >> 1);
    Point middle_point = tab[mid];

    std::vector<Point> left_v(tab.begin(), tab.begin() + mid);
    std::vector<Point> right_v(tab.begin() + mid, tab.end());

    P4 left = divide_conquer(left_v);
    P4 right = divide_conquer(right_v);

    P4 better_result = std::get<0>(left) < std::get<0>(right) ? left : right;
    float minc = std::get<0>(better_result);

    std::vector<Point> strip{};

    for (auto &i: tab) {
        if ((float) abs(i.first - middle_point.first) < minc) {
            strip.push_back(i);
        }
    }

    P4 strip_result = check_strip(strip, minc);

    if (std::get<0>(better_result) < std::get<0>(strip_result)) return better_result;
    else return strip_result;
}