#include "Figure.hpp"
#include <iostream>

double calcUnionSquare(const std::vector<Figure *> & figures);

int main() {
	std::vector<Figure *> figures = {
		new Rectangle,
		new Trapezoid,
		new Romb
	};
	std::cout << "Inputs figures..." << std::endl;
	for (Figure * figure : figures) {
		std::cout << "Input " << figure->getFigureType() <<
			"(" << figure->getAngles() << " points): " << std::endl;
		std::cin >> *figure;
	}

	std::cout << std::endl << "Printing figures..." << std::endl;

	for (Figure * figure : figures) {
		std::cout << *figure << std::endl;
		std::cout << "-----------" << std::endl;
	}

	std::cout << std::endl << "Union square = " << calcUnionSquare(figures) << std::endl;
	std::cout << "Deleting figure with index equals 1..." << std::endl;

	figures.erase(figures.begin() + 1);

	std::cout << std::endl << "Updated figures here" << std::endl;

	for (Figure * figure : figures) {
		std::cout << *figure << std::endl;
		std::cout << "-----------" << std::endl;
	}

	for (Figure * figure : figures) {
		delete figure;
	}

	return 0;
}

double calcUnionSquare(const std::vector<Figure *> & figures) {
	double result = 0;
	for (Figure * figure : figures) {
		result += double(*figure);
	}

	return result;
}