//
// Created by yangzilong on 2022/11/16.
//

#pragma once

#include "HashTable.h"
namespace yzl
{
    template <class K>
    struct hash
    {
        size_t operator()(const K& key) {
            return key;
        }
    };

    // Ä£°åÌØ»¯
    template <>
    struct hash<string>
    {
        size_t operator()(const string& str) {
            size_t sum = 0;
            for(auto&ch:str)
            {
                sum*=131;
                sum+=ch;
            }
            return sum;
        }
    };

    template <class K>
    struct SetEqual
    {
        bool operator()(const K& k1, const K& k2) {
            return k1 == k2;
        }
    };

    template<class K, class Hash = hash<K>, class Equal = SetEqual<K>>
    class unordered_set {
        struct SetKeyOfT
        {
            const K& operator()(const K& key) {
                return key;
            }
        };
    public:
        typedef typename HashTable<K, K, SetKeyOfT, Hash, Equal>::iterator iterator;

        iterator begin() {
            return _table.begin();
        }

        iterator end() {
            return _table.end();
        }

        pair<iterator, bool> insert(const K& key) {
            return _table.Insert(key);
        }

    private:
        HashTable<K, K, SetKeyOfT, Hash, Equal> _table;
    };
}