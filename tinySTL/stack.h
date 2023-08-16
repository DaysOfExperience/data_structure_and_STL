//
// Created by yangzilong on 2022/10/8.
//

#ifndef STL_STACK_H
#define STL_STACK_H
#include <deque>
#include <cstdlib>
namespace yzl
{
    template<class T, class Container = std::deque<T>>
    class stack
    {
    public:
        void push(const T& val)
        {
            _con.push_back(val);
        }
        void pop()
        {
            _con.pop_back();
        }
        T& top()
        {
            return _con.back();
        }
        const T& top() const
        {
            return _con.back();
        }
        size_t size() const
        {
            return _con.size();
        }
        bool empty() const
        {
            return _con.empty();
        }

    private:
        // vector<T> _con;
        Container _con;
    };
}



#endif //STL_STACK_H
