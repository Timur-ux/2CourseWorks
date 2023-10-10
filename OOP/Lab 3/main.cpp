#include "Figure.hpp"
#include <iostream>

using namespace geometry;

int main() {
    Figure *figures[3] = {
        new Rectangle,
        new Trapezoid,
        new Romb
    };
    
    for(Figure * figure : figures) {
        std::cout << "Input " << figure->getFigureType() << 
                            "(" << figure->getAngles() << " points): " << std::endl;
        std::cin >> *figure;
    }

    for(Figure * figure : figures) {
        std::cout << *figure << std::endl;
        std::cout << "-----------" << std::endl;
    }
    return 0;
}