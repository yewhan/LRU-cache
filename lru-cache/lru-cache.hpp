#ifndef LRU_CACHE_HPP
#define LRU_CACHE_HPP

#include <iostream>
#include <unordered_map>

class LRUCache {
    private:
        struct Node {
            int key;
            int data;
            Node* prev;
            Node* next;
        };

        std::unordered_map<int, Node*> cacheMap;
        Node* head;
        Node* tail;
        int size;

    public:
        LRUCache(int size);
        ~LRUCache();

};



#endif