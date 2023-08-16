//
// Created by yangzilong on 2022/11/15.
//
#pragma once
#include <utility>
#include <vector>
#include <iostream>
using namespace std;

// 开散列（链地址法）解决哈希表中的哈希冲突

    // 哈希表中的结点并不知道自己存储的数据类型，unordered_map为pair，unordered_set为key
    template <class T>
    struct HashNode
    {
        HashNode<T>(const T& data)
        :_data(data)
        { }
        T _data;
        HashNode* _next = nullptr;
    };

    // 哈希表的前置声明，因为迭代器中要用到
    template <class , class , class , class , class >
    class HashTable;

    // 哈希表迭代器，因为数据成员中有哈希表指针，所以这些模板参数都需要
    template <class K, class T, class KeyOfT, class Hash, class Equal>
    struct __HashTable_Iterator
    {
        typedef HashNode<T> Node;
        typedef HashTable<K, T, KeyOfT, Hash, Equal> HT;
        typedef __HashTable_Iterator<K, T, KeyOfT, Hash, Equal> Self;

        __HashTable_Iterator(Node* node, HT* ptr)
        : _node(node), _tablePtr(ptr)
        { }

        bool operator==(const Self& it) const {
            return _node == it._node;
        }

        bool operator!=(const Self& it) const {
            return _node != it._node;
        }

        T& operator*() const {
            return _node->_data;
        }

        T* operator->() const {
            return &_node->_data;
        }

        // unordered_map unordered_set为单向迭代器
        Self& operator++() {
            // 前置++
            if(_node->_next)
                _node = _node->_next;
            else {
                KeyOfT kot;
                Hash hash;
                size_t hashAddress = hash(kot(_node->_data)) % _tablePtr->_table.size();
                ++hashAddress;
                _node = nullptr;
                while(hashAddress < _tablePtr->_table.size() && (_node = _tablePtr->_table[hashAddress]) == nullptr)
                    ++hashAddress;
//                while(hashAddress < _tablePtr->_table.size() && _tablePtr->_table[hashAddress] == nullptr)
//                    ++hashAddress;
//                if(hashAddress == _tablePtr->_table.size())  //
//                    _node = nullptr;
//                else
//                    _node = _tablePtr->_table[hashAddress];
            }
            return *this;
        }
        Self operator++(int) {
            Self ret = *this;
            ++*this;
            return ret;
        }
        // 每个迭代器中的数据成员
        Node* _node;
        HashTable<K, T, KeyOfT, Hash, Equal>* _tablePtr; // 存储对应哈希表的指针
    };

    // 第一个参数为关键字，用于Find。第二个参数为开散列哈希表中每个结点存储的数据类型
    template <class K, class T, class KeyOfT, class Hash, class Equal>
    class HashTable
    {
        // 迭代器中要用到哈希表的私有数据成员，即那个哈希表(vector)的长度。
        template <typename A, class B, class C, class D, class E>
        friend struct __HashTable_Iterator;

        typedef HashNode<T> Node;
    public:
        typedef __HashTable_Iterator<K, T, KeyOfT, Hash, Equal> iterator;

        iterator begin() {
            for(size_t i = 0; i < _table.size(); ++i) {
                if(_table[i])
                    return iterator(_table[i], this);
            }
            return end();
        }

        iterator end() {
            return iterator(nullptr, this);
        }

        ~HashTable() {
            for(auto& ptr : _table) {
                Node* cur = ptr;
                while(cur) {
                    Node* next = cur->_next;
                    delete cur;
                    cur = next;
                }
                ptr = nullptr;
            }
        }

        pair<iterator, bool> Insert(const T& data) {
            KeyOfT kot;
            iterator it = Find(kot(data));
            if(it != end())
                return make_pair(it, false);
            Hash convert;

            // 负载因子到1就扩容
            if(_table.size() == 0 || 10 * _size / _table.size() >= 10) {
                // 开散列法哈希表扩容
                vector<Node*> newTable;
                size_t newSize = _table.size() == 0 ? 10 : _table.size()*2;
                newTable.resize(newSize);
                for(size_t i = 0; i < _table.size(); ++i) {
                    Node* cur = _table[i];
                    while(cur) {
                        Node* next = cur->_next;
                        size_t hashAddress = convert(kot(cur->_data)) % newTable.size();
                        cur->_next = newTable[hashAddress];
                        newTable[hashAddress] = cur;
                        cur = next;
                    }
                    _table[i] = nullptr;
//                    if(_table[i]) {
//                        Node* cur = _table[i];
//                        Node* next = cur->_next;
//                        while(cur) {
//                            size_t hashAddress = convert(cur->_kv.first) % newTable.size();
//                            cur->_next = newTable[hashAddress];
//                            newTable[hashAddress] = cur;
//                            cur = next;
//                            if(cur)
//                                next = cur->_next;
//                        }
//                        // 也没必要其实
//                        _table[i] = nullptr;
//                    }
                }
                _table.swap(newTable);
            }
            // 通过哈希函数求哈希地址
            size_t hashAddress = convert(kot(data)) % _table.size();
            Node* ptr = _table[hashAddress];
            Node* newNode = new Node(data);
            // 每个哈希桶中进行头插
            newNode->_next = ptr;
            _table[hashAddress] = newNode;
            ++_size;
            return make_pair(iterator(newNode, this), true);
        }

        // 用到了第一个模板参数
        iterator Find(const K& key) {
            Equal equal;
            if(_table.size() == 0) {
                return end();
            }
            KeyOfT kot;
            Hash convert;
            size_t hashAddress = convert(key) % _table.size();
            Node* cur = _table[hashAddress];
            while(cur) {
                if(equal(kot(cur->_data), key)) {
                    return iterator(cur, this);
                }
                cur = cur->_next;
            }
            return end();
        }

        bool Erase(const K& key) {
            if(_table.size() == 0)
                return false;
            Hash convert;
            Equal equal;
            KeyOfT kot;
            size_t hashAddress = convert(key) % _table.size();
            Node* cur = _table[hashAddress];
            Node* prev = nullptr;
            while(cur) {
                if(equal(kot(cur->_data), key)) {
                    if(prev)
                        prev->_next = cur->_next;
                    else
                        _table[hashAddress] = cur->_next;
                    delete cur;
                    --_size;
                    return true;
                }
                prev = cur;
                cur = cur->_next;
            }
            // 不存在该节点
            return false;
        }

        // 哈希表的长度
        size_t TableSize() {
            return _table.size();
        }

        // 非空哈希桶的个数
        size_t BucketNum() {
            size_t num = 0;
            for(auto&ptr:_table) {
                if(ptr)
                    num++;
            }
            return num;
        }

        // 哈希表中数据的个数
        size_t Size() {
            return _size;
        }

        // 最大的桶的长度
        size_t MaxBucketLength() {
            size_t max = 0;
            for(size_t i = 0; i < _table.size(); ++i) {
                size_t len = 0;
                Node* ptr = _table[i];
                while(ptr)
                {
                    len++;
                    ptr = ptr->_next;
                }
                if(len > max)
                    max = len;
//                if (len > 0)
//                    printf("[%d]号桶长度:%d\n", i, len);
            }
            return max;
        }
    private:
        vector<HashNode<T>*> _table;
        size_t _size = 0;
    };