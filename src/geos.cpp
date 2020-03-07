#include "geos.h"

Line::Line(double x1, double y1, double x2, double y2) {
    if (x1 == x2) { // ֱ��ƽ����y��
        k = INF;
        b = x1;
    }
    else {
        double tmp = x1 - x2;
        k = (y1 - y2) / tmp;
        b = (x1 * y2 - x2 * y1) / tmp;
    }
}

Line::Line(double a, double _b, double c) {
    if (_b == 0) { // ֱ��ƽ����y��
        k = INF;
        b = -c / a;
    }
    else {
        k = -a / _b;
        b = -c / _b;
    }
}

// ��ֱ���ϵ��xֵ���yֵ
double Line::xCalY(double x) {
    // k=INFʱ��x�㲻����y���˴�������
    return k * x + b;
}

// ��ֱ���ϵ��yֵ���xֵ
double Line::yCalX(double y) {
    if (k == INF) {
        return b;
    }
    return (y - b) / k;
}

// ������ֱ�ߵĽ���
pair<double, double> Line::getIntersect(Line& geo) {
    // û��ʵ������ֱ��ƽ��ʱ������
    if (k == INF) {
        return pair<double, double>(b, geo.xCalY(b));
    }
    if (geo.k == INF) {
        return pair<double, double>(geo.b, xCalY(geo.b));
    }
    return pair<double, double>((geo.b - b) / (k - geo.k), (geo.k * b - k * geo.b) / (geo.k - k));
}

// ��ֱ�ߺ�Բ�Ľ���
vector<pair<double, double>> Line::getIntersect(Circle& geo) {
    double c = geo.a;
    double d = geo.b;
    double r = geo.r;
    vector<pair<double, double>> tmp;
    if (k == INF) {
        if (b < c + r && b > c - r) {
            auto ys = geo.xCalY(b);
            tmp.emplace_back(b, ys.first);
            tmp.emplace_back(b, ys.second);
        }
        else if (b == c + r || b == c - r) {
            tmp.emplace_back(b, d);
        }
    }
    else {
        double distance = (k * c - d + b) / (sqrt(k * k + 1));
        if (distance <= r) {
            double pa = k * k + 1;
            double pb = 2 * (k * (b - d) - c);
            double pc = c * c + (b - d) * (b - d) - r * r;
            double p = pb * pb - 4 * pa * pc;
            if (p == 0) {
                double x = -pb / (2 * pa);
                tmp.emplace_back(x, k * x + b);
            }
            else if (p > 0) {
                double x = (-pb + sqrt(p))/ (2 * pa);
                tmp.emplace_back(x, k * x + b);
                x = (-pb - sqrt(p)) / (2 * pa);
                tmp.emplace_back(x, k * x + b);
            }
        }
    }
    return tmp;
}


Circle::Circle(double _a, double _b, double _r) {
    a = _a;
    b = _b;
    r = _r;
}

// ��Բ�ϵ��xֵ���yֵ
pair<double, double> Circle::xCalY(double x) {
    double tmp = sqrt(r * r - (x - a) * (x - a));
    return pair<double, double>(b + tmp, b - tmp);
}

// ��Բ�ϵ��yֵ���xֵ
pair<double, double> Circle::yCalX(double y) {
    double tmp = sqrt(r * r - (y - b) * (y - b));
    return pair<double, double>(a + tmp, a - tmp);
}

// ��ֱ�ߺ�Բ�Ľ���
vector<pair<double, double>> Circle::getIntersect(Line& geo) {
    return geo.getIntersect(*this);
}

// ������Բ�Ľ���
vector<pair<double, double>> Circle::getIntersect(Circle& geo) {
    double distance = (a - geo.a) * (a - geo.a) + (b - geo.b) * (b - geo.b);
    if (distance <= (r + geo.r) * (r + geo.r) && distance >= (r - geo.r) * (r - geo.r)) {
        Line tmpline(2 * (a - geo.a), 2 * (b - geo.b), geo.a * geo.a - a * a + geo.b * geo.b - b * b + r * r - geo.r * geo.r);
        return getIntersect(tmpline);
    }
    return vector<pair<double, double>>();
}
