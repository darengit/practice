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
