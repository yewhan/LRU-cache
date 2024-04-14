#ifndef LRU_CACHE_HPP
#define LRU_CACHE_HPP

#include <iostream>
#include <unordered_map>

template<typename K, typename D>
class LRUCache {
    private:
        struct Node {
            K key;
            D data;
            Node* prev;
            Node* next;
        };

        std::unordered_map<K, Node*> cacheMap;
        Node* head;
        Node* tail;
        int size;

        // inline these 3 funcs?
        void removeNode(Node* node);
        void moveToHead(Node* node);
        void removeTail();

    public:
        LRUCache(int size);
        ~LRUCache();

        // inline getNode?
        std::pair<D, bool> getNode(const K& key) const;
        void putNode(const K& key, const D& data);
};

#include "lru-cache.cpp"

#endif