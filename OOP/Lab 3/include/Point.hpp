#include <iostream>
#include <cmath>

namespace Figure {
    
    using decart = std::pair<double, double>;
    using polar = std::pair<double, double>;

    class Point {
    private:
        double x;
        double y;
    public:
        Point() = default;
        Point(const decart cordinate);
        Point(const polar cordinate);
        Point(const Point & other);

        ~Point() = default;

        decart getDecart() const;
        polar getPolar() const;
        
        double getDistance(Point & other) const;
        
        Point operator+(const Point & rhs) const;
        Point operator-(const Point & rhs) const;

        friend Point operator*(int k, Point & point);
        friend Point operator*(Point & point, int k);
        friend Point operator/(Point & point, int k);

        friend std::ostream& operator<<(std::ostream& os, Point& point);
        friend std::istream& operator>>(std::istream& is, Point& point);
    };
    
    Point operator*(int k, Point & point);
    Point operator*(Point & point, int k);
    Point operator/(Point & point, int k);
    
    std::ostream& operator<<(std::ostream& os, Point& point);
    std::istream& operator>>(std::istream& is, Point& point);    
}
