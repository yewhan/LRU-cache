#include "lru-cache.hpp"

LRUCache::LRUCache(int size) : size(size) {
    // create head and tail nodes
    head = new Node();
    tail = new Node();

    // initialise head->next and tail->prev to each other
    head->next = tail;
    tail->prev = head;
}

LRUCache::~LRUCache() {
    // delete all nodes
    while (head != nullptr) { // tail->next = nullptr
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }
}