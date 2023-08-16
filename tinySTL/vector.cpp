//
// Created by yangzilong on 2022/8/26.
//

#include<vector>
#include <iostream>
#include<algorithm>
#include<list>
#include<cassert>
#include<cstdlib>
#include "vector.h"
#include "string.h"
#include <string>
using namespace std;
//using namespace yzl;

// 2023 5 28复习vector

void t1()
{
    std::vector<double> v(10);
    for(auto&i:v)
        std::cout << i << " ";
}

int main()
{
    t1();
    return 0;
}

//================================================================
    void test_vector1() {
        vector<int> v;
        cout << v.size() << endl;
        cout << v.capacity() << endl;
        for (int i = 0; i < 10000; i++) {
            v.push_back(1);
            if (v.size() == v.capacity())
                cout << v.size() << " ";
        }
    }
    void test_vector2()
    {
        vector<int> v;
        size_t sz = v.capacity();
        cout<<sz<<endl;
        for(int i = 0; i < 10000; ++i)
        {
            v.push_back(1);
            if(sz != v.capacity())
            {
                sz = v.capacity();
                cout<<sz<<" ";
            }
        }
    }

    void test_vector3()
    {
        vector<int> v;
        v.push_back(1);
        v.push_back(2);
        v.push_back(3);
        v.push_back(4);
        v.push_back(5);
//        vector<int>::const_iterator
        vector<int>::const_iterator it = find(v.cbegin(), v.cend(), 3);
        v.insert(it, 6);
        for(const auto& i : v)
        {
            cout<<i<<" ";
        }
        cout<<endl;
    }

    void test_vector4()
    {
        vector<int> v;
        v.push_back(1);
        v.push_back(2);
        v.push_back(3);
        v.push_back(4);
        v.push_back(5);
        sort(v.begin(),v.end(),greater<int>());  // 匿名对象
        for(const auto& i: v)
        {
            cout<<i<<" ";
        }
        cout<<endl;
        less<int> ls;
        sort(v.begin(),v.end(),ls);
        for(const auto& i: v)
        {
            cout<<i<<" ";
        }
        cout<<endl;
        string s("abcde11111211231212");
        sort(s.begin(),s.end(),greater<char>());
        cout << s << endl;
    }
    void test_vector5()
    {
        vector<string> v = {"aaa","bbb","ccc"};
        string s("ddd");
        v.push_back(s);
        v.push_back(string("eee"));
        v.push_back("eee");
        for(auto& i:v)
            cout<<i<<" ";
    }
    void test_vector6()
    {
        vector<int> v1 = {1,2,3,4,5};
        vector<int> v2({1,2,3,4,5});
        vector<int> v3{1,2,3,4,5};
        for(auto&i:v1)
            cout<<i<<" ";
        cout<<endl;
        for(auto&i:v2)
            cout<<i<<" ";
        cout<<endl;
        for(auto&i:v3)
            cout<<i<<" ";
        cout<<endl;
    }

    void test_vector7()
    {
        // 和G++  非常像  而vs是非常严格的不可以。
        vector<int> v;
        v.push_back(1);
        v.push_back(2);
        v.push_back(4);
        v.push_back(3);
        v.push_back(4);
        v.push_back(5);
        vector<int>::iterator it = v.begin();
        while(it != v.end())
        {
            if(*it %2 == 0)
                v.erase(it);
            ++it;
        }
        for(auto&i:v)
        {
            cout<<i<<" ";
        }
        cout<<endl;
    }
    void test_vector8()
    {
        list<int> l;
        l.push_back(1);
        l.push_back(2);
        l.push_back(3);
        vector<int> v;
        v.resize(10);
        for(auto& i :v)
        {
            cout<<i<<" ";
        }
    }


void test1()
{
    yzl::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    for(auto&i : v)
    {
        cout<<i<<" ";
    }
    cout<<endl;
    yzl::vector<int> v2(v.cbegin(),v.cend());
    for(auto&i:v2)
        cout<<i<<" ";
    cout<<endl;
    cout<<v.size()<<v.capacity()<<endl;
    cout<<v2.size()<<v2.capacity()<<endl;
}
void test2()
{
    yzl::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.reserve(20);
    cout<<v.size()<<v.capacity()<<endl;
    v.resize(10,0);
    cout<<v.size()<<v.capacity()<<endl;
    v.resize(7,0);
    cout<<v.size()<<v.capacity()<<endl;
    for(auto&i:v)
        cout<<i<<" ";
    cout<<endl;
    // 1234500
    v.insert(v.begin(),3,2);
    for(auto&i:v)
        cout<<i<<" ";
    cout<<endl;
}
void test3()
{
    yzl::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.erase(v.begin());
    for(auto&i:v)
        cout<<i<<" ";
}
void test4()
{
    yzl::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
//    v.push_back(5);

    for (auto e : v)
    {
        cout << e << " ";
    }
    cout << endl;

    auto p = find(v.begin(), v.end(), 3);
    if (p != v.end())
    {
        // 在p位置插入数据以后，不要访问p，因为p可能失效了。
        v.insert(p, 30);

//        cout << *p << endl;
        v.insert(p, 40);
    }

    for (auto e : v)
    {
        cout << e << " ";
    }
    cout << endl;
}
void test5()
{
    yzl::vector<int> v;
    v.push_back(1);
    v.push_back(2);
//    v.push_back(4);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    auto it = v.begin();
    //   error
//    while(it != v.end())
//    {
//        if(*it %2==0)
//            v.erase(it);
//        it++;
//    }
    while(it != v.end())
    {
        if(*it % 2 == 0)
        {
            it = v.erase(it);
        }
        else
        {
            ++it;
        }
    }
    for(auto&i:v)
        cout<<i<<" ";
    cout<<endl;
}
void test6()
{
    yzl::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    int i = 6;
    while(i >= 0) {
        v.insert(v.begin(), i);
        i--;
    }
    for(auto&i:v)
        cout<<i<<" ";
//    yzl::vector<int>::iterator it = v.begin();
//    v.push_back(5);
//    cout<<*it<<endl;
}

void test7()
{
    yzl::string s("sss");
    yzl::string s2(" bbbb");
    s = s2;
}
void test8()
{
    yzl::vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);
    v1.push_back(5);
    v1.push_back(6);
    yzl::vector<std::string> v2;
    v2.push_back("aaa");
    v2.push_back("bbb");
    v2.push_back("ccc");
    yzl::vector<int> v3(v1);
    v3.push_back(7);
//    for(auto&i:v1)
//        cout<<i<<" ";
//    cout<<endl;
//    v2.reserve(7);
//    for(auto&i:v2)
//        cout<<i<<" ";
    cout<<v1.size()<<endl;
    cout<<v3.size()<<endl;
    v1.swap(v3);
    cout<<v1.size()<<endl;
    cout<<v3.size()<<endl;
}

void test9()
{
    yzl::vector<int> v;
    v.insert(v.begin(),1);
    v.insert(v.begin(),2);
    v.insert(v.begin(),3);
    v.insert(v.begin(),4);
    v.insert(v.begin(),5);
    v.insert(v.begin(),3,6);
    for(auto&i:v)
    {
        cout<<i<<" ";
    }
    cout<<endl;
    for(int i = 0; i <3; ++i)
    {
        v.erase(v.begin());
    }
    for(auto&i:v)
        cout<<i<<" ";
    cout<<endl;
}

void testa()
{
    yzl::vector<int> v;
    yzl::vector<int> v2(10,1);
    for(auto&i:v2)
    {
        std::cout<<i<<" ";
    }
    std::cout<<endl;
}

void testb() {
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
//    v.push_back(5);
    auto it = v.begin();
    while (it != v.end()) {
        if (*it % 2 == 0) {
            it = v.insert(it, 2 * *it); // 插入一个2倍值
            // 如果没有下面这个，则，无限插入，最后当insert内部扩容，这里的it还是会成为野指针。
            ++it;
        }
        ++it;
    }
    for (auto &i: v)
        cout << i << " ";
    cout<<endl;
}
void testc() {
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.push_back(6);
    v.push_back(7);
    std::vector<int>::iterator it = v.begin();
    while (it != v.end()) {
        if (*it % 2 == 0) {
            it = v.erase(it);
        } else {
            ++it;
        }
    }
    for (auto &i: v) {
        cout << i << " ";
    }
    cout << endl;
}
void testd()
{
    yzl::vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);
    v1.push_back(5);
    v1.push_back(6);
//    yzl::vector<int> v2(v1.begin(), v1.end());
    yzl::vector<int> v2(v1);
    v1[0] = 8;
    cout<<"原vector:"<<endl;
    for(auto&i:v1)
        cout<<i<<" ";
    cout<<endl;
    cout<<"新vector:"<<endl;
    for(auto&i:v2)
        cout<<i<<" ";
    cout<<endl;
}
void teste()
{
    std::vector<int> v(10,1);
    for(auto&i:v)
        cout<<i<<" ";
    cout<<endl;
}
void testf()
{
    std::vector<int> v;
    v.resize(5,0);
    for(auto&i:v)
        cout<<i<<" ";
    cout<<endl;
    v.resize(10,10);
    for(auto&i:v)
        cout<<i<<" ";
    cout<<endl;
    v.resize(20,20);
    for(auto&i:v)
        cout<<i<<" ";
    cout<<endl;
    v.resize(3);
    for(auto&i:v)
        cout<<i<<" ";
    cout<<endl;
}

//yzl::vector<yzl::vector<int>> testg()
//{
//    yzl::vector<yzl::vector<int>> v;
//    yzl::vector<int> v2(10,2);
//    v.push_back(v2);
//    v.push_back(v2);
//    v.push_back(v2);
//    v.push_back(v2);
//
//    return v;
//}

void test11()
{
    std::vector<int> v;
    v.push_back(1);
    std::vector<int>::reverse_iterator it = v.rbegin();
    cout<<*it<<endl;
}

void test12()
{
    yzl::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.push_back(6);
    yzl::vector<int>::reverse_iterator rit = v.rbegin();
    while(rit != v.rend())
    {
        cout<<*rit<<" ";
        rit++;
    }
    cout<<endl;
}
//int main()
//{
////    std::test_vector8();
////    yzl::vector<yzl::vector<int>> ret = testg();
//    test4();
//    return 0;
//}