#pragma once
#include <vector>

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

    // 由直线上点的x值算出y值
    double xCalY(double x);

    // 由直线上点的y值算出x值
    double yCalX(double y);

    // 求两条直线的交点
    pair<double, double> getIntersect(Line& geo);

    // 求直线和圆的交点
    vector<pair<double, double>> getIntersect(Circle& geo);
};

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