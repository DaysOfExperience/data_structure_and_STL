//
// Created by yangzilong on 2022/11/8.
//

#ifndef STL_AVLTREE_H
#define STL_AVLTREE_H
#include <utility>
#include <cmath>
#include <cassert>
#include <iostream>
#include <algorithm>
using namespace std;

template <class K, class V>
struct AVLTreeNode
{
    AVLTreeNode(const pair<K, V>& kv)
    : _left(nullptr), _right(nullptr), _parent(nullptr), _kv(kv), _bf(0)
    { }
    AVLTreeNode<K, V>* _left;
    AVLTreeNode<K, V>* _right;
    AVLTreeNode<K, V>* _parent;
    pair<K, V> _kv;  // 键值对，AVL树的每个节点的元素类型
    int _bf; // balance factor 平衡因子
};

template< typename K, typename V>
class AVLTree
{
private:
    AVLTreeNode<K, V> *_root = nullptr;
public:
    typedef AVLTreeNode<K, V> Node;

    bool Insert(const pair<K, V>& kv)
    {
        // 如果此时是一个空树，直接建立新结点，改_root即可。此时左右子节点和父节点均为nullptr，平衡因子为0.
        if(_root == nullptr) {
            _root = new Node(kv);
            return true;
        }
        Node* cur = _root;
        Node* parent = nullptr;
        while(cur != nullptr) {
            if(kv.first > cur->_kv.first) {
                parent = cur;
                cur = cur->_right;
            }
            else if(kv.first < cur->_kv.first) {
                parent = cur;
                cur = cur->_left;
            }
            else {
                // 找到了相等的（此处的平衡二叉搜索树不支持多键值相等）
                return false;
            }
        }
        // 此时找到了合适的位置，cur==nullptr,parent为要插入位置的父节点
        cur = new Node(kv);
        if(kv.first > parent->_kv.first) {
            parent->_right = cur;
        }
        else {
            parent->_left = cur;
        }
        cur->_parent = parent;
        // 现在整个树的父子结点关系都弄好了，新插入结点的左右子节点为nullptr，

        // 更新平衡因子（parent->_bf）
        while(parent != nullptr)
        {
            if(cur == parent->_right)   parent->_bf++;
            else    parent->_bf--;
            if(parent->_bf == 0) {
                // 表示之前_bf == -1 or _bf == 1，此时以parent为根节点的这个树的高度不变，不会影响其他祖宗结点。
                break;
            }
            else if(abs(parent->_bf) == 1) {
                // 之前_bf == 0，此时parent这棵树高度改变，需要继续向上修改，因为parent这颗子树高度改变了，此时是有可能进一步影响上方子树的
                cur = parent;
                parent = parent->_parent;   // 三叉链的作用
            }
            else if(abs(parent->_bf) == 2) {
                // 此时，以parent为根节点的子树破坏了AVL树的性质，需要旋转调整。
                if(parent->_bf == 2 && parent->_right->_bf == 1) {
//                if(parent->_bf == 2 && cur->_bf == 1) {    // 不能这样，因为cur和parent的关系不定
                    // 较高右子树的右边高，左单旋
                    RotateL(parent);
                }
                else if(parent->_bf == -2 && parent->_left->_bf == -1) {
                    // 较高左子树的左边高，右单旋
                    RotateR(parent);
                }
                else if(parent->_bf == -2 && parent->_left->_bf == 1) {
//                else if(parent->_bf == -2 && cur->_bf == 1) {
                    // 较高左子树的右边插入，使得不平衡，则左右双旋
                    RotateLR(parent);
                }
                else if(parent->_bf == 2 && parent->_right->_bf == -1) {
//                else if(parent->_bf == 2 && cur->_bf == -1) {
                    // 较高右子树的左边插入，使得不平衡，则右左双旋
                    RotateRL(parent);
                }
                break;  // 一次插入最多一次旋转。只要旋转一次，就平衡了，不需要再向上观察
            }
            else {
                // 理论上不可能出现
                assert(false);
            }
        }
        return true;
    }
    void InOrder()
    {
        _InOrder(_root);
    }
    bool IsBalance()
    {
        return _IsBalance(_root);
    }
private:
    void RotateL(Node* parent)
    {
        Node* subR = parent->_right;
        Node* subRL = subR->_left;  // 可能为空

        parent->_right = subRL;
        if(subRL)
            subRL->_parent = parent;

        subR->_left = parent;
        Node* ppNode = parent->_parent;  // 修改parent->parent之前，保存原先parent->parent
        parent->_parent = subR;

        if(parent == _root)
        {
            _root = subR;
            subR->_parent = nullptr;
        }
        else
        {
            if(parent == ppNode->_right) {
                ppNode->_right = subR;
                subR->_parent = ppNode;
            }
            else {
                ppNode->_left = subR;
                subR->_parent = ppNode;
            }
        }
        // 这里是一定的！！！左单旋后的平衡因子结果
        subR->_bf = parent->_bf = 0;
    }
    void RotateR(Node* parent)
    {
        // 此时parent不平衡
        Node* subL = parent->_left;
        Node* subLR = subL->_right;

        parent->_left = subLR;
        if(subLR)
            subLR->_parent = parent;

        Node* ppNode = parent->_parent;
        parent->_parent = subL;
        subL->_right = parent;

        if(parent == _root) {
            // parent是整棵树的根节点
            _root = subL;
            subL->_parent = nullptr;
        }
        else {
            // parent不是整棵树的根节点，parent有parent
            if(parent == ppNode->_right) {
                ppNode->_right = subL;
                subL->_parent = ppNode;
            }
            else {
                ppNode->_left = subL;
                subL->_parent = ppNode;
            }
        }
        subL->_bf = parent->_bf = 0;
    }
    void RotateLR(Node* parent) {
        Node* subL = parent->_left;
        Node* subLR = subL->_right;   // 这两个一定不是空

        int bf = subLR->_bf;

        RotateL(subL);
        RotateR(parent);

        if(bf == 1) {
            parent->_bf = 0;
            subL->_bf = -1;
            subLR->_bf = 0;
        }
        else if(bf == -1) {
            subL->_bf = 0;
            parent->_bf = 1;
            subLR ->_bf = 0;
        }
        else if(bf == 0) {
            subL->_bf = 0;
            parent->_bf = 0;
            subLR->_bf = 0;
        }
        else {
            assert(false);
        }
    }
    void RotateRL(Node* parent) {
        Node* subR = parent->_right;
        Node* subRL = subR->_left;

        int bf = subRL->_bf;

        RotateR(subR);
        RotateL(parent);

        if(bf == 1) {
            subR->_bf = 0;
            parent->_bf = -1;
            subRL->_bf = 0;
        }
        else if(bf == -1){
            parent->_bf = 0;
            subR->_bf = 1;
            subRL->_bf = 0;
        }
        else if(bf == 0) {
            // H = 0的情况，最简单的情况
            parent->_bf = 0;
            subR->_bf = 0;
            subRL->_bf = 0;
        }
        else {
            assert(false);
        }
    }
    void _InOrder(Node* root)
    {
        if(root == nullptr) {
            return;
        }
        _InOrder(root->_left);
        std::cout<<root->_kv.first<<"-"<<root->_kv.second<<std::endl;
        _InOrder(root->_right);
    }
    int Height(Node* root) {
        // 获取root这颗树的高度
        if(root == nullptr)
            return 0;
        return 1 + max(Height(root->_left), Height(root->_right));
    }
    bool _IsBalance(Node* root) {
        // 测试这颗二叉树是否符合AVL树
        if(root == nullptr) {
            return true;
        }
        if(abs(Height(root->_right) - Height(root->_left)) >= 2) {
            return false;
        }
        return _IsBalance(root->_left) && _IsBalance(root->_right);
    }
};


#endif //STL_AVLTREE_H
