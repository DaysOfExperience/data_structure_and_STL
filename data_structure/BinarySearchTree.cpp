//
// Created by yangzilong on 2022/10/30.
//
#include<queue>
#include<string>
#include<vector>
#include<map>
#include<set>
#include<algorithm>
#include<functional>
#include "BinarySearchTree.h"
using namespace std;
void test1()
{
    BinarySearchTree<int> t;
    int a[] = {8, 3, 1, 10, 6, 4, 7, 14, 13};
    for(auto & i:a)
    {
        t.Insert_R(i);
    }
    t.InOrder();
    t.Erase_R(8);
    t.InOrder();
    t.Erase_R(14);
    t.InOrder();
    t.Erase_R(6);
    t.InOrder();
    t.Erase_R(4);
    t.InOrder();
//    t.InOrder();
//    t.Erase(8);
//    t.InOrder();
//    for(auto&i:a) {
//        t.Erase(i);
//        t.InOrder();
//    }
//    t.Erase(10);
//    t.InOrder();
//    t.Erase(3);
//    t.InOrder();
}
void test2()
{
    BinarySearchTree<int> t;
    int a[] = {8, 3, 1, 10, 6, 4, 7, 14, 13};
    for(auto & i:a)
    {
        t.Insert(i);
    }
    BinarySearchTree<int> copy = t; // 调用拷贝构造函数
    t.InOrder();
    copy.InOrder();
}
void test3()
{
    // 一些和二叉搜索树关联性不大的测试
    int a[] = {4,3,2,5,6,8,7,9,1,0};
    priority_queue<int, vector<int>, greater<int>> q(begin(a), end(a));
    while(!q.empty())
    {
        cout<<q.top()<<" ";
        q.pop();
    }
    cout<<endl;
    vector<int> v = {4,3,5,7,6,1,8,9,0,2};
    sort(v.begin(), v.end(), less<int>());
    for(auto&i:v)
    {
        cout<<i<<" ";
    }

}

void test4()
{
    int arr[] = {4,3,6,8,7,9,1,2,0,3};
    priority_queue<int> pq(begin(arr), end(arr));
    while(!pq.empty())
    {
        cout<<pq.top()<<" ";
        pq.pop();
    }
    cout<<endl;
    map<int, int> m;
    m[1];
    m[4];
    m[3];
    m[9];
    m[8];
    for(auto&i:m)
    {
        cout<<i.first<<" "<<i.second<<endl;
    }
}

void test5()
{
    BinarySearchTree<int> bst;
    int a[] = {8, 3, 1, 10, 6, 4, 7, 14, 13};
    for(auto&i:a)
        bst.Insert(i);
    bst.InOrder();
    bst.Erase_R(3);
    bst.InOrder();
}

void test6()
{
    BinarySearchTree<int> bst;
    bst.Insert(1);
    bst.Insert(2);
    bst.Insert(3);
    bst.Insert(4);
    bst.Insert(5);
    bst.Insert(6);
    bst.InOrder();
    bst.Erase_R(1);
    bst.InOrder();
}
int main()
{
    test6();
    return 0;
}