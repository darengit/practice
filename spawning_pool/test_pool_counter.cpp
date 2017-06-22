#include <vector>
#include <thread>
#include <atomic>

#include "spawning_pool.h"

#include <iostream>

using namespace std;

void increment(atomic<int> *i) {
    ++*i;
    return;
}

void spawn_increment(SpawningPool *sp, atomic<int> *i, int instances) {
    vector<Spawn *> spawns;

    for(int j=0; j<instances; ++j)
        spawns.push_back(new Spawn(increment,i));

    for(Spawn *s: spawns)
        sp->push(s);

    for(Spawn *s: spawns) {
        s->wait_for_completion();
        delete s;
    }

    return;
}

int main() {
    atomic<int> toIncr(0);

    SpawningPool *sp = new SpawningPool(4);

    thread t1(spawn_increment, sp, &toIncr, 300000);
    thread t2(spawn_increment, sp, &toIncr, 200000);
    thread t3(spawn_increment, sp, &toIncr, 100000);

    t3.join();
    t2.join();
    t1.join();

    cout << toIncr << endl; 

    return 0;
}
