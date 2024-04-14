#include "lru-cache.hpp"

template<typename K, typename D>
LRUCache<K, D>::LRUCache(int size) : size(size) {
    // create head and tail nodes
    head = new Node();
    tail = new Node();

    // initialise head->next and tail->prev to each other
    head->next = tail;
    tail->prev = head;
}

template<typename K, typename D>
LRUCache<K, D>::~LRUCache() {
    // delete all nodes
    while (head != nullptr) { // tail->next = nullptr
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }
}

template<typename K, typename D>
std::pair<D, bool> LRUCache<K, D>::getNode(const K& key) { // pass by ref
    // check if key exists in hashmap
    if (cacheMap.find(key) != cacheMap.end()) {
        Node* curr = cacheMap[key];

        // move curr to front of cache
        moveToHead(curr);
        return {curr->data, true};
    }
    // return default value if key doesn't exist
    return {D(), false};
}

template<typename K, typename D>
void LRUCache<K, D>::putNode(const K& key, const D& newData) {
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

template<typename K, typename D>
void LRUCache<K, D>::removeNode(Node* node) {
    // update node->next's and node->prev's links
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

template<typename K, typename D>
void LRUCache<K, D>::moveToHead(Node* node) {
    removeNode(node);

    // update current node's links
    node->next = head->next;
    node->prev = head;

    // update head's and head->next's links 
    head->next->prev = node;
    head->next = node;
}

template<typename K, typename D>
void LRUCache<K, D>::removeTail() {
    // remove tail->prev entry from cacheMap
    cacheMap.erase(tail->prev->key);
    removeNode(tail->prev);
}