#ifndef LRU_CACHE_HPP
#define LRU_CACHE_HPP

#include <iostream>
#include <unordered_map>

class LRUCache {
    struct node {
        int key;
        int data;
        struct node *prev;
        struct node *next;

        node(int k, int d) : key(k), data(d), prev(nullptr), next(nullptr) {}
    };

    std::unordered_map<int, struct node> cache;
    node *head;
    node *tail;
    int size;

    public:
        LRUCache();
        ~LRUCache();

    private:


};



#endif