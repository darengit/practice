#include <unistd.h>
#include <vector>
#include <thread>

#include "spawningpool.h"

using namespace std;

void sleep_for(int duration) {
    sleep(duration);
    return;
}

void spawn_sleep(SpawningPool *sp, int spawn_count, int sleep_duration) {
    vector<Spawn *> spawns;

    for(int i=0; i<spawn_count; ++i)
        spawns.push_back(new Spawn(sleep_for,sleep_duration));

    for(Spawn *s: spawns)
        s->pool(sp);

    for(Spawn *s: spawns) {
        s->wait_for_completion();
        delete s;
    }

    return;
}

int main() {
    SpawningPool *sp = new SpawningPool(8);

    thread t1(spawn_sleep, sp, 10, 1);
    thread t2(spawn_sleep, sp, 5, 2);

    t1.join();
    t2.join();

    return 0;
}
