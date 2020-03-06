#include "geos.h"



// 输入分析
void Individual::parser() {
    int n, x1, y1, x2, y2;
    char c;
    cin >> n;
    while (n--) {
        cin >> c;
        if (c == 'L') {
            cin >> x1 >> y1 >> x2 >> y2;
            save(x1, y1, x2, y2);
        }
        else if (c == 'C') {
            cin >> x1 >> y1 >> x2;
            save(x1, y1, x2);
        }
    }
}

void Individual::save(int x1, int y1, int x2, int y2) {
    Line tmpLine(x1, y1, x2, y2);
    if (lineMap.find(tmpLine.k) == lineMap.end()) {
        lineMap.emplace(tmpLine.k, vector<Line>());
    }
    lineMap[tmpLine.k].emplace_back(tmpLine);
}

void Individual::save(int a, int b, int r) {
    circleList.emplace_back(a, b, r);
}

int Individual::calc() {
    vector<vector<Line>> lineList;

    for (auto it = lineMap.begin(); it != lineMap.end(); it++) {
        lineList.push_back(it->second);
    }

    for (auto it1 = lineList.begin(); it1 != lineList.end() - 1; it1++) {
        for (auto it2 = it1 + 1; it2 != lineList.end(); it2++) {
            for (auto l1 = it1->begin(); l1 != it1->end(); l1++) {
                for (auto l2 = it2->begin(); l2 != it2->end(); l2++) {
                    pointSet.insert(l1->getIntersect(*l2));
                }
            }
        }
    }

    return pointSet.size();
}

int main()
{
    Individual ind;
    ind.parser();
    cout << ind.calc() << endl;
}