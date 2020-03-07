#pragma once
#include <vector>
#include <cmath>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#define INF 300000

using namespace std;

/*
直线
k为斜率，b为y轴截距。
当k=INF时，直线平行于y轴，b为x轴截距。
*/
class Circle;

class Line {
public:
    double k;
    double b;

    Line(double x1, double y1, double x2, double y2);
    Line(double a, double b, double c);

    // 由直线上点的x值算出y值
    double xCalY(double x);

    // 求两条直线的交点
    pair<double, double> getIntersect(Line& geo);

    // 求直线和圆的交点
    vector<pair<double, double>> getIntersect(Circle& geo);
};

/*
圆
a, b为圆心坐标，r为圆的半径
*/
class Circle {
public:
    double a;
    double b;
    double r;

    Circle(double _a, double _b, double _r);

    // 由圆上点的x值算出y值
    pair<double, double> xCalY(double x);

    // 由圆上点的y值算出x值
    pair<double, double> yCalX(double y);

    // 求直线和圆的交点
    vector<pair<double, double>> getIntersect(Line& geo);

    // 求两个圆的交点
    vector<pair<double, double>> getIntersect(Circle& geo);
};

class Individual {
public:
    struct pairHash
    {
        template<class T1, class T2>
        size_t operator() (const pair<T1, T2>& p) const
        {
            auto h1 = hash<T1>{}(p.first);
            auto h2 = hash<T2>{}(p.second);
            return h1 ^ h2;
        }
    };

    unordered_map<double, vector<Line>> lineMap;
    unordered_set<pair<double, double>, pairHash> pointSet;
    vector<Circle> circleList;

    void parser();
    void parser(const string filename);
    void save(int x1, int y1, int x2, int y2);
    void save(int a, int b, int r);
    int calc();
};