// 337942
// Piotr Stachowicz
#include <iostream>
#include <algorithm>
#include <cmath>
#include <climits>

int n;

struct Point {
    int x;
    int y;
};

struct P2 {
    Point p1;
    Point p2;
};

double dist(Point& p1, Point& p2) {
    if(p1.x == INT_MIN) return INT_MAX;
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

P2 trivial(Point tab[], int x) {
    double min = -1;
    auto p1 = Point(INT_MIN, INT_MIN);
    auto p2 = Point(INT_MIN, INT_MIN);

    for (int i = 0; i < x; i++) {
        for (int j = i + 1; j < x; j++) {
            if (dist(tab[i], tab[j]) < min) {
                min = dist(tab[i], tab[j]);
                p1 = tab[i];
                p2 = tab[j];
            }
        }
    }

    auto result = P2(p1, p2);

    return result;
}

P2 check_strip(Point strip[], int size, double d) {
    double min = d;
    auto p1 = Point(INT_MIN, INT_MIN);
    auto p2 = Point(INT_MIN, INT_MIN);

    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size && (strip[j].y - strip[i].y) < min; j++) {
            if (dist(strip[i], strip[j]) < min) {
                min = dist(strip[i], strip[j]);
                p1 = strip[i];
                p2 = strip[j];
            }
        }
    }


    auto result = P2(p1, p2);

    return result;
}


P2 divide_conquer(Point tab[], int count) {
    if (count <= 3) {
        return trivial(tab, count);
    }

    int mid = count >> 1;

    Point mid_Point = tab[mid];

    P2 left = divide_conquer(tab, mid);
    P2 right = divide_conquer(tab + mid, count - mid);

    double distance1 = dist(left.p1, left.p2);
    double distance2 = dist(right.p1, right.p2);

    double d = std::min(distance1, distance2);

    Point strip[n];
    int idx = 0;

    for (int i = 0; i < n; i++) {
        if(abs(tab[i].x - mid_Point.x) < d) {
            strip[idx] = tab[i];
            idx++;
        }
    }

    P2 strip_result = check_strip(strip, idx, d);

    double distance3 = dist(strip_result.p1, strip_result.p2);

    P2 result{};

    double minimum_distance = std::min({distance1, distance2, distance3});

    if(minimum_distance == distance1) result = left;
    else if(minimum_distance == distance2) result = right;
    else result = strip_result;

    return result;
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    std::cin >> n;

    Point X[n];
    Point Y[n];

    for (int i = 0; i < n; i++) {
        int x, y;

        std::cin >> x >> y;

        X[i] = Point(x, y);
        Y[i] = Point(x, y);
    }

    std::sort(X, X + n, [](Point &p1, Point &p2) {
        return p1.x < p2.x;
    });

    std::sort(Y, Y + n, [](Point &p1, Point &p2) {
        return p1.y < p2.y;
    });

    P2 result = divide_conquer(X, n);

    std::cout << result.p1.x << " " << result.p1.y << "\n"
              << result.p2.x << " " << result.p2.y;

    return 0;
}