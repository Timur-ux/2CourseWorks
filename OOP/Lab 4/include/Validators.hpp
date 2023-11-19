#pragma once

#include <typeinfo>
#include <string>

#include "Point.hpp"
#include "Line.hpp"

#include "Figure.hpp"
#include "Trapezoid.hpp"
#include "Rectangle.hpp"
#include "Romb.hpp"

template<class T>
concept TConcretFigure = std::is_base_of_v<Figure, T> && std::is_default_constructible_v<T>;

class Validator {
public:
	virtual void validate(const std::vector<Point> & _points) const = 0;
	virtual bool isAllowedFor(const std::type_info & type) const = 0;
};

class TrapezoidValidator : public Validator {
public:
	virtual void validate(const std::vector<Point> & _points) const override;
	virtual bool isAllowedFor(const std::type_info & type) const  override;
};

class RectangleValidator : public Validator {
public:
	virtual void validate(const std::vector<Point> & _points) const override;
	virtual bool isAllowedFor(const std::type_info & type) const  override;
};

class RombValidator : public Validator {
public:
	virtual void validate(const std::vector<Point> & _points) const override;
	virtual bool isAllowedFor(const std::type_info & type) const  override;
};

template <TConcretFigure T>
class FigureValidatorException : public std::exception {
	std::string message = std::string(typeid(T).name()) + "validate error";
public:
	FigureValidatorException(const char * _message) : message(_message) {}
	const char * what() const noexcept override {
		return message.c_str();
	}
};