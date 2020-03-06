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
    return vector<pair<double, double>>();
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
    return vector<pair<double, double>>();
}

// ������Բ�Ľ���
vector<pair<double, double>> Circle::getIntersect(Circle& geo) {
    return vector<pair<double, double>>();
}
