#include <atomic>
#include <new>
#include <algorithm>

using namespace std;

template <typename T>
class FIFOQueueSPSC {
    T *store;
    atomic<int> sz;
    size_t capacity;
    size_t head;
    size_t tail;

public:

    int mxsz;

    FIFOQueueSPSC()=default;
    FIFOQueueSPSC(size_t cap):capacity(cap), store(new T[cap]), sz(0), head(0), tail(0), mxsz(0) {}

    ~FIFOQueueSPSC() {
        delete store;
    }

    size_t size() {
        return sz;
    }

    bool empty() {
        return !sz;
    }

    bool push(const T &elt) {
        if (sz+2>capacity) return false;

        new (store+tail) T(elt);
        tail = (tail+1)%capacity;
        sz.fetch_add(1, memory_order_relaxed);

        int intsz = sz;
        mxsz = max(mxsz,intsz);

        return true;
    }

    T pop() {
        sz.fetch_sub(1, memory_order_relaxed);
        size_t old_head = head;
        head = (head+1)%capacity;
        return store[old_head];
    }
};
