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
    pair<K, V> _kv;  // ��ֵ�ԣ�AVL����ÿ���ڵ��Ԫ������
    int _bf; // balance factor ƽ������
};

template< typename K, typename V>
class AVLTree
{
private:
    AVLTreeNode<K, V>* _root = nullptr;
public:
    typedef AVLTreeNode<K, V> Node;

    bool Insert(const pair<K, V>& kv)
    {
        // �����ʱ��һ��������ֱ�ӽ����½�㣬��_root���ɡ���ʱ�����ӽڵ�͸��ڵ��Ϊnullptr��ƽ������Ϊ0.
        if(_root == nullptr)
        {
            _root = new Node(kv);
            return true;
        }
        Node* parent = nullptr;
        Node* cur = _root;
        while(cur != nullptr)
        {
            if(kv.first > cur->_kv.first) {
                parent = cur;
                cur = cur->_right;
            }
            else if(kv.first < cur->_kv.first) {
                parent = cur;
                cur = cur->_left;
            }
            else {
                // �ҵ�����ȵģ��˴���ƽ�������������֧�ֶ��ֵ���
                return false;
            }
        }
        // ��ʱ�ҵ��˺��ʵ�λ�ã�cur==nullptr,parentΪҪ����λ�õĸ��ڵ�
        cur = new Node(kv);
        if(kv.first > parent->_kv.first) {
            parent->_right = cur;
        }
        else {
            parent->_left = cur;
        }
        cur->_parent = parent;
        // �����������ĸ��ӽ���ϵ��Ū���ˣ��²�����������ӽڵ�Ϊnullptr��

        // ����ƽ�����ӣ�parent->_bf��
        while(parent != nullptr)
        {
            if(cur == parent->_right) {
                parent->_bf++;
            }
            else {
                parent->_bf--;
            }
            if(parent->_bf == 0) {
                // ��ʾ֮ǰ_bf == -1 or _bf == 1����ʱparent������߶Ȳ��䣬����Ӱ���������ڽ�㡣
                break;
            }
            else if(abs(parent->_bf) == 1) {
                // ֮ǰ_bf == 0����ʱparent������߶ȸı䣬��Ҫ���������޸�
                cur = parent;
                parent = parent->_parent;
            }
            else if(abs(parent->_bf) == 2) {
                // ��Ҫ��ת
                if(parent->_bf == 2 && parent->_right->_bf == 1) {
//                if(parent->_bf == 2 && cur->_bf == 1) {
                    // �ϸ����������ұ߸ߣ�����
                    RotateL(parent);
                }
                else if(parent->_bf == -2 && parent->_left->_bf == -1) {
                    // �ϸ�����������߸ߣ��ҵ���
                    RotateR(parent);
                }
                else if(parent->_bf == -2 && parent->_left->_bf == 1) {
//                else if(parent->_bf == -2 && cur->_bf == 1) {
                    // �ϸ����������ұ߲��룬����˫��
                    RotateLR(parent);
                }
                else if(parent->_bf == 2 && parent->_right->_bf == -1) {
//                else if(parent->_bf == 2 && cur->_bf == -1) {
                    // �ϸ�����������߲��룬����˫��
                    RotateRL(parent);
                }
                break;  // һ�β������һ����ת��ֻҪ��תһ�Σ���ƽ���ˣ�����Ҫ�����Ϲ۲�
            }
            else {
                // �����ϲ����ܳ���
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
        Node* subRL = subR->_left;  // ����Ϊ��

        parent->_right = subRL;
        if(subRL)
            subRL->_parent = parent;

        subR->_left = parent;
        Node* ppNode = parent->_parent;  // �޸�parent->parent֮ǰ������ԭ��parent->parent
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
        // ������һ���ģ������������ƽ�����ӽ��
        subR->_bf = parent->_bf = 0;
    }

    void RotateR(Node* parent)
    {
        // ��ʱparent��ƽ��
        Node* subL = parent->_left;
        Node* subLR = subL->_right;

        parent->_left = subLR;
        if(subLR)
            subLR->_parent = parent;

        Node* ppNode = parent->_parent;
        parent->_parent = subL;
        subL->_right = parent;

        if(parent == _root) {
            // parent���������ĸ��ڵ�
            _root = subL;
            subL->_parent = nullptr;
        }
        else {
            // parent�����������ĸ��ڵ㣬parent��parent
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
        Node* subLR = subL->_right;   // ������һ�����ǿ�

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
            // H = 0���������򵥵����
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
        // ��ȡroot������ĸ߶�
        if(root == nullptr)
            return 0;
        return 1 + max(Height(root->_left), Height(root->_right));
    }
    bool _IsBalance(Node* root) {
        // ������Ŷ������Ƿ����AVL��
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
