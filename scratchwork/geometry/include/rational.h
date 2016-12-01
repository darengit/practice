#ifndef GEOMETRY_RATIONAL_H
#define GEOMETRY_RATIONAL_H
namespace geometry {
    int gcd(int a, int b) {
        if(a%b == 0)
            return b; 
        return gcd(b, a%b);
    }

    struct Rational {
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
}

namespace std {
    bool operator==(const geometry::Rational &a, const geometry::Rational &b) {
        return a.sign==b.sign && a.numerator==b.numerator && a.denominator==b.denominator;
    }

    template<>
    struct hash<geometry::Rational> {
        size_t operator()(const geometry::Rational &r) const {
            std::hash<int> h;
            return h(r.sign<<1)^h(r.numerator>>1)^h(r.denominator);
        }
    };
}
#endif
