//
// Created by yangzilong on 2022/8/13.
//

#include "string.h"
#include <string>
// 2023/5/27 ∏¥œ∞string π”√

void teststring1()
{
    std::string s1("aaaaaaa");
    std::string s2("aaaaaaa",3);
    std::string s3(s1);
    std::string s4;
    std::string s5(5,'z');
    std::string s6(s1.begin(),s1.end());
    std::cout << s1 << std::endl;
    std::cout << s2 << std::endl;
    std::cout << s3 << std::endl;
    std::cout << s4 << std::endl;
    std::cout << s5 << std::endl;
    std::cout << s6 << std::endl;
    s1 = "1111111";
    std::cout << s1 << std::endl;
    s1 += "222222";
    std::cout << s1 << std::endl;
    s1.append("333333");
    std::cout << s1 << std::endl;
    s1.push_back('4');
    s2.assign("zzzz");
    s1.insert(3, 4, 'f');
    std::cout << s1 << std::endl;
    s1.erase(1,2);
    std::cout << s1 << std::endl;
    s1.replace(1, 3, "zzzzz");
    std::cout << s1 << std::endl;
    std::cout << s2 << std::endl;
}

int main()
{
    teststring1();
    return 0;
}

// ==========================================================================================

void test_string1()
{
    yzl::string s1("yzl66666 ssss");
    cout<<s1.size()<<endl;
    for(auto it = s1.begin(); it!=s1.end(); ++it)
    {
        cout<<*it;
    }
    cout<<endl;
    for(const auto&i : s1)
        cout<<i;
    cout<<endl;
}
void test_string2()
{
    std::string s("123456",3);
    cout<<s.size()<<endl;
    cout<<s.capacity()<<endl;
    cout<<s<<endl;
}
void test_string3()
{
    yzl::string s1("111111");
    yzl::string s2(s1);
    cout<<s1.c_str()<<endl;
    cout<<s2.c_str()<<endl;
    yzl::string s3("aa");
    s3 = s1;
    cout<<s3.c_str()<<endl;
}
void test_STLstring()
{
    std::string s = "aaaaabbbbb";
//    cout<<s.capacity()<<endl;
//    s.reserve(1);
//    cout<<s.size()<<endl;
//    cout<<s.capacity()<<endl;
//    s.insert(s.size(),1,'c');
//    s.insert(0,"");
//    cout<<s.c_str()<<endl;
//    cout<<s<<endl;
//    s+='\0';
//    s+="ssssssss";
//    cout<<s.c_str()<<endl;
//    cout<<s<<endl;

    std::cin>>s;
    cout<<s<<endl;
}

void test_string4()
{
    yzl::string s("aaaaaaa");
    s.append("zazzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz");
    cout<<s.c_str()<<endl;
    cout<<s.size()<<endl;
    cout<<s.capacity()<<endl;
}

void test_string5()
{
    yzl::string s("aaaa");
    s.insert(1,3,'b');
    cout<<s.size()<<endl;
    cout<<s.c_str()<<endl;
    s.insert(0,2,'x');
    cout<<s.size()<<endl;
    cout<<s.c_str()<<endl;
    s.insert(0,"yzlll");
    cout<<s.size()<<endl;
    cout<<s.c_str()<<endl;
    s.insert(0,"");
    cout<<s.size()<<endl;
    cout<<s.c_str()<<endl;
}

void test_string6()
{
    yzl::string s("123456");
    yzl::string s2("aaazzzzzzzzzz");
    s.erase(0,2);
    s2.erase();
    cout<<s.c_str()<<endl;
    cout<<s2.c_str()<<endl;
}
void test_string7()
{
    yzl::string s("ssss");
    yzl::string s2;
//    cout<<s<<endl;
//    cout<<s2<<endl;
//    cin>>s>>s2;
//    cout<<s<<endl;
//    cout<<s2<<endl;
}


void test_new1()
{
    yzl::string s = "aaaa";
}

void test_new2()
{
    yzl::string s("aaaa");
    yzl::string s2("hahaha");
    s.append(s2);
    cout<<s.c_str()<<endl;
}
void testnnn()
{
    yzl::string s("abcs"),s2("sssss");
    cin>>s;
    cin>>s2;
    cout<<s<<endl;
    cout<<s2<<endl;
}
//int main()
//{
//    try
//    {
////        test_string7();
////        test_STLstring();
////    test_new1();
//    testnnn();
//    }
//    catch(const exception& e)
//    {
//        cout<<e.what()<<endl;
//    }
//    return 0;
//}