#pragma once

#include "Figure.hpp"
#include <memory>
#include <vector>

double calcUnionSquare(const std::vector<std::shared_ptr<Figure>> & figures);
void inputFigures(std::vector<std::shared_ptr<Figure>> & figures);
void printFigures(const std::vector<std::shared_ptr<Figure>> & figures);

double calcUnionSquare(const std::vector<std::shared_ptr<Figure>> & figures) {
	double result = 0;
	for (auto figure : figures) {
		result += double(*figure);
	}

	return result;
}

void inputFigures(std::vector<std::shared_ptr<Figure>> & figures) {
	for (auto figure : figures) {
		std::cout << "Input " << figure->getFigureType() <<
			" (" << figure->getAngles() << " points): " << std::endl;
		std::cin >> *figure;
	}
}

void printFigures(const std::vector<std::shared_ptr<Figure>> & figures) {
	for (auto figure : figures) {
		std::cout << std::endl << *figure << std::endl;
		std::cout << "-----------" << std::endl;
	}
}
