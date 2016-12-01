#include <assert.h>
#include <string.h>
#include <stdbool.h>

#include "listnode.h"



#define BUFSIZE 512

void *addrHash[BUFSIZE];

size_t hashFunc(void *h[], void *a) {
    size_t hash = ((unsigned long)a>>3)%BUFSIZE;
    while(h[hash] && h[hash]!=a)
        hash = (hash+1)%BUFSIZE;
    return hash;
}

bool hashContains(void *h[], void *a) {
    return h[hashFunc(h,a)]==a;
}

void hashInsert(void *h[], void *a) {
    h[hashFunc(h,a)]=a;
    return;
}

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {
    memset(addrHash,0,sizeof(void *)*BUFSIZE);

    while(headA) {
        hashInsert(addrHash, headA);
		headA = headA->next;
    }

    while(headB) {
        if(hashContains(addrHash, headB))
            return headB;
        headB = headB->next;
    }

    return NULL;
}

int main() {
	struct ListNode h;
	h.val = 1;
	h.next = NULL;

	struct ListNode *ret = getIntersectionNode(&h,NULL);

	assert(ret == NULL);
}
