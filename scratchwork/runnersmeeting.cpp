#include <stdio.h>
#include <assert.h>
#include <vector>
#include <unordered_map>

namespace solution {
    int gcd(int a, int b) {
        if(a%b == 0)
            return b; 
        return gcd(b, a%b);
    }

    class Line {
        public:
        int yinter;
        int slope;
        Line(int y, int s):yinter(y),slope(s){}
    };

    class Rational {
        public:
        int numerator;
        int denominator;
        int sign;
        Rational(int num, int denom) {
            sign = 1;
            if(num<0){
                sign *= -1;
                num = -num;
            }
            if(denom<0){
                sign *= -1;
                denom = -denom;
            }
            int g = gcd(num, denom);
            numerator = num/g;
            denominator = denom/g;
        }
    };

    class Point {
        public:
        Rational x;
        Rational y;
        Point(const Rational &x, const Rational &y):x(x),y(y){}
    };

    inline bool parallel(const Line &l1, const Line &l2) {
        return l1.slope==l2.slope;
    }

    Point intersection(const Line &l1, const Line &l2) {
        return Point(Rational(l2.yinter-l1.yinter,l1.slope-l2.slope),
                     Rational(l1.slope*l2.yinter-l2.slope*l1.yinter,l1.slope-l2.slope));
    }
}

namespace std {
    bool operator==(const solution::Rational &a, const solution::Rational &b) {
        return a.sign==b.sign && a.numerator==b.numerator && a.denominator==b.denominator;
    }

    bool operator==(const solution::Point &a, const solution::Point &b) {
        return a.x==b.x && a.y==b.y;
    }

    template<>
    struct hash<solution::Rational> {
        size_t operator()(const solution::Rational &r) const {
            std::hash<int> h;
            return h(r.sign<<1)^h(r.numerator>>1)^h(r.denominator);
        }
    };

    template<>
    struct hash<solution::Point> {
        size_t operator()(const solution::Point &p) const {
            std::hash<solution::Rational> h;
            return h(p.x)^h(p.y);
        }
    };
}

int runnersMeetings(std::vector<int> startPosition, std::vector<int> speed) {
    std::vector<solution::Line> lines;
    for(size_t i=0; i<startPosition.size(); ++i) {
        lines.emplace_back(solution::Line(startPosition[i], speed[i]));
    }    
    
    int maxInter = 0;
    for(size_t i=0; i<lines.size(); ++i) {
        std::unordered_map<solution::Point, int> intersections;
        for(size_t j=i+1; j<lines.size(); ++j) {
            if(!parallel(lines[i],lines[j])){
                solution::Point intersect = solution::intersection(lines[i], lines[j]);
                int n = ++intersections[intersect];
                if(n > maxInter)
                    maxInter = n;
            }
        }
    }
    return maxInter+1;
}

struct A{
int i;
};

int main() {
    int m = runnersMeetings(std::vector<int> {1,4,2},std::vector<int> {27,18,24});
    assert(m==3);
}
