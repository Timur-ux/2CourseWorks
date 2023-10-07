#pragma once

#include "Figure.hpp"
#include "FigureBuilder.hpp"

namespace Figure {
    class Rectangle : public Figure {
    private:
        std::string figureType = "Rectangle";
        int angles = 2;
    public:
        Rectangle() = default;
        Rectangle(std::vector<Point> & _points);
        
        virtual void setPoints(std::vector<Point> & _points) override;

        virtual Point getCenter() const override;
        virtual operator double() const override;

        virtual Figure & operator=(const Figure &rhs) override;
        virtual Figure & operator=(Figure && rhs) override;
    
        virtual bool operator==(const Figure & rhs) const;
    };

    class RectangleBuilder : public FigureBuilder {
    private:
        Figure* rectangle;
    public:
        RectangleBuilder() : rectangle(new Rectangle) {};

        virtual FigureBuilder * setPoints(std::vector<Point> & _points) override;
        virtual Figure* getFigure() override;
    };
}