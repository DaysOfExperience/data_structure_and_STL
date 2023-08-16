//
// Created by yangzilong on 2022/10/9.
//

namespace yzl
{
    // less大堆，greater小堆
    template<class T, class Container = std::vector<T>, class Compare = std::less<T> >
    class priority_queue
    {
    private:
        Container _con;
    public:
        priority_queue() = default;
        template<class InputIterator>
        priority_queue(InputIterator begin, InputIterator end)
        {
            while(begin != end)
            {
                _con.push_back(*begin);
                ++begin;
            }
            // 建堆，向下调整效率高
            for(int i = (_con.size()-1-1)/2; i >= 0; --i)
            {
                adjust_down(i);
            }
        }
        void push(const T& val)
        {
            _con.push_back(val);
            adjust_up(_con.size()-1);
        }
        void adjust_up(size_t child)   // 从child下标处开始向上调整。child是二叉树中这个结点的下标。
        {
            Compare cmp;
            size_t parent = (child-1)/2;
            while(child > 0)  // 向上调整终止条件
            {
                if(cmp(_con[parent], _con[child]))
                {
                    std::swap(_con[parent], _con[child]);
                    child = parent;
                    parent = (child-1)/2;
                }
                else
                {
                    break;
                }
            }
        }
        void pop()
        {
            std::swap(_con[0], _con[_con.size()-1]);
            _con.pop_back();
            adjust_down(0);
        }
        void adjust_down(size_t parent)   // parent是需要调整的结点在二叉树中的下标。（因为是顺序存储的。堆：完全二叉树
        {
            Compare cmp;
            size_t child = parent*2+1;
            while(child < _con.size())
            {
                if(child + 1 < _con.size() && cmp(_con[child], _con[child+1]))
                {
                    child+=1;
                }
                if(cmp(_con[parent], _con[child]))
                {
                    std::swap(_con[parent], _con[child]);
                    parent = child;
                    child = parent*2+1;
                }
                else
                {
                    break;
                }
            }
        }
        // 优先级队列的top返回值为const不可以修改。
        const T& top() const
        {
            return _con.front();
        }
        size_t size() const
        {
            return _con.size();
        }
        bool empty() const
        {
            return _con.empty();
        }
    };
}