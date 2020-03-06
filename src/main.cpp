#include <iostream>
#include <cmath>
#include <vector>
#include <unordered_map>
#include "geos.h"
#define INF 300000

using namespace std;


Line::Line(double x1, double y1, double x2, double y2) {
    if (x1 == x2) { // 直线平行于y轴
        k = INF;
        b = x1;
    }
    else {
        double tmp = x1 - x2;
        k = (y1 - y2) / tmp;
        b = (x1 * y2 - x2 * y1) / tmp;
    }
}

// 由直线上点的x值算出y值
double Line::xCalY(double x) {
    // k=INF时，x算不出来y，此处不考虑
    return k * x + b;
}

// 由直线上点的y值算出x值
double Line::yCalX(double y) {
    if (k == INF) {
        return b;
    }
    return (y - b) / k;
}

// 求两条直线的交点
pair<double, double> Line::getIntersect(Line &geo) {
    // 没有实现两条直线平行时的特判
    if (k == INF) {
        return pair<double, double>(b, geo.xCalY(b));
    }
    if (geo.k == INF) {
        return pair<double, double>(geo.b, xCalY(geo.b));
    }
    return pair<double, double>((geo.b - b) / (k - geo.k), (geo.k * b - k * geo.b) / (geo.k - k));
}

// 求直线和圆的交点
vector<pair<double, double>> Line::getIntersect(Circle& geo) {
    return vector<pair<double, double>>();
}


Circle::Circle(double _a, double _b, double _r) {
    a = _a;
    b = _b;
    r = _r;
}

// 由圆上点的x值算出y值
pair<double, double> Circle::xCalY(double x) {
    double tmp = sqrt(r * r - (x - a) * (x - a));
    return pair<double, double>(b + tmp, b - tmp);
}

// 由圆上点的y值算出x值
pair<double, double> Circle::yCalX(double y) {
    double tmp = sqrt(r * r - (y - b) * (y - b));
    return pair<double, double>(a + tmp, a - tmp);
}

// 求直线和圆的交点
vector<pair<double, double>> Circle::getIntersect(Line& geo) {
    return vector<pair<double, double>>();
}

// 求两个圆的交点
vector<pair<double, double>> Circle::getIntersect(Circle& geo) {
    return vector<pair<double, double>>();
}


struct pairHash
{
    template<class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2>& p) const
    {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ h2;
    }
};

unordered_map<double, vector<Line>> lineMap;
vector<Circle> circleList;

int main()
{
    int n, x1, y1, x2, y2;
    char c;
    cin >> n;
    while (n--) {
        cin >> c;
        if (c == 'L') {
            cin >> x1 >> y1 >> x2 >> y2;
            Line tmpLine(x1, y1, x2, y2);
            if (lineMap.find(tmpLine.k) == lineMap.end()) {
                lineMap.emplace(tmpLine.k, vector<Line>());
            }
            lineMap[tmpLine.k].emplace_back(tmpLine);
        }
        else if (c == 'C') {
            cin >> x1 >> y1 >> x2;
            circleList.emplace_back(x1, y1, x2);
        }
    }

    for (auto elm : lineMap) {
        cout << elm.first << endl;
    }
}