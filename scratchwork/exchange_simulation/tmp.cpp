#include "order.h"
#include "fifo_queue_spsc.h"
#include <cstdio>
#include <iostream>
#include <chrono>

using namespace std;

int main() {
    cout << sizeof(Order) << endl;

    chrono::time_point<chrono::high_resolution_clock> n = chrono::high_resolution_clock::now();
    cout << (unsigned long long)n.time_since_epoch().count() << endl;

    cout << sizeof(OrderTS) << endl;

    Order buf;

    FILE *f = fopen("orders.gateway0.stream", "r");
    size_t rd;
    while((rd=fread(&buf, sizeof(Order), 1, f)))
        cout << rd << " " << buf.px << " " << buf.entity_id << endl;
    fclose(f);
    return 0;
}
