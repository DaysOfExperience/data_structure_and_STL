//
// Created by yangzilong on 2022/9/28.
//

#include "list.h"
#include <iostream>
#include <list>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;

void t1()
{
    int array[10] = {1,2,3,4,5,6,7,8,9,0};
    std::list<int> ls(array, array + sizeof array / sizeof array[0]);
    std::cout << ls.front() << std::endl;
    std::cout << ls.back() << std::endl;
    std::cout << ls.size() << std::endl;
    ls.push_front(123);
    ls.pop_back();
    std::list<int>::iterator it = ls.begin();
    while(it != ls.end())
    {
        std::cout << *it << " ";
        it++;
    }
    std::cout << std::endl;
    for(auto & i : ls)
    {
        std::cout << i << " ";
    }
}

void t2()
{
    yzl::list<int> ls;
    ls.push_back(1);
    ls.push_back(1);
    ls.push_back(1);
    ls.push_back(1);
    ls.push_back(1);
    ls.show();
    ls.clear();
    std::cout  << "  asdasds"<< ls.size() << std::endl;
    ls.show();
    yzl::list<int> ls2(ls);
    ls2.show();
}

int main()
{
//    t1();
//    int i = int();
//    std::cout << i << std::endl;
    t2();
    return 0;
}

// ===============================================================================

void test_list1() {
    list<int> ls={1,2,3,4,5,6,7,8,9,10};
    list<int>::iterator it = find(ls.begin(), ls.end(), 4);
    if(it != ls.end())
    {
        ls.insert(it, 66);
        it = ls.insert(it,77);
        ls.insert(it,88);
    }
    for(auto & i : ls)  cout<<i<<" ";  cout<<endl;
    it = ls.begin();
    while(it != ls.end())
    {
        if(*it % 2 == 0)
        {
            it = ls.erase(it);
        }
        else {
            ++it;
        }
    }
    for(auto & i : ls)  cout<<i<<" ";  cout<<endl;
}

void test_list2() {
    // test constructor
    list<int> ls1;
    list<int> ls2(5,6);
    ls1.assign({1,2,3,4,5,6});
    for(auto & i : ls1) cout<<i<<" "; cout<<endl;
    ls2.push_back(7);
    ls2.push_back(8);
    ls2.push_back(9);
    for(auto & i : ls2) cout<<i<<" "; cout<<endl;
    ls2.push_front(3);
    ls2.push_front(2);
    ls2.push_front(1);
    for(auto & i : ls2) cout<<i<<" "; cout<<endl;
}

void test_list3() {
    // test insert & erase
    list<int> ls_tmp = {1,2,3,4,5,6}; // 这里本应该是先构造，再拷贝，但是编译器优化为直接构造
    list<int> ls({1,2,3,4,5,6,7});
    // 在所有的奇数之前插入一个888
    list<int>::iterator it = ls.begin();
    while(it != ls.end()) {
        if(*it % 2 == 1) {
            it = ls.insert(it,{8,5,7});
            it++;
            it++;
            it++;
            it++;
        }
        else {
            it++;
        }
    }
    for(auto&i:ls) cout<<i<<" "; cout<<endl;
    ls.remove(8);
    for(auto&i:ls) cout<<i<<" "; cout<<endl;
    // 删除所有偶数
    it = ls.begin();
    while(it != ls.end()) {
        if(*it % 2 == 0) {
            it = ls.erase(it);
        }else {
            ++it;
        }
    }
    for(auto&i:ls) cout<<i<<" "; cout<<endl;
}

void test_list4() {
    list<int> ls = {1, 2, 3, 4, 5, 6};
    list<int>::iterator it = find(ls.begin(), ls.end(), 4);
    it = ls.erase(it);
    cout << *it << endl;
    for (auto &i: ls) cout << i << " ";
    cout << endl;
}

void test_list5() {
    list<int> ls = {1, 2, 3, 4, 5, 6};
    list<int>::iterator it = ls.begin();
    cout<<ls.size()<<endl;
    while(it != ls.end()) {
        it = ls.erase(it);
    }
    cout<<ls.size()<<endl;
}
void test_list6() {
    list<int> ls = {1,2,3,4,5};
    ls.clear();
    list<int> ls2;
    cout<<ls2.front()<<endl;
}
struct Pos
{
    Pos(int r = 0,int c = 0)
    :row(r),col(c)
    {

    }
    int row;
    int col;
};
void test1()
{
    Pos p1(10,20);
    Pos p2(30,40);
    yzl::list<Pos> ls;
    ls.push_back(p1);
    ls.push_back(p2);
    yzl::list<Pos>::iterator it = ls.begin();
    while(it != ls.end())
    {
//        cout<<(*it).row<<" "<<(*it).col<<endl;
        cout<<it->row<<" "<<it->col<<endl;
        it++;
    }
    cout<<endl;
}

void test2()
{
    yzl::list<int> ls;
    ls.push_back(1);
    ls.push_back(2);
    ls.push_back(3);
    ls.push_back(4);
    ls.push_back(5);

    yzl::list<int>::iterator it = ls.begin();
    ++it;
    ++it;
    ++it;
    int n = 77;
    while(n != 55)
    {
        it = ls.insert(it, n);
        n -= 11;
    }
    for(auto&i:ls)
    {
        cout<<i<<" ";
    }
    cout<<endl;
}
void test3()
{
    yzl::list<int> ls;
    ls.push_back(1);
    ls.push_back(2);
    ls.push_back(3);
    ls.push_back(4);
    yzl::list<int>::iterator it = find(ls.begin(), ls.end(), 2);
    ls.insert(it, 0);
    for(auto& i:ls)
        cout<<i<<" ";
    cout<<endl;
}

void test4()
{
    // 测试一下STL中的list的迭代器
    yzl::list<int> ls;
    ls.push_back(1);
    ls.push_back(2);
    ls.push_back(3);
    ls.push_back(4);
    ls.push_back(5);
    ls.show();
    ls.clear();
    cout<<ls.size()<<endl;
}
void test5()
{
    yzl::list<int> ls;
    ls.push_back(1);
    ls.push_back(2);
    ls.push_back(3);
    ls.push_back(4);
    ls.push_back(5);
    yzl::list<int> fuzhi;
    fuzhi = ls;
    ls.show();
    fuzhi.show();
    ls.push_back(111);
    fuzhi.show();
}
void test6()
{
    yzl::list<int> ls;
    ls.push_back(1);
    ls.push_back(1);
    ls.push_back(1);
    ls.push_back(1);
    ls.push_back(1);
    yzl::list<int> ls2;
    ls2.push_back(2);
    ls2.push_back(2);
    ls2.push_back(2);
    ls2.push_back(2);
    ls2.push_back(2);
    ls.swap(ls2);
    ls.show();
    ls2.show();
}
void test7()
{
    yzl::list<int> ls;
    ls.push_back(1);
    ls.push_back(2);
    ls.push_back(3);
    ls.push_back(4);
    ls.push_back(5);
    yzl::list<int> ls2(ls);
    ls.push_back(6);
    ls2.show();
}
void test8()
{
    queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    q.push(5);
    q.pop();
    cout<<q.front()<<endl;
    cout<<q.back()<<endl;
}
class Solution {
public:
    bool IsPopOrder(vector<int> pushV,vector<int> popV) {
        queue<int> qu;
        stack<int> st;
        for(auto &i : popV)
        {
            qu.push(i);
        }
        for(int i = 0; i < pushV.size(); ++i)
        {
            if(st.empty() || st.top() != qu.front())
            {
                st.push(pushV[i]);
            }
            while(!st.empty() && st.top() == qu.front())
            {
                st.pop();
                qu.pop();
            }
        }
        // true会出循环，且queue是空的
        // false会出循环，且queue不空
        if(qu.empty())
            return true;
        return false;
    }
};

void test9()
{
    stack<int,vector<int>> st;
    st.push(1);
    st.push(1);
    st.push(1);
    st.push(1);
    st.push(1);
    cout<<st.size()<<endl;
}

void test10()
{
    yzl::list<int> ls;
    ls.push_back(1);
    ls.push_back(2);
    ls.push_back(3);
    ls.push_back(4);
    ls.push_back(5);
    ls.push_back(6);
    yzl::list<int>::reverse_iterator it  = ls.rbegin();
    while(it != ls.rend())
    {
        cout<<*it<<" ";
        ++it;
    }
}
struct Date
{
    Date()
    {

    }
    Date(int _year, int _month, int _day)
    :year(_year), month(_month), day(_day)
    {

    }
    int year;
    int month;
    int day;
};
void test11()
{
    yzl::list<Date> ls;
    ls.push_back(Date(2001,1,1));
    ls.push_back(Date(2002,2,2));
    yzl::list<Date>::reverse_iterator rit = ls.rbegin();

    cout<<rit.operator->()->year<<endl;
    cout<<rit->year<<endl;

}
//int main()
//{
//    test11();
//    return 0;
//}