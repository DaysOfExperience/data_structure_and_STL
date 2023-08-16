//
// Created by yangzilong on 2022/11/15.
//


#include <utility>
#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
using namespace std;

#include "HashTable - ����.h"

void Test1() {
    size_t num = 10000000;
    srand(time(0));
    vector<int> v;
    v.reserve(num);
    for(size_t i = 0; i < num; ++i) {
        int number = rand() + i;
        v.push_back(number);
    }
    ClosedHashing::HashTable<int,int> cht;
    OpenHashing::HashTable<int,int> oht;
    unordered_map<int,int> stdht;
    map<int,int> m;

    cout<<"���룺����������"<<endl;
    size_t begin = clock();
//    for(auto&i:v)
//    {
//        cht.Insert(make_pair(i,i));
//    }
    size_t end = clock();
    cout<<"��ɢ��:"<<end-begin<<endl;

    begin = clock();
    for(auto&i:v)
    {
        oht.Insert(make_pair(i,i));
    }
    end = clock();
    cout<<"��ɢ��:"<<end-begin<<endl;
    begin = clock();
    for(auto&i:v)
    {
        stdht.insert(make_pair(i,i));
    }
    end = clock();
    cout<<"��׼���ϣ:"<<end-begin<<endl;
    begin = clock();
    for(auto&i:v)
    {
        m.insert(make_pair(i,i));
    }
    end = clock();
    cout<<"��׼������:"<<end-begin<<endl;

    cout<<"���ң�����������"<<endl;
    begin = clock();
    for(auto&i:v)
    {
        m.find(i);
    }
    end = clock();
    cout<<"��׼������:"<<end-begin<<endl;
    begin = clock();
    for(auto&i:v)
    {
        cht.Find(i);
    }
    end = clock();
    cout<<"��ɢ��:"<<end-begin<<endl;

    begin = clock();
    for(auto&i:v)
    {
        oht.Find(i);
    }
    end = clock();
    cout<<"��ɢ��:"<<end-begin<<endl;
    begin = clock();
    for(auto&i:v)
    {
        stdht.find(i);
    }
    end = clock();
    cout<<"��׼���ϣ:"<<end-begin<<endl;

}

void Test2() {
    size_t num = 1000000;
    srand(time(0));
    vector<int> v;
    v.reserve(num);
    for(size_t i = 0; i < num; ++i) {
        int number = rand() + i;
        v.push_back(number);
    }
    OpenHashing::HashTable<int,int> ht;
    for(auto&i:v)
    {
        ht.Insert(make_pair(i,i));
    }
    cout << "��ϣ�������ݸ���:" << ht.Size() << endl;
    cout << "��ϣ��ĳ���:" << ht.TableSize() << endl;
    cout << "Ͱ�ĸ���:" << ht.BucketNum() << endl;
    cout << "ƽ��ÿ��Ͱ�ĳ���:" << (double)ht.Size() / (double)ht.BucketNum() << endl;
    cout << "���Ͱ�ĳ���:" << ht.MaxBucketLength() << endl;
    cout << "��������:" << (double)ht.Size() / (double)ht.TableSize() << endl;
}

void TestHT3()
{
    int n = 25000000;
//    vector<int> v;
    set<int> v;
    srand(time(0));
    for (int i = 0; i < n; ++i)
    {
        //v.push_back(i);
        v.insert(rand() + i);  // �ظ���
        //v.push_back(rand());  // �ظ���
    }
    cout<<"��ǰ���ظ�����Ч���ݸ���Ϊ:"<<v.size()<<endl;
    size_t begin1 = clock();
    OpenHashing::HashTable<int, int> ht;
    for (auto e : v)
    {
        ht.Insert(make_pair(e, e));
    }
    size_t end1 = clock();

    cout << "��ϣ�������ݸ�������ȥ�أ�:" << ht.Size() << endl;
    cout << "��ĳ���:" << ht.TableSize() << endl;
    cout << "Ͱ�ĸ���:" << ht.BucketNum() << endl;
    cout << "ƽ��ÿ��Ͱ�ĳ���:" << (double)ht.Size() / (double)ht.BucketNum() << endl;
    cout << "���Ͱ�ĳ���:" << ht.MaxBucketLength() << endl;
    cout << "��������:" << (double)ht.Size() / (double)ht.TableSize() << endl;
}

void test_op()
{
    int n = 10000000;
    vector<int> v;
    v.reserve(n);
    srand(time(0));
    for (int i = 0; i < n; ++i)
    {
        //v.push_back(i);
        v.push_back(rand()+i);  // ?
        //v.push_back(rand());  // ?
    }

    size_t begin1 = clock();
    set<int> s;
    for (auto e : v)
    {
        s.insert(e);
    }
    size_t end1 = clock();

    size_t begin2 = clock();

    unordered_set<int> us;
//    us.reserve(n);
    //cout << us.bucket_count() << endl;
    //// us.reserve(1000);
    //us.rehash(1000);
    //cout << us.bucket_count() << endl;

    for (auto e : v)
    {
        us.insert(e);
    }
    size_t end2 = clock();

    cout <<"size:"<<s.size() << endl;

    cout << "set insert:" << end1 - begin1 << endl;
    cout << "unordered_set insert:" << end2 - begin2 << endl;


    size_t begin3 = clock();
    for (auto e : v)
    {
        s.find(e);
    }
    size_t end3 = clock();

    size_t begin4 = clock();
    for (auto e : v)
    {
        us.find(e);
    }
    size_t end4 = clock();
    cout << "set find:" << end3 - begin3 << endl;
    cout << "unordered_set find:" << end4 - begin4 << endl;


    size_t begin5 = clock();
    for (auto e : v)
    {
        s.erase(e);
    }
    size_t end5 = clock();

    size_t begin6 = clock();
    for (auto e : v)
    {
        us.erase(e);
    }
    size_t end6 = clock();

    cout << "set erase:" << end5 - begin5 << endl;
    cout << "unordered_set erase:" << end6 - begin6 << endl;

//    unordered_map<string, int> countMap;
//    countMap.insert(make_pair("?", 1));
}
int main()
{
//    ClosedHashing::TestClosedHash();
//    ClosedHashing::TestHT1();
//    Test1();
//    TestHT3();
    test_op();
    return 0;
}