//
// Created by yangzilong on 2022/11/8.
//

#include "AVLTree.h"

void TestAVLTree1() {
    int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
    AVLTree<int, int> t;
    for(auto& i:a)
        t.Insert(make_pair(i,i));
    t.InOrder();
    if(t.IsBalance() == true) {
        cout<<"平衡"<<endl;
    }
    else {
        cout<<"否平衡"<<endl;
    }
}
void TestAVLTree2() {
    int sz = 10000;
    srand(time(nullptr));
    AVLTree<int, int> t;
    for(int i = 0; i < sz; ++i) {
        int num = rand();
        t.Insert(make_pair(num,num));
    }
    t.InOrder();
    cout<<t.IsBalance()<<endl;
}
int main()
{
    TestAVLTree2();
    return 0;
}