//
// Created by yangzilong on 2022/9/28.
//

#ifndef STL_LIST_H
#define STL_LIST_H

#include <cstddef>   // size_t
#include <cassert>
#include <iostream>
#include "reverse_iterator.h"
//using namespace std;
namespace yzl
{
    template<class T>
    struct list_node  // list内部使用的结点类型
    {
    public:
        T _data;
        list_node<T>* _next;
        list_node<T>* _prev;
    public:
        list_node(const T& data = T())  // 结点的默认构造函数
        : _data(data), _next(nullptr), _prev(nullptr)
        { }
//        ~list_node() = default;
//        // 拷贝构造，其实没必要
//        list_node(const list_node<T>& node)
//        : _data(node._data), _next(node._next), _prev(node._prev)  // 浅拷贝
//        { }
//        // 赋值运算符重载，也没必要
//        list_node<T>& operator=(const list_node<T>& node)  // 浅拷贝
//        {
//            _data = node._data;
//            _prev = node._prev;
//            _next = node._next;
//            return *this;
//        }
    };

    // 说真的，只是对结点指针的一个封装罢了，构造函数也是通过一个结点指针即可构造出一个迭代器。
    // 对于迭代器的操作，其实也就是++ -- 然后解引用。目前的操作就是这些，之后再有再补充吧。
    template<class T, class Ref, class Ptr> // T&  T*  or  const T& const T*
    class __list_iterator  // 成员就是一个结点指针
    {
    public:
        typedef list_node<T> Node;  // 这是一个结构体，结点。Node就是一个结点结构体。
        typedef __list_iterator<T, Ref, Ptr> iterator;

        typedef std::bidirectional_iterator_tag iterator_category;
        typedef T value_type;
        typedef Ptr pointer;
        typedef Ref reference;
        typedef ptrdiff_t difference_type;
    public:
        Node* _node;  // 这个迭代器类型有一个数据成员，是结点指针。
    public:
        __list_iterator(Node* node)
        :_node(node)
        { }
        // 这个类型的实例化对象本身不支持解引用操作，operator*赋予了它解引用之后的操作。
        Ref operator*()
        {
            return _node->_data;
        }
        Ptr operator->()
        {
            return &(operator*());
//            return &(_node->_data);
        }
        bool operator!=(const iterator& it)
        {
            return _node != it._node;
        }
        bool operator==(const iterator& it)
        {
            return _node == it._node;
        }
        // 思考一下迭代器++，普通迭代器和const迭代器其实都可以++
        iterator& operator++() // 前置
        {
            _node = _node->_next;
            return *this;
        }
        iterator operator++(int)  // 后置
        {
            iterator tmp = *this;
            this->_node = this->_node->_next;
            return tmp;
        }

        iterator& operator--()
        {
            _node = _node->_prev;
            return *this;
        }
        iterator operator--(int)
        {
            iterator tmp(*this);
            this->_node = this->_node->_prev;
            return tmp;
        }
    };
//    template<typename T, typename Ref, typename Ptr, typename iterator = __list_iterator<T, Ref, Ptr> >
//    class __list_reverse_iterator
//    {
//    public:
//        typedef __list_reverse_iterator<T, Ref, Ptr, iterator> reverse_iterator;
//        typedef list_node<T> Node;
//
//    public:
//        __list_reverse_iterator(Node* p)
//        :it(p)
//        {
//        }
//        Ref operator*()
//        {
//            return *it;
//        }
//        Ptr operator->()
//        {
//            return it.operator->();
//        }
//        bool operator==(reverse_iterator rit)
//        {
//            return it == rit.it;
//        }
//        bool operator!=(reverse_iterator rit)
//        {
//            return it != rit.it;
//        }
//        reverse_iterator& operator++()
//        {
//            --it;
//            return *this;
//        }
//        reverse_iterator operator++(int)
//        {
//            auto ret = *this;
//            --it;
//            return ret;
//        }
//        reverse_iterator& operator--()
//        {
//            ++it;
//            return *this;
//        }
//        reverse_iterator operator--(int)
//        {
//            auto ret = *this;
//            ++it;
//            return ret;
//        }
//    private:
//        iterator it;
//    };

    // list<int> ls;
    template<class T>
    class list
    {
    private:
        typedef list_node<T> Node;
        Node* _head;    // list_node<T>* _head;  头节点

    public:
        // 说真的，关于list的迭代器，你只需要实现begin end这一系列的即可，还要让它的返回值支持++ 解引用操作，这就够了，说真的。
        typedef __list_iterator<T, T&, T*> iterator;   // 这个结构体别名为迭代器，本身是不支持解引用操作的。
        //typedef const __list_iterator<T> const_iterator;  // 你这里const修饰的是迭代器类型，他有结点指针数据成员，const使得结点指针不能改变。这就不对了。
        // 但是根本上，const迭代器是指不能修改*迭代器所指的值。而不是迭代器本身!!!
        typedef __list_iterator<T, const T&, const T*> const_iterator;

//        typedef __list_reverse_iterator<T, T&, T*> reverse_iterator;
//        typedef __list_reverse_iterator<T, const T&, const T*> const_reverse_iterator;
        typedef __reverse_iterator<__list_iterator<T, T&, T*>, T&, T*> reverse_iterator;
        typedef __reverse_iterator<const_iterator, const T&, const T*> const_reverse_iterator;
        iterator begin()
        {
            return iterator(_head->_next);
        }
        iterator end()
        {
            return iterator(_head);
        }
        const_iterator begin() const
        {
            return const_iterator(_head->_next);
        }
        const_iterator end() const
        {
            return const_iterator(_head);
        }
        const_iterator cbegin() const
        {
            return const_iterator(_head->_next);
        }
        const_iterator cend() const
        {
            return const_iterator(_head);
        }
        reverse_iterator rbegin()
        {
            return reverse_iterator(end());
        }
        reverse_iterator rend()
        {
            return reverse_iterator(begin());
        }
        const_reverse_iterator rbegin() const
        {
            return const_reverse_iterator(end());
        }
        const_reverse_iterator rend() const
        {
            return const_reverse_iterator(begin());
        }
        const_reverse_iterator crbegin() const
        {
            return const_reverse_iterator(end());
        }
        const_reverse_iterator crend() const
        {
            return const_reverse_iterator(begin());
        }
    public:
        list() {   // list的默认构造函数
            _head = new Node;   // 调用list_node<T>的默认构造函数，头节点里面的data是随机数（其实也不是，使用的是T类型的默认构造
                                // 所以，你也可以理解为int，double都有了默认构造，为了符合这些场景的使用
            _head->_next = _head;
            _head->_prev = _head;
        }
        ~list()
        {
            clear();
            delete _head;
            _head = nullptr;
        }
        void empty_init()
        {
            _head = new Node;
            _head->_next = _head;
            _head->_prev = _head;
        }
        template<class InputIterator>
        list(InputIterator first, InputIterator last)
        {
            empty_init();
            while(first != last)
            {
                push_back(*first);
                ++first;
            }
        }
        // 拷贝构造函数现代写法
        list(const list<T>& ls)
        {
            empty_init();
            list<T> tmp(ls.begin(), ls.end());
            this->swap(tmp);
        }
//        list(const list<T>& ls)
//        :_head(new Node)
//        {
//            _head->_next = _head;
//            _head->_prev = _head;
//            for(auto&i:ls)
//            {
//                Node* newnode = new Node(i);
//                Node* tail = _head->_prev;
//                tail->_next = newnode;       // 尾插!!!!!!或者对ls的倒着遍历，进行头插，哈哈哈。
//                newnode->_prev = tail;
//                newnode->_next = _head;
//                _head->_prev = newnode;
//            }
//        }
        // ls1 = ls2
        list<T>& operator=(list<T> ls)
        {
            this->swap(ls);
            return *this;
        }
    public:
        void push_back(const T& val)
        {
            Node* newnode = new Node(val);
            Node* tail = _head->_prev;

            tail->_next = newnode;
            newnode->_prev = tail;
            newnode->_next = _head;
            _head->_prev = newnode;
        }
        void push_front(const T& val)
        {
            // 复习：一个很简单的push_front，其实就是四个指针的改变而已。
            Node* newnode = new Node(val);
            Node* first = _head->_next;

            _head->_next = newnode;
            newnode->_prev = _head;
            newnode->_next = first;
            first->_prev = newnode;
        }
        iterator insert(iterator position, const T& val)
        {
            Node* cur = position._node;
            Node* prev = cur->_prev;
            Node* newnode = new Node(val);

            prev->_next = newnode;
            newnode->_prev = prev;
            newnode->_next = cur;
            cur->_prev = newnode;

            return iterator(newnode);
        }
        iterator erase(iterator position)
        {
            assert(position._node != _head);

            Node* cur = position._node;
            Node* prev = cur->_prev;
            Node* next = cur->_next;

            prev->_next = next;
            next->_prev = prev;
            delete cur;

            return iterator(next);
        }
        void pop_back()
        {
            assert(size() > 0);
            Node* tail = _head->_prev;
            Node* newtail = tail->_prev;
            newtail->_next = _head;
            _head->_prev = newtail;
            delete tail;
        }
        void pop_front()
        {
            assert(size() > 0);
            Node* front = _head->_next;
            Node* newfront = _head->_next->_next;
            _head->_next = newfront;
            newfront->_prev = _head;
            delete front;
        }
        void show() const
        {
            Node* tmp = _head->_next;
            while(tmp != _head)
            {
                std::cout<<tmp->_data<<" ";
                tmp = tmp->_next;
            }
            std::cout << std::endl;
        }
        void swap(list<T>& ls)
        {
            std::swap(_head, ls._head);
        }
        size_t size() const
        {
            size_t ret = 0;
            Node* tmp = _head->_next;
            while(tmp != _head)
            {
                ++ret;
                tmp = tmp->_next;
            }
            return ret;
        }
        bool empty() const
        {
            return _head->_next == _head;
        }
        T& front()
        {
            assert(size() > 0);
            return _head->_next->_data;
        }
        const T& front() const
        {
            assert(size() > 0);
            return _head->_next->_data;
        }
        T& back()
        {
            assert(size() > 0);
            return _head->_prev->_data;
        }
        const T& back() const
        {
            assert(size() > 0);
            return _head->_prev->_data;
        }
        void clear()  // const不能使用
        {
            // 复习，简单实现
            Node *first = _head->_next;
            while(first != _head)
            {
                Node *next = first->_next;
                delete first;
                first = next;
            }
            _head->_next = _head;
            _head->_prev = _head;

    // 不如我写的
//            auto it = begin();
//            while(it != end())
//            {
//                it = erase(it);
//            }

    // 不如我写的
//            Node* it = cbegin()._node;
//            while(it != cend()._node)
//            {
//                Node* prev = it->_prev;
//                Node* next = it->_next;
//                prev->_next = next;
//                next->_prev = prev;
//                delete it;
//                it = next;
//            }
        }
    };
}


#endif //STL_LIST_H


//    void test1()
//    {
//        yzl::list<int> ls;
//        ls.push_back(1);
//        ls.push_back(2);
//        ls.push_back(3);
//        ls.push_back(4);
//        ls.push_back(5);
//        ls.push_back(6);
//        ls.show();
//        cout<<ls.size()<<endl;
//        ls.pop_back();
//        ls.pop_back();
//        ls.pop_back();
//        ls.pop_back();
//        ls.show();
//        cout<<ls.size()<<endl;
//        ls.push_front(5);
//        ls.push_front(4);
//        ls.push_front(3);
//        ls.push_front(2);
//        ls.push_front(1);
//        ls.show();
//        ls.pop_front();
//        ls.pop_front();
//        ls.pop_front();
//        ls.show();
//    }


//    void test2()
//    {
//        yzl::list<int> ls;
//        ls.push_back(1);
//        ls.push_back(2);
//        ls.push_back(3);
//        ls.push_back(4);
//        ls.push_back(5);
//        yzl::list<int>::iterator it = ls.begin();
//        while(it != ls.end())
//        {
//            cout<<*it<<" ";
//            ++it;
//        }
//        cout<<endl;
//    }
//    void Func(const list<int>& ls)
//    {
//        list<int>::const_iterator it = ls.cbegin();
//        while(it != ls.cend())
//        {
//            cout<<*it<<" ";
//            ++it;
//        }
//        cout<<endl;
//    }
//    void test3()
//    {
//        list<int> ls;
//        ls.push_back(1);
//        ls.push_back(2);
//        ls.push_back(3);
//        ls.push_back(4);
//        ls.push_back(5);
//        Func(ls);
//    }

