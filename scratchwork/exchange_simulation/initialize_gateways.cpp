#include "order.h"
#include "config.h"
#include <cstdlib>
#include <cstdio>
#include <new>


#define FILE_NAME_PREFIX "orders.gateway"
#define FILE_NAME_SUFFIX ".stream"
#define MAX_ORDER_PRICE 1024*16
#define ENTITY_COUNT 128

int main() {
    char filename[64];
    Order orders[ORDERS_PER_GATEWAY_FILE];

    for(int i=0; i<GATEWAY_COUNT; ++i) {
        for(int j=0; j<ORDERS_PER_GATEWAY_FILE; ++j)
            new (orders+j) Order(rand()%(MAX_ORDER_PRICE*2) - MAX_ORDER_PRICE,
                rand()%ENTITY_COUNT);

        sprintf(filename, "%s%d%s", FILE_NAME_PREFIX, i, FILE_NAME_SUFFIX);
        FILE *f = fopen(filename, "ab+");
        fwrite(orders, sizeof(Order), ORDERS_PER_GATEWAY_FILE, f);
        fclose(f);
    }

    return 0;
}
