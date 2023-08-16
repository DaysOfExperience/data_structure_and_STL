//
// Created by yangzilong on 2022/8/26.
//

#ifndef STL_VECTOR_H
#define STL_VECTOR_H
#include "reverse_iterator.h"

namespace yzl
{
    // 拷贝构造，重载赋值都没实现。
    template<typename T, class Alloc = std::allocator<T>> // 就是一个用于申请T类型对象的类型而已。Alloc就是这么一个类型
    class vector {
    public:
        typedef T value_type;
        typedef value_type *iterator;
        typedef const value_type *const_iterator;

        typedef yzl::__reverse_iterator<iterator, T&, T*> reverse_iterator;
        typedef yzl::__reverse_iterator<const_iterator, const T&, const T*> const_reverse_iterator;
    private:
        iterator _start;    // T*
        iterator _finish;   // T*
        iterator _end_of_storage; // T*
    public:
        iterator begin() {
            return _start;
        }

        iterator end() {
            return _finish;
        }

        const_iterator begin() const {
            return _start;
        }

        const_iterator end() const {
            return _finish;
        }

        const_iterator cbegin() const {
            return _start;
        }

        const_iterator cend() const {
            return _finish;
        }

        reverse_iterator rbegin()
        {
            return yzl::__reverse_iterator<iterator, T&, T*>(end());
        }

        reverse_iterator rend()
        {
            return yzl::__reverse_iterator<iterator, T&, T*>(begin());
        }

        yzl::__reverse_iterator<const_iterator, const T&, const T*> rbegin() const
        {
            return yzl::__reverse_iterator<const_iterator, const T&, const T*>(end());
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
        vector()
                : _start(nullptr), _finish(nullptr), _end_of_storage(nullptr) {}

//        vector(size_t n, const T& val=T())
//        : _start(new T[n]), _finish(_start+n), _end_of_storage(_start+n)
//        {
//            for(size_t i = 0; i < n; ++i)
//                *(_start+i) = val;    // 调用T的赋值运算符
//        }
        // 必须有下面这个，如果是size_t  T的如上函数，则会出现报错。
        vector(int n, const T &value = T())
                : _start(new T[n]), _finish(_start + n), _end_of_storage(_finish) {
            for (int i = 0; i < n; ++i) {
                _start[i] = value;
            }
        }

        template<class InputIterator>
        vector(InputIterator first, InputIterator last)
                : _start(nullptr), _finish(nullptr), _end_of_storage(nullptr) {
//            size_t sz = last - first;
////            while(first+sz != last)
////            {
////                ++sz;
////            }
//            _start = new T[sz];
//            _finish = _start + sz;
//            _end_of_storage = _start + sz;
//            for(size_t i = 0; i < sz; ++i)
//            {
//                *(_start+i) = *first;
//                ++first;
//            }

            // 复用版本：  有问题：
            while (first != last) {
                this->push_back(*first);
                first++;
            }
        }

        vector(const vector<T> &v)
                : _start(new T[v.size()]), _finish(_start + v.size()), _end_of_storage(_finish) {
            // 不能用memcpy，memcpy是逐字节拷贝，若涉及深度拷贝则出错。
            for (size_t i = 0; i < v.size(); ++i) {
                *(_start + i) = *(v._start + i);
            }
        }
        // vector拷贝构造的第二种写法:
        vector(const vector& v)
        : _start(nullptr), _finish(nullptr), _end_of_storage(nullptr)
        {
            reserve(v.size());
            for(const auto& i : v)
            {
                this->push_back(i);
            }
        }

        // vector的现代写法：借用其他的构造
        vector(const vector &v)
                : _start(nullptr), _finish(nullptr), _end_of_storage(nullptr) {
            // 这是要基于迭代器区间构造
            vector<T> tmp(v.begin(), v.end());
            this->swap(tmp);
        }

        vector<T> &operator=(vector<T> v) {
            this->swap(v);
            return *this;
        }

        ~vector() {
            if (_start) {
                delete[] _start;
                _start = _finish = _end_of_storage = nullptr;
            }
        }
        // -------------------------------------------------------------------
        size_t size() const {
            return _finish - _start;
        }

        size_t capacity() const {
            return _end_of_storage - _start;
        }

        void reserve(size_t n) {
            if (n > capacity()) {
                size_t oldSize = size();
                T *tmp = new T[n];
                // 不能memcpy，必须这样，防止元素类型涉及深拷贝。
                for (size_t i = 0; i < size(); ++i) {
                    *(tmp + i) = *(_start + i);
                }
                delete[] _start;
                _start = tmp;
                _finish = _start + oldSize;   // 如果不存储这个oldSize，此时用size()的话，会出问题。（但是也不是必须好像，不关注了
                _end_of_storage = _start + n;
            }
        }

        void resize(size_t n, const T &val = T()) {
            if (n > size()) {
                reserve(n);
                size_t sz = size();
                for (; sz < n; ++sz) {
                    *(_start + sz) = val;
                }
                _finish = _start + n;
            } else {
                _finish = _start + n;
            }
        }

        void push_back(const T &val) {
            if (_finish == _end_of_storage) {
                reserve(size() == 0 ? 4 : 2 * size());
            }
            *(_start + size()) = val;
            ++_finish;
        }

        void pop_back() {
            assert(size() > 0);
            --_finish;
        }

        iterator insert(const_iterator position, const value_type &val) {
            assert(position >= _start);
            assert(position <= _finish);
            if (_finish == _end_of_storage) {
                size_t diff = position - _start;
                reserve(size() == 0 ? 4 : 2 * size());
                position = _start + diff;   // 纠正迭代器，因为扩容之后原迭代器就失效了   insert引起的迭代器失效！！！！！
            }
            iterator end = _finish - 1;
            while (end >= position) {
                *(end + 1) = *(end);
                end--;
            }
            *(_start + (position - _start)) = val;   // 调用value_type的赋值操作。
            ++_finish;
            return _start + (position - _start);
        }

        iterator insert(const_iterator position, size_t n, const value_type &val) {
            assert(position >= _start);
            assert(position <= _finish);
            if (_finish + n > _end_of_storage) {
                size_t diff = position - _start;
                reserve(size() + n);
                position = _start + diff;
            }
            iterator it = _finish - 1;
            while (it >= position) {
                *(it + n) = *it;
                --it;
            }
            size_t diff = position - _start;
            for (size_t i = diff; i < diff + n; ++i) {
                *(_start + i) = val;
            }
            _finish += n;
            return _start + diff;
        }

        iterator erase(const_iterator pos) {
            assert(pos >= _start && pos < _finish);
            iterator it = _start + (pos - _start);
            while (it != _finish - 1) {
                *it = *(it + 1);
                ++it;
            }
            --_finish;
            return _start + (pos - _start);
        }

//        iterator erase(const_iterator first, const_iterator lase)
//        {
//            return first;
//        }
        T &operator[](size_t n) {
            assert(n < size());
            return *(_start + n);
        }

        const T &operator[](size_t n) const {
            assert(n < size());
            return *(_start + n);
        }

        bool empty() const {
            return _start == _finish;
        }

        T &front() {
            assert(size() > 0);
            return *_start;
        }

        const T &front() const {
            assert(size() > 0);
            return *_start;
        }

        T &back() {
            assert(size() > 0);
            return *(_finish - 1);
        }

        const T &back() const {
            assert(size() > 0);
            return *(_finish - 1);
        }

        void swap(vector &v) {
            std::swap(_start, v._start);
            std::swap(_finish, v._finish);
            std::swap(_end_of_storage, v._end_of_storage);
        }

        void clear() {
            _finish = _start;
        }
    };
}


#endif //STL_VECTOR_H
