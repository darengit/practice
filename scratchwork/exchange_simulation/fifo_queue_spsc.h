#include <atomic>
#include <new>

using namespace std;

template <typename T>
class FIFOQueueSPSC {
    T *store;
    atomic<int> sz;
    size_t capacity;
    size_t head;
    size_t tail;

public:
    FIFOQueueSPSC()=default;
    FIFOQueueSPSC(size_t cap):capacity(cap), store(new T[cap]), sz(0), head(0), tail(1) {}

    bool empty() {
        return sz;
    }

    bool insert(T &elt) {
        if (sz>capacity-2) return false;

        new (store+tail) T(elt);
        sz.fetch_add(1, memory_order_relaxed);
        tail = (tail+1)%capacity; 
    }

    T pop() {
        sz.fetch_sub(1, memory_order_relaxed);
        size_t old_head = head;
        head = (head+1)%capacity;        
        return store[old_head];
    }
    
};
