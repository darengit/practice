#include <functional>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include <thread>

using namespace std;

class SpawningPool;
class Spawn;

class Spawn {
    function<void()> bound;
    mutex m;
    condition_variable cv;
    bool complete;

public:
    template<class Function, class ... Args>
    explicit Spawn(Function f, Args ... args):complete(false) {
        bound = bind(f, args ...); 
    }

    void run() {
        bound();

        {
            lock_guard<mutex> guard(m);
            complete = true;
        }
        cv.notify_one();
    }

    void wait_for_completion() {
        unique_lock<mutex> lk(m);
        cv.wait(lk, [this]{return complete;});
    }
};

class SpawningPool {
    queue<Spawn *> poolQueue;
    mutex queueMutex;
    condition_variable queueCv;

    vector<thread> poolThreads;

    bool shutdown;
public:

    SpawningPool(int sz):shutdown(false) {
        poolThreads.resize(sz);
        for(thread &t: poolThreads)
            t = thread(&SpawningPool::poolThreadLoop, this);
    }

    void poolThreadLoop() {
        while(!shutdown) {
            {
                unique_lock<mutex> lk(queueMutex);
                queueCv.wait(lk, [this](){return !poolQueue.empty() || shutdown;});
            }

            Spawn *s=NULL;
            {
                lock_guard<mutex> guard(queueMutex);
                if(!poolQueue.empty()) {
                    s = poolQueue.front();
                    poolQueue.pop();
                }
            }

            if(s) s->run();
        }
    }

    void push(Spawn *s) {
        {
            lock_guard<mutex> guard(queueMutex);
            poolQueue.push(s);
        }
        queueCv.notify_one();
    }

    ~SpawningPool() {
        {
            lock_guard<mutex> guard(queueMutex);
            shutdown = true;
        }
        queueCv.notify_all();

        for(thread &t: poolThreads)
            t.join();
    }
};
