//
// Created by yangzilong on 2022/10/9.
//


#include <stack>
#include <queue>
#include <vector>
#include <deque>
#include <list>
#include <iostream>
#include <functional>
#include "queue.h"
#include "stack.h"
#include "priority_queue.h"
using namespace std;
void test1()
{
    yzl::stack<int, vector<int>> st;
    st.push(1);
    st.push(2);
    st.push(3);
    st.push(4);
    while(! st.empty())
    {
        cout<<st.top()<<" ";
        st.pop();
    }
    cout<<endl;
    yzl::queue<int> qu;
    qu.push(1);
    qu.push(2);
    qu.push(3);
    qu.push(4);
    qu.push(5);
    while(! qu.empty())
    {
        cout<<qu.front()<<" ";
        qu.pop();
    }
    cout<<endl;
}

void test2()
{
    vector<int> v = {3,1,6,5,7,9,8,2,4};
    yzl::priority_queue<int> q(v.begin(), v.end());
    while(!q.empty())
    {
        cout<<q.top()<<" ";
        q.pop();
    }
//    yzl::priority_queue<int> qu;
//
//    qu.push(30);
//    qu.push(60);
//    qu.push(40);
//    qu.push(70);
//    qu.push(10);
//    qu.push(20);
//    qu.push(50);
//    qu.push(90);
//    while(!qu.empty())
//    {
//        cout<<qu.top()<<" ";
//        qu.pop();
//    }
}
// 简单的测试罢了
void test3()
{
    // short 2字节 16位
    unsigned short s1 = 65535;
    unsigned short s2 = 61680;
    unsigned short s3 = s1 + s2;
    cout<<s3<<endl;
}
void test4()
{
    const char* ch1 = "abc";
    const char* ch2 = "cde";
    const char* const arr[] = {ch1, ch2};
}
int main()
{
    test4();
    return 0;
}