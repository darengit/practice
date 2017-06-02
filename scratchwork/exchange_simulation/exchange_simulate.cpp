//#include "exchange_simulator.h"
#include <cstdlib>

#include <queue>
#include <iostream>
#include <thread>

#include "config.h"
#include "order.h"
#include "fifo_queue_spsc.h"

using namespace std;

struct State {
    bool dispatch_complete;
    bool sequencing_complete;
};


void dispatch_orders(Order *orders, FIFOQueueSPSC<OrderTS> *gateways[], State *state) {
    for(int i=0; i<TOTAL_ORDERS; ++i)
        while(!gateways[rand()%GATEWAY_COUNT]->push(orders[i]));

    state->dispatch_complete = true;

    return;
}

struct OrderComp{
    bool operator()(const pair<OrderTS,int> &p1, const pair<OrderTS,int> &p2) {
        if(p1.first.ts<p2.first.ts || p1.first.ts==p2.first.ts && p1.second<p2.second)
            return true;
        return false;
    }
};


void sequencer(FIFOQueueSPSC<OrderTS> *gateways[], FIFOQueueSPSC<OrderTS> *sequenced, State *state) {
    priority_queue<pair<OrderTS,int>, vector<pair<OrderTS,int>>, OrderComp> sequencing_queue;
    bool sequencing_gateways[GATEWAY_COUNT] = {false};

/*
    bool sequenced_elt = true;

    while(!state->dispatch_complete || sequenced_elt) {
        sequenced_elt = false;


    }
*/


    state->sequencing_complete = true;
    return;
}


int main() {
    State *state = new State();

    FIFOQueueSPSC<OrderTS> *gateways[GATEWAY_COUNT];
    for(int i=0; i<GATEWAY_COUNT; ++i)
        gateways[i] = new FIFOQueueSPSC<OrderTS>(GATEWAY_CAPACITY);

    FIFOQueueSPSC<OrderTS> *sequenced = new FIFOQueueSPSC<OrderTS>(SEQUENCED_CAPACITY);
    
    Order *orders = new Order[TOTAL_ORDERS];
    for(int i=0; i<TOTAL_ORDERS; ++i)
        new (orders+i) Order(rand()%MAX_ORDER_PRICE, rand()%(MAX_ORDER_QUANTITY*2)-MAX_ORDER_QUANTITY, rand()%ENTITY_COUNT);



    thread sequence(sequencer, gateways, sequenced, state);

    thread dispatch(dispatch_orders, orders, gateways, state);

    dispatch.join();
    sequence.join();


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
