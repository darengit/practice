#ifndef GEOMETRY_LINE_H
#define GEOMETRY_LINE_H
namespace geometry {
    struct Line {
        int yinter;
        int slope;
        Line(int y, int s):yinter(y),slope(s){}
    };
}
#endif
