#ifndef FIGURE_FABRIC_H_
#define FIGURE_FABRIC_H_

#include "FigureValidator.hpp"
#include "Figure.hpp"
#include "Rectangle.hpp"
#include "Romb.hpp"
#include "Trapezoid.hpp"

#include <type_traits>
#include <memory>

template<TConcretFigure T>
class FigureFabric {
public:
	static std::shared_ptr<T> createInstance(std::vector<Point> _points);
	static std::shared_ptr<T> createInstance();
};


template<TConcretFigure T>
inline std::shared_ptr<T> FigureFabric<T>::createInstance(std::vector<Point> _points) {
	_points = unificatePoints(_points);
	FigureValidator::validate(typeid(T), _points);
	return std::make_shared<T>(_points);
}

template<TConcretFigure T>
inline std::shared_ptr<T> FigureFabric<T>::createInstance() {
	return std::make_shared<T>();
}


inline std::istream & operator>>(std::istream & is, Figure & figure) {
	std::vector<Point> _points(figure.getAngles());
	for (Point & point : _points) {
		is >> point;
	}

	_points = unificatePoints(_points);
	FigureValidator::validate(typeid(figure), _points);

	figure.points = _points;
	figure.square = figure.calcSquare(figure.points);
	figure.geometryCenter = figure.calcGeometryCenter(figure.points);

	return is;
}

#endif