//#include "exchange_simulator.h"
#include <iostream>

#include <cstdlib>

#include <thread>

#include "config.h"
#include "order.h"
#include "fifo_queue_spsc.h"

using namespace std;

void dispatch_orders(Order *orders, FIFOQueueSPSC<OrderTS> *gateways[]) {
    for(int i=0; i<TOTAL_ORDERS; ++i)
        while(!gateways[rand()%GATEWAY_COUNT]->push(orders[i]));
    return;
}


int main() {
    FIFOQueueSPSC<OrderTS> *gateways[GATEWAY_COUNT];
    for(int i=0; i<GATEWAY_COUNT; ++i)
        gateways[i] = new FIFOQueueSPSC<OrderTS>(GATEWAY_CAPACITY);

    
    Order *orders = new Order[TOTAL_ORDERS];
    for(int i=0; i<TOTAL_ORDERS; ++i)
        new (orders+i) Order(rand()%(MAX_ORDER_PRICE*2) - MAX_ORDER_PRICE, rand()%ENTITY_COUNT);

    thread dispatch(dispatch_orders, orders, gateways);

    dispatch.join();


    for(int i=0; i<GATEWAY_COUNT; ++i)
        cout << gateways[i]->size() << endl;


    return 0;


/*
    ExchangeSimulator es;
    es.initialize_gateways();
    es.run_simulation();
    cout << es.simulation_results << endl;
    return 0;
*/
}
