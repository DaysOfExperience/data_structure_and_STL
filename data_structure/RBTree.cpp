//
// Created by yangzilong on 2022/11/11.
//
#include <map>
#include <set>
#include "RBTree.h"
//#include "RBTreeForMapSet.h"

void test1()
{
    std::set<int,std::greater<int>> s;
    int array[] = { 1, 3, 5, 7, 9, 2, 4, 6, 8, 0, 1, 3, 5, 7, 9, 2, 4,
                    6, 8, 0 };
    for(auto&i:array)
    {
        auto ret = s.insert(i);
        if(ret.second == true)
        {
            std::cout << "true ";
        }
        else {
            std::cout << "false ";
        }
    }
    std::cout << std::endl;
    std::set<int>::iterator it = s.begin();
    while(it != s.end())
    {
        std::cout << *(it++) << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;
    std::set<int>::reverse_iterator rit = s.rbegin();
    while(rit != s.rend())
    {
        std::cout << *(rit++) << " ";
    }
    std::cout << std::endl;
    std::cout << s.count(3) << std::endl;
}

void test2()
{
    std::map<std::string, int> m;
    m.insert({"sss",1});
    auto it = m.begin();
    auto ret = m.insert({"sss", 2});
//    std::cout << ret.first->second;
    std::cout << m.erase("sss");
    std::cout << m.erase("sssssss");
}
void test3()
{
    std::set<int> s;
    s.insert(1);
    auto it = s.begin();
    std::cout << *it;
}

/////////////////////////////////////////////////////////////////////
void TestRBTree1()
{
    int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14, 0,5,30,25,20,4,13,30,28,27};  // 测试双旋平衡因子调节
    //int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
    RBTree<int, int> t1;
    for (auto e : a)
    {
        t1.Insert(make_pair(e, e));
    }
    t1.InOrder();
    cout << "IsBalance:" << t1.IsValidRBTree() << endl;
}
void TestRBTree2() {
    int sz = 10000;
    srand(time(0));
    RBTree<int, int> t;
    for(int i = 0; i < sz; ++i) {
        int num = rand();
        t.Insert(make_pair(num,i));
    }
    t.InOrder();
    cout<<t.IsValidRBTree()<<endl;
}
int main()
{
    TestRBTree1();
//    test2();
    return 0;
}