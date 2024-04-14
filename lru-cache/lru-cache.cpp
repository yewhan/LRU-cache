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

int LRUCache::getNode(const int &key) { // pass by ref
    // check if key exists in hashmap
    if (cacheMap.find(key) != cacheMap.end()) {
        Node* curr = cacheMap[key];

        // move curr to front of cache
        moveToHead(curr);
        return curr->data;
    }
}

void LRUCache::putNode(const int &key, const int &newData) {
    // check if key exists in hashmap
    if (cacheMap.find(key) != cacheMap.end()) {
        // node exists so we update data
        Node* curr = cacheMap[key];
        curr->data = newData;

        // move node to front
        moveToHead(curr);
    }
    else {
        // node doesn't exist so we create new node at front
        Node* newNode = new Node();
        newNode->key = key;
        newNode->data = newData;
        cacheMap[key] = newNode;
        
        moveToHead(newNode);

        // check if cache has reached capacity
        if (cacheMap.size() > size) {
            removeTail();
        }
    }
}

void LRUCache::removeNode(Node* node) {
    // update node->next's and node->prev's links
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

void LRUCache::moveToHead(Node* node) {
    removeNode(node);

    // update current node's links
    node->next = head->next;
    node->prev = head;

    // update head's and head->next's links 
    head->next->prev = node;
    head->next = node;
}

void LRUCache::removeTail() {
    // remove tail->prev entry from cacheMap
    cacheMap.erase(tail->prev->key);
    removeNode(tail->prev);
}