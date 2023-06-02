//
// Created by yangzilong on 2022/11/11.
//

#include "RBTreeForMapSet.h"

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
    cout << "IsBalance:" << t1.IsBalance() << endl;
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
    cout<<t.IsBalance()<<endl;
}
int main()
{
    TestRBTree2();
    return 0;
}