#include <chrono>
#include <new>

using namespace std;

struct Order {
    int px;
    unsigned int entity_id;

    Order() = default;
    Order(int p, unsigned int id):px(p), entity_id(id){}
};

struct OrderTS {
    Order o;
    unsigned long long ts;

    OrderTS(char *buf) {
        new ((void *)&o) Order(*((int *)buf), *((unsigned int *)(buf+sizeof(int))));
        ts = (unsigned long long)chrono::high_resolution_clock::now().time_since_epoch().count();
    }
};
