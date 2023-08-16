//
// Created by yangzilong on 2022/11/11.
//

#ifndef STL_RBTREE_H
#define STL_RBTREE_H
#include <utility>
#include <iostream>
#include <vector>
using namespace std;
enum Color
{
    RED,
    BLACK
};

template< class K, class V >
struct RBTreeNode
{
    RBTreeNode(const pair<K, V>& kv)
    :_left(nullptr), _right(nullptr), _parent(nullptr), _kv(kv)
    {   }

    RBTreeNode<K, V>* _left;
    RBTreeNode* _right;
    RBTreeNode* _parent;
    pair<K, V> _kv;
    Color _col;
};

template <class K, class V>
class RBTree
{
    typedef RBTreeNode<K, V> Node;
private:
    RBTreeNode<K, V>* _root = nullptr;
public:
    bool Insert(const pair<K, V>& kv)
    {
        if(_root == nullptr) {
            _root = new Node(kv);
            _root->_col = BLACK;
            return true;
        }
        Node* parent = nullptr;
        Node* cur = _root;
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
                // Ҫ����ļ�ֵ�Ѵ���
                return false;
            }
        }
        cur = new Node(kv);
        cur->_col = RED;
        if(kv.first > parent->_kv.first) {
            parent->_right = cur;
        }
        else {
            parent->_left = cur;
        }
        cur->_parent = parent;

        // �����½��ɹ�����Ϊ��ɫ�������ж�
        // �����·�ѭ����parentһ��Ϊ�죬��parentһ�����Ǹ��ڵ㣬��parentһ���и��ף���û���ֵܲ�һ����
        while(parent && parent->_col == RED) {
            Node* grandfather = parent->_parent;
            Node* uncle = nullptr;
            if(parent == grandfather->_left)
                uncle = grandfather->_right;
            else
                uncle = grandfather->_left;

            // �ж�������������������ʽ
            if(uncle && uncle->_col == RED) {
                // ���������Ϊ��
                parent->_col = BLACK;
                uncle->_col = BLACK;

                grandfather->_col = RED;
                cur = grandfather;
                parent = cur->_parent;
            }
            else {
                // ���岻���ڻ������������Ϊ��
                if(parent == grandfather->_left && cur == parent->_left) {
                    // ��ʱ�������ҵ���+��ɫ
                    // �ȱ�ɫҲ����
                    parent->_col = BLACK;
                    grandfather->_col = RED;
                    RotateR(grandfather);
                }
                else if(parent == grandfather->_right && cur == parent->_right) {
                    // ���ң�����
                    parent->_col = BLACK;
                    grandfather->_col = RED;
                    RotateL(grandfather);
                }
                else if(parent == grandfather->_right && cur == parent->_left) {
                    // curΪ�죬parentΪ�죬grandfatherΪ�ڡ�
                    // ����˫����
//                    RotateR(parent);
//                    RotateL(grandfather);
//                    // ��ס�������Ϻڣ��������켴�ɡ�
//                    cur->_col = BLACK;
//                    grandfather->_col = RED;

                    // �ڶ���ʵ�ַ��������������Ϊ˫����
                    RotateR(parent);
                    std::swap(cur, parent);
                    parent->_col = BLACK;
                    grandfather->_col = RED;
                    RotateL(grandfather);
                }
                else if(parent == grandfather->_left && cur == parent->_right) {
//                    RotateL(parent);
//                    RotateR(grandfather);
//                    // ��ס�������Ϻڣ��������켴�ɡ�
//                    cur->_col = BLACK;
//                    grandfather->_col = RED;
                    RotateL(parent);
                    std::swap(cur, parent);
                    parent->_col = BLACK;
                    grandfather->_col = RED;
                    RotateR(grandfather);
                }

                break;
            }
            if(cur == _root) {
                cur->_col = BLACK;
            }
        }
        return true;
    }


    void InOrder()
    {
        _InOrder(_root);
        cout << endl;
    }

    // ����ɫ���ǿ��߶ȣ�
    // ����ɫ����Ϊ�߶���ȷ��һ���Ǻ����
    bool IsBalance()
    {
        if(_root == nullptr)
            return true;
        if(_root->_col == RED) {
            cout << "���ڵ�Ϊ��ɫ������" << endl;
            return false;
        }
        int baseNum = 0;
        return PrevCheck(_root, 0, 0);
    }

private:
    bool PrevCheck(Node* root, int baseNum, int blackNum)
    {
        if(root == nullptr)
        {
            if(baseNum == 0) {
                baseNum = blackNum;
                return true;
            }
            else if(blackNum != baseNum){
                cout << "ĳ��·����ɫ���������ͬ������" << endl;
                return false;
            }
            else
                return true;
        }
        if(root->_col == BLACK)
            blackNum++;
        else {
            if((nullptr != root->_left && root->_left->_col == RED) || (nullptr != root->_right && root->_right->_col == RED)) {
                cout << "����������ɫ��㣬����" << endl;
                return false;
            }
        }
        return PrevCheck(root->_left, baseNum, blackNum)
            && PrevCheck(root->_right, baseNum, blackNum);
    }

    void _InOrder(Node* root)
    {
        if (root == nullptr)
        {
            return;
        }
        _InOrder(root->_left);
        cout << root->_kv.first << ":" << root->_kv.second << endl;
        _InOrder(root->_right);
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
    }

    void RotateR(Node* parent)
    {
        Node* subL = parent->_left;
        Node* subLR = subL->_right;

        parent->_left = subLR;
        if(subLR)
            subLR->_parent = parent;

        Node* ppNode = parent->_parent;
        parent->_parent = subL;
        subL->_right = parent;

        if(parent == _root) {
            _root = subL;
            subL->_parent = nullptr;
        }
        else {
            if(parent == ppNode->_right) {
                ppNode->_right = subL;
                subL->_parent = ppNode;
            }
            else {
                ppNode->_left = subL;
                subL->_parent = ppNode;
            }
        }
    }
};


#endif //STL_RBTREE_H
