#include "Validators.hpp"

using namespace geometry;

void TrapezoidValidator::validate(std::vector<Point> &_points) const {
    if(_points.size() != 4) {
        throw TrapezoidValidatorException("Trapezoid must have 4 points");
    }

    Line line1(_points[0], _points[1]);
    Line line2(_points[1], _points[2]);
    Line line3(_points[2], _points[3]);
    Line line4(_points[3], _points[0]);

    if(not(line1 || line3) and not(line2 || line4)) {
        throw TrapezoidValidatorException("Trapezoid must have 1 pair of parallel sides minimum");
    }
}

void geometry::RectangleValidator::validate(std::vector<Point> &_points) const {
    if(_points.size() != 4) {
        throw RectangleValidatorException("Rectangle must have only 4 points");
    }
     
    Line line1(_points[0], _points[1]);
    Line line2(_points[1], _points[2]);
    Line line3(_points[2], _points[3]);
    Line line4(_points[3], _points[0]);

    if(not((line1 || line3) and (line2 || line4))) {
        throw RectangleValidatorException("Rectangle must have 2 pairs of parallels line, unparallel given");
    }

    if( 
        scalarMult(line1, line2) > EPS or 
        scalarMult(line2, line3) > EPS or
        scalarMult(line3, line4) > EPS or
        scalarMult(line4, line1) > EPS
      ) {
        throw RectangleValidatorException("Rectangle must have ortogonal sides");
    }
}

void geometry::RombValidator::validate(std::vector<Point> &_points) const {
    if(_points.size() != 4) {
        throw RombValidatorException("Romb must have 4 points");
    }

    Line line1(_points[0], _points[1]);
    Line line2(_points[1], _points[2]);
    Line line3(_points[2], _points[3]);
    Line line4(_points[3], _points[0]);

    if(not(line1 || line3) or not(line2 || line4)) {
        throw RombValidatorException("Romb must have 2 pairs of parallel sides, unparallel given");
    }
}
