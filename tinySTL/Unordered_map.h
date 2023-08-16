//
// Created by yangzilong on 2022/11/16.
//

#pragma once

#include "HashTable.h"
namespace yzl
{
    template <class K>
    struct MapEqual
    {
        bool operator()(const K& k1, const K& k2) {
            return k1 == k2;
        }
    };

    // unordered_map的key需要支持转为整型，相等判断，若关键字类型不支持，可传递仿函数类。
    template<class K, class V, class Hash = hash<K>, class Equal = MapEqual<K>>
    class unordered_map {
        struct MapKeyOfT
        {
            const K& operator()(const pair<K,V>& kv) {
                return kv.first;
            }
        };
    public:
        typedef typename HashTable<K, pair<K,V>, MapKeyOfT, Hash, Equal>::iterator iterator;

        iterator begin() {
            return _table.begin();
        }

        iterator end() {
            return _table.end();
        }

        pair<iterator, bool> insert(const pair<K,V>& kv) {
            return _table.Insert(kv);
        }

        V& operator[](const K& key) {
            pair<iterator, bool> ret = _table.Insert(make_pair(key, V()));
            return ret.first->second;
        }
    private:
        HashTable<K, pair<K,V>, MapKeyOfT, Hash, Equal> _table;
    };
}