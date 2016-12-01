#include <assert.h>
#include <vector>
#include <unordered_map>

#include "geometry.h"
#include "line.h"
#include "point.h"
#include "rational.h"

int maxintersection(std::vector<int> yinter, std::vector<int> slope) {
    std::vector<geometry::Line> lines;
    for(size_t i=0; i<yinter.size(); ++i) {
        lines.emplace_back(geometry::Line(yinter[i], slope[i]));
    }    
    
    int maxInter = 0;
    for(size_t i=0; i<lines.size(); ++i) {
        std::unordered_map<geometry::Point, int> intersections;
        for(size_t j=i+1; j<lines.size(); ++j) {
            if(!parallel(lines[i],lines[j])){
                geometry::Point intersect = geometry::intersection(lines[i], lines[j]);
                int n = ++intersections[intersect];
                if(n > maxInter)
                    maxInter = n;
            }
        }
    }
    return maxInter+1;
}

int main() {
    int m = maxintersection(std::vector<int> {1,4,2},std::vector<int> {27,18,24});
    assert(m==3);
}
