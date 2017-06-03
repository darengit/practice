#include <chrono>
#include <new>

using namespace std;

struct Order {
    unsigned int px;
    int qty; // negative qty signifies a sell order
    unsigned int entity_id;
    int id;

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

struct Trade {
    unsigned long long buyer_order_ts;
    unsigned long long seller_order_ts;

    unsigned int buyer_entity_id;
    unsigned int seller_entity_id;

    unsigned int qty;
    unsigned int px;


    Trade() = default;
    Trade(const OrderTS &buy, const OrderTS &sell, unsigned int quantity, unsigned int price):
        buyer_order_ts(buy.ts),
        seller_order_ts(sell.ts),
        buyer_entity_id(buy.o.entity_id),
        seller_entity_id(sell.o.entity_id),
        qty(quantity),
        px(price) {}
};
