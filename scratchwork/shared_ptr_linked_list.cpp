#include <memory>
#include <assert.h>

struct Node {
    std::shared_ptr<Node> next;
    std::shared_ptr<int> val;

    Node(int n, std::shared_ptr<Node> next):next(next) {
        val = std::shared_ptr<int>(new int);
        *val = n;
    };
};

int local_func() {

    std::shared_ptr<Node> head(new Node(0,nullptr));

    for(int i=1; i<10000; ++i) {
        std::shared_ptr<Node> tmp(new Node(i,head));
        head = tmp;
    }

    int i=9999;
    auto tmp_ptr = head;
    while(tmp_ptr) {
        assert(*(tmp_ptr->val) == i--);
        tmp_ptr = tmp_ptr->next;
    }

    return 0;
}

int main() {
    return local_func();
}

