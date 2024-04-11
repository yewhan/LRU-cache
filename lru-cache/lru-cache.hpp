#ifndef LRU_CACHE_HPP
#define LRU_CACHE_HPP

#include <iostream>
#include <unordered_map>

class LRUCache {
    struct Node {
        int key;
        int data;
        struct Node *prev;
        struct Node *next;

        Node(int k, int d) : key(k), data(d), prev(nullptr), next(nullptr) {}
    };

    std::unordered_map<int, struct Node> cache;
    Node *head;
    Node *tail;
    int size;

    public:
        LRUCache();
        ~LRUCache();

    private:


};



#endif