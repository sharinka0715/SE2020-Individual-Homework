#include "geos.h"
#include <string>
#include <fstream>

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

void Individual::parser(const string filename) {
    ifstream fp;
    fp.open(filename);
    int n, x1, y1, x2, y2;
    char c;
    fp >> n;
    while (n--) {
        fp >> c;
        if (c == 'L') {
            fp >> x1 >> y1 >> x2 >> y2;
            save(x1, y1, x2, y2);
        }
        else if (c == 'C') {
            fp >> x1 >> y1 >> x2;
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

    // 直线和直线
    for (auto it1 = lineList.begin(); it1 != lineList.end() - 1; it1++) {
        for (auto it2 = it1 + 1; it2 != lineList.end(); it2++) {
            for (auto l1 = it1->begin(); l1 != it1->end(); l1++) {
                for (auto l2 = it2->begin(); l2 != it2->end(); l2++) {
                    pointSet.insert(l1->getIntersect(*l2));
                }
            }
        }
    }
    if (!circleList.empty()) {
        //直线和圆
        for (auto it1 = lineList.begin(); it1 != lineList.end(); it1++) {
            for (auto l1 = it1->begin(); l1 != it1->end(); l1++) {
                for (auto l2 = circleList.begin(); l2 != circleList.end(); l2++) {
                    auto vec = l1->getIntersect(*l2);
                    for (auto elm : vec) {
                        pointSet.insert(elm);
                    }
                }
            }
        }

        //圆和圆
        for (auto l1 = circleList.begin(); l1 != circleList.end() - 1; l1++) {
            for (auto l2 = l1 + 1; l2 != circleList.end(); l2++) {
                auto vec = l1->getIntersect(*l2);
                for (auto elm : vec) {
                    pointSet.insert(elm);
                }
            }
        }
    }
    return pointSet.size();
}

int main(int argc, char* argv[])
{
    string input = "";
    string output = "";
    if (argc == 3) {
        string s1(argv[1]);
        if (s1 == "-i") {
            input = string(argv[2]);
        }
        else if (s1 == "-o") {
            output = string(argv[2]);
        }
        else {
            cout << "程序无法解析命令行参数！" << endl;
            return 0;
        }
    }
    else if (argc == 5) {
        string s1(argv[1]);
        string s2(argv[3]);
        if (s1 == s2) {
            cout << "程序无法解析命令行参数！" << endl;
            return 0;
        }
        else {
            if (s1 == "-i") {
                input = string(argv[2]);
            }
            else if (s1 == "-o") {
                output = string(argv[2]);
            }
            else {
                cout << "程序无法解析命令行参数！" << endl;
                return 0;
            }
            if (s2 == "-i") {
                input = string(argv[4]);
            }
            else if (s2 == "-o") {
                output = string(argv[4]);
            }
            else {
                cout << "程序无法解析命令行参数！" << endl;
                return 0;
            }
        }
    }
    else if (argc != 1) {
        cout << "程序无法解析命令行参数！" << endl;
        return 0;
    }
    Individual ind;
    if (input != "") {
        ind.parser(input);
    }
    else {
        ind.parser("input.txt");
    }
    
    if (output != "") {
        ofstream fp;
        fp.open(output);
        fp << ind.calc();
    }
    else {
        cout << ind.calc() << endl;
    }
    return 0;
}