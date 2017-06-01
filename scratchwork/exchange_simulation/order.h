#include <chrono>
#include <new>

using namespace std;

struct Order {
    int px; // negative px signifies a sell order
    unsigned int entity_id;

    Order() = default;
    Order(const Order &other) = default;
    Order(int p, unsigned int id):px(p), entity_id(id){}
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
