#pragma once
#include <vector>
#include <cmath>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <set>
#define INF 500000
using namespace std;

/*
交点。
以有理分子、无理分子、分母来存储。
*/
class Point {
public:
    long long xup;
    long long xdown;
    double xdelta;
    long long yup;
    long long ydown;
    double ydelta;

    long long gcd(long long a, long long b) {
        a = abs(a);
        b = abs(b);
        long long temp;
        if (a < b) {
            temp = a;
            a = b;
            b = temp;
        }
        while (b != 0) {
            temp = a % b;
            a = b;
            b = temp;
        }
        return a;
    }

    Point(long long _xup, long long _xdown, double _xdelta, long long _yup, long long _ydown, double _ydelta)
    {
        xup = 0;
        xdown = 0;
        yup = 0;
        ydown = 0;
        xdelta = _xdelta + (double)_xup / _xdown;
        ydelta = _ydelta + (double)_yup / _ydown;
    }

    Point(long long _xup, long long _xdown, long long _yup, long long _ydown)
    {
        if (_xup == 0) {
            xup = 0;
            xdown = 1;
        }
        else {
            long long g = gcd(_xup, _xdown);
            xup = _xup / g;
            xdown = _xdown / g;
            if (xdown > 0) {
                xdown = -xdown;
                xup = -xup;
            }
        }
        xdelta = 0;

        if (_yup == 0) {
            yup = 0;
            ydown = 1;
        }
        else {
            long long g = gcd(_yup, _ydown);
            yup = _yup / g;
            ydown = _ydown / g;
            if (ydown > 0) {
                ydown = -ydown;
                yup = -yup;
            }
        }
        ydelta = 0;

        xdelta = (double)xup / xdown;
        ydelta = (double)yup / ydown;
    }

    bool operator==(const Point& rc) const
    {
        if (xdelta == 0 && ydelta == 0 && rc.xdelta == 0 && rc.ydelta == 0) {
            if ((xup == rc.xup) && (xdown == rc.xdown) && (yup == rc.yup) && (ydown == rc.ydown)) {
                return true;
            }
        }
        else {
            double eps = 1e-12;
            double a = fabs(xdelta - rc.xdelta);
            double b = fabs(ydelta - rc.ydelta);
            return (a < eps) && (b < eps);
        }
        return false;
    }

};

class pointHash
{
public:
    size_t operator()(const Point& rc)const
    {
        return hash<float>()(rc.xdelta) ^ hash<float>()(rc.ydelta);
    }

};

/*
直线
k为斜率分子，b为y轴截距分子，d为分母。
当d=0时，直线平行于y轴，b为x轴截距。
*/
class Circle;

class Line {
public:
    long long k;
    long long b;
    long long d;
    double xl;

    Line(long long x1, long long y1, long long x2, long long y2);
    Line(long long a, long long _b, long long c);

    // 求两条直线的交点
    Point getIntersect(Line& geo);

    // 求直线和圆的交点
    vector<Point> getIntersect(Circle& geo);
};

/*
圆
a, b为圆心坐标，r为圆的半径
*/
class Circle {
public:
    long long a;
    long long b;
    long long r;

    Circle(long long _a, long long _b, long long _r);

    // 求直线和圆的交点
    vector<Point> getIntersect(Line& geo);

    // 求两个圆的交点
    vector<Point> getIntersect(Circle& geo);
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
    unordered_set<Point, pointHash> pointSet;
    vector<Circle> circleList;

    void parser();
    void parser(const string filename);
    void save(int x1, int y1, int x2, int y2);
    void save(int a, int b, int r);
    int calc();
};