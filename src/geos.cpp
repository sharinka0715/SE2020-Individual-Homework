#include "geos.h"

Line::Line(long long x1, long long y1, long long x2, long long y2) {
    d = x1 - x2;
    k = (y1 - y2);
    b = (x1 * y2 - x2 * y1);
    if (d == 0) {
        xl = INF;
    }
    else {
        xl = (double)k / d;
    }
}

Line::Line(long long a, long long _b, long long c) {
    k = a;
    b = c;
    d = _b;

    if (d == 0) {
        xl = INF;
    }
    else {
        xl = (double)k / d;
    }
}

// 求两条直线的交点
Point Line::getIntersect(Line& geo) {
    // 没有实现两条直线平行时的特判
    if (d == 0) {
        return Point(-b, k, -geo.k * b + geo.b, geo.d * k);
    }
    if (geo.d == 0) {
        return Point(-geo.b, geo.k, -k * geo.b + b, geo.k * d);
    }
    long long xu = geo.b * d - b * geo.d;
    long long yu = k * geo.b - geo.k * b;
    long long down = k * geo.d - geo.k * d;
    return Point(xu, down, yu, down);
}

// 求直线和圆的交点
vector<Point> Line::getIntersect(Circle& geo) {
    long long m = geo.a;
    long long n = geo.b;
    long long r = geo.r;
    vector<Point> tmp;
    if (d == 0) {
        long long dl = (k * m + b) * (k * m + b);
        long long dr = r * r * k * k;
        if (dl <= dr) {
            long long xu = -b;
            long long xd = k;
            long long yu = k * n;
            long long yd = xd;
            if (dl < dr) {
                double delta = sqrt((b + k * m + k * r) * (k * r - k * m - b));
                tmp.emplace_back(xu, xd, 0, yu, yd, delta / yd);
                tmp.emplace_back(xu, xd, 0, yu, yd, -delta / yd);
            }
            else {
                tmp.emplace_back(xu, xd, 0, yu, yd, 0);
            }
        }
    }
    else {
        long long dl = (k * m - d * n + b) * (k * m - d * n + b);
        long long dr = r * r * (k * k + d * d);
        if (dl <= dr) {
            long long xu = m * d * d - k * b + d * k * n;
            long long xd = d * d + k * k;
            long long yu = b * d + k * k * n + k * d * m;
            long long yd = xd;
            if (dl < dr) {
                double delta = sqrt(-b * b + 2 * b * d * n - 2 * b * k * m - d * d * n * n + d * d * r * r + 2 * d * k * m * n - k * k * m * m + k * k * r * r);
                tmp.emplace_back(xu, xd, delta * d / xd, yu, yd, delta * k / yd);
                tmp.emplace_back(xu, xd, -delta * d / xd, yu, yd, -delta * k / yd);
            }
            else {
                tmp.emplace_back(xu, xd, yu, yd);
            }
        }
    }    
    return tmp;
}


Circle::Circle(long long _a, long long _b, long long _r) {
    a = _a;
    b = _b;
    r = _r;
}

// 求直线和圆的交点
vector<Point> Circle::getIntersect(Line& geo) {
    return geo.getIntersect(*this);
}

// 求两个圆的交点
vector<Point> Circle::getIntersect(Circle& geo) {
    long long dl = (a - geo.a) * (a - geo.a) + (b - geo.b) * (b - geo.b);
    if (dl <= (r + geo.r) * (r + geo.r) && dl >= (r - geo.r) * (r - geo.r)) {
        long long xc = 2 * (geo.a - a);
        long long yc = -2 * (geo.b - b);
        long long c = a * a + b * b - r * r - geo.a * geo.a - geo.b * geo.b + geo.r * geo.r;
        Line tmp(xc, yc, c);
        return tmp.getIntersect(*this);
    }
    return vector<Point>();
}
