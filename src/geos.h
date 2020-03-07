#pragma once
#include <vector>
#include <cmath>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#define INF 300000

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
    Line(double a, double b, double c);

    // ��ֱ���ϵ��xֵ���yֵ
    double xCalY(double x);

    // ������ֱ�ߵĽ���
    pair<double, double> getIntersect(Line& geo);

    // ��ֱ�ߺ�Բ�Ľ���
    vector<pair<double, double>> getIntersect(Circle& geo);
};

/*
Բ
a, bΪԲ�����꣬rΪԲ�İ뾶
*/
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