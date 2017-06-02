#include <chrono>
#include <new>

using namespace std;

struct Order {
    unsigned int px;
    int qty; // negative qty signifies a sell order
    unsigned int entity_id;

    Order() = default;
    Order(const Order &other) = default;
    Order(unsigned int p, int q, unsigned int id):px(p), qty(q), entity_id(id){}
};

namespace std {
    bool operator==(const Order &o1, const Order &o2) {
        if(o1.px != o2.px) return false;
        if(o1.qty != o2.qty) return false;
        if(o1.entity_id != o2.entity_id) return false;

        return true;
    }
}

// an order with a timestamp in nanoseconds tacked on
struct OrderTS {
    Order o;
    unsigned long long ts;

    OrderTS() = default;
    OrderTS(const OrderTS &other) = default;

    OrderTS(const Order &order):o(order) {
        ts = (unsigned long long)chrono::high_resolution_clock::now().time_since_epoch().count();
    }

};
