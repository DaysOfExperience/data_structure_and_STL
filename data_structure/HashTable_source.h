//
// Created by yangzilong on 2022/11/15.
//
#pragma once
#include <utility>
#include <vector>
#include <iostream>
using namespace std;
// 闭散列（开放定址法）解决哈希表中的哈希冲突
namespace ClosedHashing
{
    enum State
    {
        EXIST,    // 存在
        DELETE,   // 删除
        EMPTY     // 空
    };

    template <typename K, typename V>
    struct HashData
    {
        pair<K, V> _kv;
        State _state = EMPTY;
    };

    template <class K>
    struct HashAddressConvert
    {
        size_t operator()(const K& key) {
            return (size_t)key;
        }
    };

    // 模板特化
    template <>
    struct HashAddressConvert<string>
    {
        // 将string类型转换为size_t，从而使用哈希函数求得string关键字对应的哈希地址。
        size_t operator()(const string& str) {
            size_t sum = 0;
            for(auto&c:str)
            {
                sum *= 131;
                sum += c;
            }
            return sum;
        }
    };
    // 闭散列哈希表
    template <class K, class V, class HDC = HashAddressConvert<K>>
    class HashTable
    {
    private:
        // 哈希表，存储的是结构体数据
        // 不直接存储的原因是还要加一个状态值State
        vector<HashData<K, V>> _table;
        size_t _size = 0;
    public:
        bool Insert(const pair<K, V>& kv) {
            if(Find(kv.first))
                return false;
            if(_table.size() == 0 || 10*_size/_table.size() >= 7)  // 负载因子：0.7
            {
                // 负载因子越大，哈希冲突概率越高，效率越低。但是空间利用率越高
                // 负载因子越小，哈希冲突概率越小，效率越高，但是空间利用率越低
                // 哈希表需要扩容
                HashTable newHT;  // 初始时，_size == 0，调用Insert不会发生扩容。
                newHT._table.resize(_table.size() == 0 ? 10 : 2*_table.size());
                for(size_t i = 0; i < _table.size(); ++i) {
                    if(_table[i]._state == EXIST) {
                        newHT.Insert(_table[i]._kv);
                    }
                }
                _table.swap(newHT._table);
            }
            HDC convert;
            // 哈希函数求哈希地址
            size_t hashAddr = convert(kv.first) % _table.size();   // 哈希函数：除留余数法
//            int i = 0;
//            size_t start = hashAddr;
            while(_table[hashAddr]._state == EXIST) {       // 删除和不存在皆可放入新元素
                // 此处为二次探测
//                i++;
//                hashAddr = start + i^2;
                // 此处为线性探测。
                ++hashAddr;
                if(hashAddr >= _table.size())
                    hashAddr %= _table.size();
            }
            _table[hashAddr]._kv = kv;
            _table[hashAddr]._state = EXIST;
            ++_size;
            return true;
        }
        HashData<K, V>* Find(const K& key) {
            if(_table.size() == 0)
                return nullptr;
            HDC convert;
            size_t hashAddr = convert(key) % _table.size();
            size_t start = hashAddr;
//            int i = 0;
            while(_table[hashAddr]._state != EMPTY) {
                // 删除和存在都需要继续向后判断。
                if(_table[hashAddr]._state != DELETE && _table[hashAddr]._kv.first == key) {
                    return &_table[hashAddr];
                }
//                ++i;
//                hashAddr = start + i^2;
                // 线性探测
                ++hashAddr;
                if(hashAddr >= _table.size())
                    hashAddr %= _table.size();
                // 下方检测闭散列哈希表中全为DELETE的情况，线性探测和二次探测均可。
                // 但是一般而言，正常使用哈希容器时，闭散列不会出现全DELETE的情况。
                if(hashAddr == start)
                    return nullptr;
            }
            return nullptr;
        }
        bool Erase(const K& key) {
            auto ret = Find(key);
            if(ret) {
                --_size;
                ret->_state = DELETE;
                return true;
            }
            else
                return false;
//            if(_table.size() == 0)
//                return false;
//            HDC convert;
//            size_t hashAddr = convert(key) % _table.size();
//            size_t start = hashAddr;
//            while(_table[hashAddr]._state != EMPTY) {
//                if(_table[hashAddr]._state != DELETE && _table[hashAddr]._kv.first == key) {
//                    _table[hashAddr]._state = DELETE;
//                    --_size;
//                    return true;
//                }
//                ++hashAddr;
//                if(hashAddr == _table.size())
//                    hashAddr = 0;
//                if(hashAddr == start)
//                    return false;
//            }
//            return false;
        }
        void Print() {
            for(size_t i = 0; i < _table.size(); ++i) {
                if(_table[i]._state == EXIST) {
                    cout<<"["<<_table[i]._kv.first<<":"<<_table[i]._kv.second<<"  --  "<<i<<"]"<<endl;
                }
                else {
                    printf("[****    -- %d]\n", i);
                }
            }
        }
    };

    void TestClosedHash() {
        HashTable<string, int> ht;
        string arr[] = { "苹果", "西瓜", "苹果", "西瓜", "苹果", "苹果", "西瓜", "苹果", "香蕉", "苹果", "香蕉" };
        for(auto&s:arr)
        {
            if(ht.Find(s))
                ht.Find(s)->_kv.second++;
            else
                ht.Insert(make_pair(s,1));
        }
        ht.Print();
    }
    void TestHT1()
    {
        //int a[] = { 1, 11, 4, 15, 26, 7, 44, 9 };
        int a[] = { 1, 11, 4, 15, 26, 7, 44 };
        HashTable<int, int> ht;
        for (auto e : a)
        {
            ht.Insert(make_pair(e, e));
        }

        ht.Print();
        cout<<endl;
        ht.Erase(4);
        cout << ht.Find(44)->_kv.first << endl;
        cout << ht.Find(4) << endl;
        ht.Print();
        cout<<endl;
        ht.Insert(make_pair(-2, -2));
        ht.Print();

        cout << ht.Find(-2)->_kv.first << endl;
    }
}

// 开散列（链地址法）解决哈希表中的哈希冲突
namespace OpenHashing
{
    // 这里仅仅是实现哈希表的最简单逻辑，Find等函数的实现没有考虑unordered_map等容器
    template <class K, class V>
    struct HashNode
    {
        HashNode<K,V>(const pair<K,V>& kv)
        :_kv(kv)
        { }
        pair<K, V> _kv;
        HashNode* _next = nullptr;
    };

    template <class K>
    struct HashAddressConvert
    {
        size_t operator()(const K& key) {
            return key;
        }
    };

    // 模板特化
    template <>
    struct HashAddressConvert<string>
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

    template <class K, class V, class HDC = HashAddressConvert<K>>
    class HashTable
    {
        typedef HashNode<K, V> Node;
    private:
        vector<HashNode<K, V>*> _table;
        size_t _size = 0;
    public:
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
        bool Insert(const pair<K, V>& kv) {
            if(Find(kv.first)) {
                return false;
            }
            HDC convert;
            if(_table.size() == 0 || 10 * _size / _table.size() >= 10) {
                // 开散列法哈希表扩容
                vector<Node*> newTable;
                size_t newSize = _table.size() == 0 ? 10 : _table.size()*2;
                newTable.resize(newSize);
                for(size_t i = 0; i < _table.size(); ++i) {
                    Node* cur = _table[i];
                    while(cur) {
                        Node* next = cur->_next;
                        size_t hashAddress = convert(cur->_kv.first) % newTable.size();
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
            // 通过哈希函数求哈希地址(除留余数法
            size_t hashAddress = convert(kv.first) % _table.size();
            Node* ptr = _table[hashAddress];   // 哈希桶
            Node* newNode = new Node(kv);
            // 每个哈希桶中进行头插
            newNode->_next = ptr;
            _table[hashAddress] = newNode;   // 这里并没有哨兵位（头结点）
            ++_size;
            return true;
        }

        Node* Find(const K& key) {
            if(_table.size() == 0) {
                return nullptr;
            }
            HDC convert;
            size_t hashAddress = convert(key) % _table.size();
            Node* cur = _table[hashAddress];
            while(cur) {
                if(cur->_kv.first == key) {
                    return cur;
                }
                cur = cur->_next;
            }
            return nullptr;
        }

        bool Erase(const K& key) {
            if(_table.size() == 0)
                return false;
            HDC convert;
            size_t hashAddress = convert(key) % _table.size();
            Node* cur = _table[hashAddress];
            Node* prev = nullptr;
            while(cur) {
                if(cur->_kv.first == key) {
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
                if(ptr) num++;
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
                while(ptr) {
                    ++len;
                    ptr = ptr->_next;
                }
                if(len > max)   max = len;
//                if(len > 0)  printf("[%d]号桶长度:%d\n", i, len);
            }
            return max;
        }
    };
}