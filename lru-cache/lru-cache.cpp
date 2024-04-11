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

int LRUCache::getNode(const int& key) { // pass by ref
    // check if key exists in hashmap
    if (cacheMap.find(key) != cacheMap.end()) {
        Node* curr = cacheMap[key];

        // update curr->next's and curr->prev's links
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;

        // update current node's links
        curr->next = head->next;
        curr->prev = head;

        // update head's and head->next's links 
        head->next->prev = curr;
        head->next = curr;
    }
}