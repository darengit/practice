#include <memory>
#include <assert.h>

struct SharedNode {
    std::shared_ptr<SharedNode> next;
    std::shared_ptr<int> val;

    SharedNode(int n, std::shared_ptr<SharedNode> next):next(next) {
        val = std::shared_ptr<int>(new int(n));
    }
};

int shared_linkedlist(int n) {

    std::shared_ptr<SharedNode> head(new SharedNode(0,nullptr));

    for(int i=1; i<n; ++i) {
        std::shared_ptr<SharedNode> tmp(new SharedNode(i,head));
        head = tmp;
    }

    int i=n-1;
 
    while(head) {
        assert(*head->val == i--);
        head = head->next;
    }

    return 0;
}

struct Node {
    Node *next;
    int *val;

    Node(int n, Node *next):next(next) {
        val = new int(n);    
    }

    ~Node() {
        delete val;
    }
};

int dynamic_linkedlist(int n) {
    Node *head = new Node(0, NULL);
    for(int i=1; i<n; ++i) {
        Node *tmp = new Node(i,head);
        head = tmp;
    }

    int i=n-1;
    while(head) {
        assert(*head->val == i--);
        Node *tmp = head;
        head = head->next;
        delete tmp;
    }

    return 0;
}
