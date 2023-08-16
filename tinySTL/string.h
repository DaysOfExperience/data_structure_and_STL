//
// Created by yangzilong on 2022/8/13.
//

#ifndef STL_STRING_H
#define STL_STRING_H
#include<iostream>
#include<cmath>
#include<cstring>
#include<cassert>
using namespace std;

namespace yzl
{
    class string
    {
    public:
        typedef char* iterator;
        typedef const char* const_iterator;
        iterator begin()
        {
            return _str;
        }
        iterator end() {
            return _str + _size;
        }
        const_iterator begin() const
        {
            return _str;
        }
        const_iterator end() const
        {
            return _str + _size;
        }
        const_iterator cbegin() const
        {
            return _str;
        }
        const_iterator cend() const
        {
            return _str+_size;
        }
    public:
//        string() : _size(0),_capacity(0),_str(new char[1])
//        {
//            _str[0] = '\0';
//        }
        string(const char* str = "")
        {
            _size = strlen(str);  // strlen不包含\0，计算的是有效字符个数。
            _capacity = _size;
            _str = new char[_capacity+1];

            strcpy(_str, str);  // strcpy会拷贝'\0'
        }
        string(size_t n, char c)
        : _size(n),_capacity(n),_str(new char[n+1])
        {
            for(size_t i = 0; i < n; ++i)
                _str[i] = c;
            _str[n] = '\0';
        }
        // 传统写法
//        string(const string& s)
//        : _size(s._size),_capacity(s._capacity),_str(new char[s._capacity+1])
//        {
//            strcpy(_str,s._str);
//        }
////         s1 = s3;
//        string& operator=(const string& s)
//        {
//            if(this != &s)
//            {
//                delete[] this->_str;
//                _str = new char[s._capacity+1];
//                _size = s._size;
//                _capacity = s._capacity;
//                strcpy(_str,s._str);
//            }
//            return *this;
//        }
////         略微改进了一点，考虑到如果new开空间失败，不破坏原对象。
//        string& operator=(const string& s)
//        {
//            if(this != &s)
//            {
//                char* tmp = new char[s._capacity+1];
//                strcpy(tmp,s._str);
//                delete[] this->_str;
//                _str = tmp;
//                _size = s._size;
//                _capacity = s._capacity;
//            }
//            return *this;
//        }

        //=======================================================
        void swap(string& tmp)
        {
            std::swap(_str,tmp._str);
            std::swap(_size,tmp._size);
            std::swap(_capacity,tmp._capacity);
        }
        // 现代写法： 老板思维
        string(const string& s)    // string s1(s2)
        :_size(0),_capacity(0),_str(nullptr)    // 如果不这样，this的_str是随机值，tmp析构时，delete[]随机值非法。
        {
            string tmp(s._str);   // 调用string(const char*) 构造函数
            this->swap(tmp);
        }
        string& operator=(const string& s)
        {
            if (this != &s) {
//                string tmp(s);
                string tmp(s._str);
                swap(tmp);
            }
            return *this;
        }
        // 最简版
//        string& operator=(string s)
//        {
//            swap(s);
//            return *this;
//        }

        string& operator=(const char* s) {
            string tmp(s);
            this->swap(tmp);
            return *this;
        }
        ~string()
        {
            delete[] _str;
            _str = nullptr;
            _size = _capacity = 0;
        }

        const char* c_str() const
        {
            return _str;
        }
        size_t size() const
        {
            return _size;
        }
        size_t capacity() const
        {
            return _capacity;
        }
        char& operator[](size_t pos)
        {
            assert(pos < _size);
            return _str[pos];
        }
        const char& operator[](size_t pos) const
        {
            assert(pos<_size);
            return _str[pos];
        }
        void reserve(size_t n = 0)
        {
            if(n > _capacity)
            {
                char* tmp = new char[n+1];   // n个有效数据,1用于'\0'
                strcpy(tmp,_str);
                delete[] (_str);
                _str = tmp;
                _capacity = n;    // _capacity 必须处理 size不变
            }
        }
        void resize(size_t n, char c = '\0')
        {
            if(n > _size)
            {
                reserve(n);
                for(size_t i = _size; i < n; ++i)
                {
                    _str[i] = c;
                }
                _str[n] = '\0';
                _size = n;
            }
            else
            {
                _str[n] = '\0';
                _size = n;
            }
        }
        void clear()
        {
            _str[0] = '\0';
            _size = 0;
        }
        bool empty() const
        {
            return _size == 0;
        }
        void push_back(char c)
        {
            if(_size == _capacity)
            {
                reserve(_capacity == 0 ? 4 : 2*_capacity);
            }
            _str[_size] = c;
            ++_size;
            _str[_size] = '\0';
        }
        string& append(const char* s)
        {
            int size = strlen(s);
            if(_size + size > _capacity)
            {
                reserve(_size+size);
            }
            strcpy(_str+_size,s);
            _size+=size;
            return *this;
        }
        string& append(const string& s)
        {
            int size = s.size();
            if(_size + size > _capacity)
            {
                reserve(_size + size);
            }
            strcpy(_str+_size,s.c_str());
            _size+=size;
            return *this;
        }
        string& append(size_t n, char c)
        {
            if(_size + n > _capacity)
            {
                reserve(_size + n);
            }
            for(size_t i = 0; i < n; ++i)
            {
                _str[_size+i] = c;
            }
            _size+=n;
            return *this;
        }
//        string& append(const string& s);   this->append(s.c_str());
//        string& append(size_t n, char c);  push_back(c);
        string& operator+=(char c)
        {
            this->push_back(c);
            return *this;
        }
        string& operator+=(const char* s)
        {
            this->append(s);
            return *this;
        }
        string& operator+=(const string& s)
        {
            this->append(s);
            return *this;
        }
        string& insert(size_t pos, char c)
        {
            assert(pos <= _size);
            if(_size == _capacity)
            {
                reserve(_capacity == 0?4:2*_capacity);
            }
            int end = _size;
            while(end >= pos)
//            while(end >= (int)pos)
            {
                _str[end+1] = _str[end];
                end--;
            }
            // 比较推荐的写法，主要是  int和size_t比较，会出现比较错误，当int小于0时。
//            size_t end = _size+1;
//            while(end > pos)
//            {
//                _str[end] = _str[end-1];
//                end--;
//            }
            _str[pos] = c;
            ++_size;
            return *this;
        }
        string& insert(size_t pos, size_t n, char ch)
        {
            assert(pos <= _size);
            // pos==0 n==0 则下面while会出错（size_t）
            if(n == 0)
                return *this;
            if(_size + n > _capacity)
            {
                reserve(_size+n);
            }
            // [pos, pos+n) n个  [_size, _size+n) n个
            size_t end = _size + n;
            while(end >= pos+n)
            {
                _str[end] = _str[end-n];
                end--;
            }
            for(size_t i = pos; i < pos+n; ++i)
            {
                _str[i] = ch;
            }
            _size+=n;
            return *this;
        }
        string& insert(size_t pos, const char* str)
        {
            assert(pos<=_size);
            if(strlen(str) == 0)
                return *this;
            int len = strlen(str);
            if(_size+len > _capacity) {
                reserve(_size+len);
            }
            size_t end = _size+len;
            while(end >= pos+len)
            {
                _str[end] = _str[end-len];
                end--;
            }
//            int end = _size;
//            while(end >= (int)pos)
//            {
//                _str[end+len] = _str[end];
//                end--;
//            }
            strncpy(_str+pos,str,len);   // strcpy会把\0也copy进去。
            _size+=len;
            return *this;
        }
        string& insert(size_t n, const string& s)
        {
            this->insert(n,s.c_str());
            return *this;
        }
        string& erase(size_t pos = 0, size_t len = npos)
        {
            assert(pos < _size);
            if(len == npos || pos + len >= _size)
            {
                _str[pos] = '\0';
                _size = pos;
            }
            else
            {
                size_t i = pos + len;
                size_t p = pos;
                while(i<=_size)
                {
                    _str[p] = _str[i];
                    i++;
                    p++;
                }
                _size -= len;
            }
            return *this;
        }
        size_t find(char c, size_t pos = 0) const
        {
            assert(pos < _size);
            for(size_t i = pos; i < size(); ++i) {
                if(_str[i] == c)
                    return i;
            }
            return npos;
        }
        size_t find(const char* str, size_t pos = 0) const
        {
            assert(pos < _size);
            assert(str);
            const char* p = strstr(_str+pos, str);
            if(p == nullptr)
                return npos;
            else
                return p-_str;
        }
        size_t find(const string& s, size_t pos = 0) const
        {
            return find(s.c_str(), pos);
        }
        string substr(size_t pos, size_t len = npos) const
        {
            assert(pos < _size);
            if(len == npos || len + pos >= _size)
            {
                len = _size - pos;
            }
            string ret;
            for(size_t i = pos; i < pos + len; ++i)
            {
                ret+=_str[pos];
            }
            return ret;
        }
        bool operator> (const string& s) const
        {
            return strcmp(_str, s.c_str())>0;
        }
        bool operator==(const string& s) const
        {
            return strcmp(_str, s.c_str()) == 0;
        }
        bool operator >=(const string& s)const
        {
            return *this > s || *this == s;
        }
        bool operator < (const string& s)const {
            return !(*this >= s);
        }
        bool operator <= (const string& s)const {
            return !(*this>s);
        }
        bool operator != (const string& s)const {
            return !(*this == s);
        }
    private:
        char* _str;
        size_t _size;
        size_t _capacity;
    public:
        const static size_t npos = -1;
//        static size_t npos;
    };

    ostream& operator<<(ostream& os, const string& s)
    {
        for(size_t i = 0; i < s.size(); ++i)
            os<<s[i];
        return os;
    }
//    istream& operator>>(istream& is, string& s)
//    {
//        s.clear();
//        char ch;
//        ch = is.get();
//        while(ch != ' ' && ch != '\n')
//        {
//            s += ch;
//            ch = is.get();
//        }
//        return is;
//    }
    istream& operator>>(istream& is, string& s)
    {
        s.clear();
        char ch;
        ch = is.get();

        const int sz = 32;
        char buff[sz];
        size_t i = 0;
        while(ch != ' ' && ch != '\n')
        {
            buff[i] = ch;
            i++;
            if(i == sz-1)
            {
                buff[i] = '\0';
                s += buff;
                i = 0;
            }
            ch = is.get();
        }
        buff[i] = '\0';
        s+=buff;
        return is;
    }
//    size_t string::npos = -1;
}




#endif //STL_STRING_H