#include "FigureFabric.hpp"
#include "main_functions.hpp"
#include <vector>
#include <iostream>

int main() {
	std::vector<std::shared_ptr<Figure>> figures = {
		FigureFabric<Rectangle>::createInstance(),
		FigureFabric<Trapezoid>::createInstance(),
		FigureFabric<Romb>::createInstance()
	};

	std::cout << "Inputs figures..." << std::endl;

	inputFigures(figures);

	std::cout << std::endl << "Printing figures..." << std::endl;

	printFigures(figures);

	std::cout << std::endl << "Union square = " << calcUnionSquare(figures) << std::endl;
	std::cout << "Deleting figure with index equals 1..." << std::endl;

	figures.erase(figures.begin() + 1);

	std::cout << std::endl << "Updated figures here" << std::endl;

	printFigures(figures);

	return 0;
}