#pragma once
#include <vector>

using namespace std;

/*
ֱ��
kΪб�ʣ�bΪy��ؾࡣ
��k=INFʱ��ֱ��ƽ����y�ᣬbΪx��ؾࡣ
*/
class Circle;

class Line {
public:
    double k;
    double b;

    Line(double x1, double y1, double x2, double y2);

    // ��ֱ���ϵ��xֵ���yֵ
    double xCalY(double x);

    // ��ֱ���ϵ��yֵ���xֵ
    double yCalX(double y);

    // ������ֱ�ߵĽ���
    pair<double, double> getIntersect(Line& geo);

    // ��ֱ�ߺ�Բ�Ľ���
    vector<pair<double, double>> getIntersect(Circle& geo);
};

class Circle {
public:
    double a;
    double b;
    double r;

    Circle(double _a, double _b, double _r);

    // ��Բ�ϵ��xֵ���yֵ
    pair<double, double> xCalY(double x);

    // ��Բ�ϵ��yֵ���xֵ
    pair<double, double> yCalX(double y);

    // ��ֱ�ߺ�Բ�Ľ���
    vector<pair<double, double>> getIntersect(Line& geo);

    // ������Բ�Ľ���
    vector<pair<double, double>> getIntersect(Circle& geo);
};