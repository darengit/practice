#ifndef GEOMETRY_GEOMETRY_H
#define GEOMETRY_GEOMETRY_H
#include "point.h"
#include "line.h"

namespace geometry {
    inline bool parallel(const Line &l1, const Line &l2) {
        return l1.slope==l2.slope;
    }

    Point intersection(const Line &l1, const Line &l2) {
        return Point(Rational(l2.yinter-l1.yinter,l1.slope-l2.slope),
                     Rational(l1.slope*l2.yinter-l2.slope*l1.yinter,l1.slope-l2.slope));
    }
}
#endif
