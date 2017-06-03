//#include "exchange_simulator.h"
#include <unistd.h>

#include <cstdlib>
#include <cassert>

#include <set>
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
    for(int i=0; i<TOTAL_ORDERS; ++i) {
        while(!gateways[rand()%GATEWAY_COUNT]->push(orders[i]));

        int delay = rand()%1024;

// two different ways to submit orders
// a constant stream of orders
// and bursts of orders
//        for(int j=0; j<delay; ++j);
        if(!delay) usleep(5000);
    }

    state->dispatch_complete = true;

    return;
}

struct SequencingOrderComp{
    bool operator()(const pair<OrderTS,int> &p1, const pair<OrderTS,int> &p2) {
        if(p1.first.ts>p2.first.ts || p1.first.ts==p2.first.ts && p1.second>p2.second)
            return true;
        return false;
    }
};


void sequencer(FIFOQueueSPSC<OrderTS> *gateways[], FIFOQueueSPSC<OrderTS> *sequenced, State *state) {
    priority_queue<pair<OrderTS,int>, vector<pair<OrderTS,int>>, SequencingOrderComp> sequencing_queue;
    bool sequencing_gateways[GATEWAY_COUNT] = {false};

    while(true) {
        bool init_empty = sequencing_queue.empty();
        bool pushed_elt = false;
        for(int i=0; i<GATEWAY_COUNT; ++i) {
            if(!sequencing_gateways[i] && !gateways[i]->empty()) {
                sequencing_queue.push(make_pair(gateways[i]->pop(),i));
                sequencing_gateways[i] = true;
                pushed_elt = true;
            }
        }
        
        // this is a really tricky synchronization issue
        // if the sequencing priority queue was initially empty
        // we can't guarantee we grabbed the most recent order with a single pass
        if(init_empty && pushed_elt) {
            for(int j=0; j<GATEWAY_COUNT; ++j) {
                if(!sequencing_gateways[j] && !gateways[j]->empty()) {
                    sequencing_queue.push(make_pair(gateways[j]->pop(),j));
                    sequencing_gateways[j] = true;
                }
            }
        }

        if(!sequencing_queue.empty()) {
            while(!sequenced->push(sequencing_queue.top().first));
            sequencing_gateways[sequencing_queue.top().second] = false;
            sequencing_queue.pop();
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

struct MatchOrderComp{
    bool operator()(const OrderTS &o1, const OrderTS &o2) {
        if(o1.o.px<o2.o.px || o1.o.px==o2.o.px && o1.ts<o2.ts)
            return true;
        return false;
    }
};

void matcher(FIFOQueueSPSC<OrderTS> *sequenced, Trade *trades, State *state, Order *orders) {
    int i=0;

    set<OrderTS, MatchOrderComp> sellOrders;
    set<OrderTS, MatchOrderComp> buyOrders;


    while(true) {
        if(!sequenced->empty()) { 
            OrderTS elt = sequenced->pop();
            //assert(elt.o == orders[i]);
            if(!(elt.o == orders[i]))
                cout << i << " " << elt.o.id << " " << orders[i].id << " " <<  elt.ts <<  endl;


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
    Trade *trades = new Trade[TRADE_BUFSZ];
    
    Order *orders = new Order[TOTAL_ORDERS];
    for(int i=0; i<TOTAL_ORDERS; ++i) {
        new (orders+i) Order(rand()%MAX_ORDER_PRICE, rand()%(MAX_ORDER_QUANTITY*2)-MAX_ORDER_QUANTITY, rand()%ENTITY_COUNT);
        orders[i].id=i;
    }


    thread match(matcher, sequenced, trades, state, orders);

    thread sequence(sequencer, gateways, sequenced, state);

    thread dispatch(dispatch_orders, orders, gateways, state);

    dispatch.join();
    sequence.join();
    match.join();

    for(int i=0; i<GATEWAY_COUNT; ++i)
        cout << gateways[i]->mxsz << endl;

    cout << sequenced->mxsz << endl;

    return 0;


/*
    ExchangeSimulator es;
    es.initialize_gateways();
    es.run_simulation();
    cout << es.simulation_results << endl;
    return 0;
*/
}
