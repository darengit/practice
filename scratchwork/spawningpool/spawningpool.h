#include <functional>
#include <mutex>
#include <condition_variable>

using namespace std;

class SpawningPool;

class Spawn {
    function<void()> bound;
    mutex m;
    condition_variable cv;
    bool complete;

public:
    template<class Function, class ... Args>
    explicit Spawn(Function f, Args ... args) {
        bound = bind(f, args ...);
        ready = false;  
    }

    void run() {
        bound();

        lock_guard<mutex> guard(m);
        complete = true;
    }

    void pool(SpawningPool *sp) {
        sp->pool(this);
    }

    void wait_for_completion() {
        unique_lock<mutex> lk(m);
        cv.wait(lk, [this]{return complete;});
    }
};
