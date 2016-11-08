#ifndef GEOMETRY_POINT_H
#define GEOMETRY_POINT_H
#include <rational.h>

namespace geometry {
    struct Point {
        Rational x;
        Rational y;
        Point(const Rational &x, const Rational &y):x(x),y(y){}
    };
}

namespace std {
    bool operator==(const geometry::Point &a, const geometry::Point &b) {
        return a.x==b.x && a.y==b.y;
    }

    template<>
    struct hash<geometry::Point> {
        size_t operator()(const geometry::Point &p) const {
            std::hash<geometry::Rational> h;
            return h(p.x)^h(p.y);
        }
    };
}
#endif
