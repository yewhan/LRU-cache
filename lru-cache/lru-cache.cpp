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

void LRUCache::putNode(const int &key, const int &newData) {
    // check if key exists in hashmap
    if (cacheMap.find(key) != cacheMap.end()) {
        // node exists so we update data
        Node* curr = cacheMap[key];
        curr->data = newData;

        // move node to front
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
    else {
        // node doesn't exist so we create new node at front
        Node* newNode = new Node();
        newNode->key = key;
        newNode->data = newData;
        cacheMap[key] = newNode;
        
        // move newNode to front
        // update curr->next's and curr->prev's links
        newNode->prev->next = newNode->next;
        newNode->next->prev = newNode->prev;

        // update current node's links
        newNode->next = head->next;
        newNode->prev = head;

        // update head's and head->next's links 
        head->next->prev = newNode;
        head->next = newNode;

        // check if cache has reached capacity
        if (cacheMap.size() > size) {
            // remove LEAST recently used node
            cacheMap.erase(tail->prev->key);
            
            // remove links to tail->prev
            tail->prev->prev->next = tail->prev->next;
            tail->prev->next->prev = tail->prev->prev;
        }
    }
}