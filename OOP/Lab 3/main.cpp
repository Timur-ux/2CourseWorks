#include "Figure.hpp"
#include <iostream>
using namespace std;

int main() {
    Point p1(decart(1, 3));
    Point p2(decart(5, 2));
    Point p3(decart(1, 13));

    Rectangle rect(Rectangle(vector<Point>{p1, p2}));
    Rectangle rect2(move(rect));

    cout << rect << endl;
    return 0;
}