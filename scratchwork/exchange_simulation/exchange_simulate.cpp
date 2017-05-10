#include "exchange_simulator.h"
#include <iostream>

using namespace std;

int main() {
    ExchangeSimulator es;
    es.initialize_gateways();
    es.run_simulation();
    cout << es.simulation_results << endl;
    return 0;
}
