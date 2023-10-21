#pragma once

#include "Point.hpp"
#include "Line.hpp"

namespace geometry {
    class Validator {
        public:
        virtual void validate(std::vector<Point> & _points) const = 0;
    };

    class TrapezoidValidator : public Validator {
    public:
        virtual void validate(std::vector<Point> & _points) const override;
    };

    class RectangleValidator : public Validator {
    public:
        virtual void validate(std::vector<Point> & _points) const override;
    };
    
    class RombValidator : public Validator {
    public:
        virtual void validate(std::vector<Point> & _points) const override;
    };

    class RectangleValidatorException : public std::exception {
        const char * message = "Rectangle validate error";
    public:
        RectangleValidatorException(const char * _message) : message(_message) {}
        const char * what() const noexcept override {
            return message;
        }
    };

    class RombValidatorException : public std::exception {
        const char * message = "Romb validate error";
    public:
        RombValidatorException(const char * _message) : message(_message) {}
        const char * what() const noexcept override {
            return message;
        }
    };

    class TrapezoidValidatorException : public std::exception {
        const char * message = "Trapezoid validate error";
    public:
        TrapezoidValidatorException(const char * _message) : message(_message) {}
        const char * what() const noexcept override {
            return message;
        }
    };
}