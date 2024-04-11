#include "lru-cache.hpp"

LRUCache::LRUCache() : head(0, 0), tail(0, 0), size(0) {

}

LRUCache::~LRUCache() {
    // set current node to 2nd node
    // head & node non-dynamic so destroyed when out of scope
    Node* curr = head->next;

    // while there are still nodes left
    while (curr != tail) {
        // delete current node, then assign next node to curr
        Node* next = curr->next;
        delete curr;
        curr = next;
    }
}