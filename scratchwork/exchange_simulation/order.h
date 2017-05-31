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

    OrderTSGateway(char *buf) {
        new ((void *)&o) Order(*((int *)buf), *((unsigned int *)(buf+sizeof(int))));
        ts = (unsigned long long)chrono::high_resolution_clock::now().time_since_epoch().count();
    }

    OrderTSGateway(OrderTSGateway &other) = default;
};
