#include <chrono>
#include <new>

using namespace std;

struct Order {
    unsigned int px;
    unsigned int entity_id;
    bool buysell; // true for buy orders

    Order() = default;
    Order(const Order &other) = default;
    Order(unsigned int p, unsigned int id, bool buy):px(p), entity_id(id), buysell(buy){}
};

struct OrderTSGateway {
    Order o;
    unsigned long long ts;
    unsigned int gateway_id;

    OrderTSGateway(char *buf, unsigned int g_id):gateway_id(g_id) {
        new ((void *)&o) Order(*((int *)buf), *((unsigned int *)(buf+sizeof(int))));
        ts = (unsigned long long)chrono::high_resolution_clock::now().time_since_epoch().count();
    }

    OrderTSGateway(OrderTSGateway &other) = default;
};
