//
// Created by yangzilong on 2022/10/9.
//

#ifndef STL_QUEUE_H
#define STL_QUEUE_H
#include <deque>
#include <cstdlib>
namespace yzl
{
    // 容器不适于stack，因为没有pop_front
    template<class T, class Container = std::deque<T>>
    class queue
    {
    public:
        void push(const T& val)
        {
            _con.push_back(val);
        }
        void pop()
        {
            _con.pop_front();
        }
        T& front()
        {
            return _con.front();
        }
        T& back()
        {
            return _con.back();
        }
        const T& front() const
        {
            return _con.front();
        }
        const T& back() const
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
        Container _con;
    };
}

#endif //STL_QUEUE_H
