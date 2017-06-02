//#include "exchange_simulator.h"
#include <cstdlib>
#include <cassert>

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
    bool match_complete;
};


void dispatch_orders(Order *orders, FIFOQueueSPSC<OrderTS> *gateways[], State *state) {
    for(int i=0; i<TOTAL_ORDERS; ++i)
        while(!gateways[rand()%GATEWAY_COUNT]->push(orders[i]));

    state->dispatch_complete = true;

    return;
}

struct OrderComp{
    bool operator()(const pair<OrderTS,int> &p1, const pair<OrderTS,int> &p2) {
        if(p1.first.ts>p2.first.ts || p1.first.ts==p2.first.ts && p1.second>p2.second)
            return true;
        return false;
    }
};


void sequencer(FIFOQueueSPSC<OrderTS> *gateways[], FIFOQueueSPSC<OrderTS> *sequenced, State *state) {
    priority_queue<pair<OrderTS,int>, vector<pair<OrderTS,int>>, OrderComp> sequencing_queue;
    bool sequencing_gateways[GATEWAY_COUNT] = {false};

    while(true) {
        if(!sequencing_queue.empty()) {
            while(!sequenced->push(sequencing_queue.top().first));
            sequencing_gateways[sequencing_queue.top().second] = false;
            sequencing_queue.pop();
        }

        for(int i=0; i<GATEWAY_COUNT; ++i) {
            if(!sequencing_gateways[i] && !gateways[i]->empty()) {
                sequencing_queue.push(make_pair(gateways[i]->pop(),i));
                sequencing_gateways[i] = true;
            }
        }

        if(state->dispatch_complete) {
            bool breakout = true;
            if(!sequencing_queue.empty())
                breakout = false;
            for(int i=0; i<GATEWAY_COUNT; ++i)
                if(!gateways[i]->empty())
                    breakout = false;
            if(breakout)
                break;
        }
    }

    state->sequencing_complete = true;
    return;
}


void matcher(FIFOQueueSPSC<OrderTS> *sequenced, State *state, Order *orders) {
    int i=0;
    while(true) {
        if(!sequenced->empty()) {
            OrderTS elt = sequenced->pop();
            //assert(elt.o == orders[i]);
            if(!(elt.o == orders[i]))
                cout << i << " " << elt.ts <<  endl;


            ++i;
        }

        if(state->sequencing_complete && sequenced->empty())
            break;
    }

    state->match_complete = true;
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


    thread match(matcher, sequenced, state, orders);

    thread sequence(sequencer, gateways, sequenced, state);

    thread dispatch(dispatch_orders, orders, gateways, state);

    dispatch.join();
    sequence.join();
    match.join();

    for(int i=0; i<GATEWAY_COUNT; ++i)
        cout << gateways[i]->size() << endl;

    cout << sequenced->size() << endl;

    return 0;


/*
    ExchangeSimulator es;
    es.initialize_gateways();
    es.run_simulation();
    cout << es.simulation_results << endl;
    return 0;
*/
}
