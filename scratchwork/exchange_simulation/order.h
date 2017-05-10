#include <chrono>
#include <new>

using namespace std;

struct Order {
    int px;
    unsigned int entity_id;

    Order() = default;
    Order(Order &other) = default;
    Order(int p, unsigned int id):px(p), entity_id(id){}
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
