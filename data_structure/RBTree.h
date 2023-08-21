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
                // 要插入的键值已存在
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
        // 插入新结点成功，且为红色。进行判断
        // 进入下方循环后，parent一定为红，则parent一定不是根节点，则parent一定有父亲，有没有兄弟不一定。
        while(parent && parent->_col == RED) {
            Node* grandfather = parent->_parent;
            Node* uncle = nullptr;
            if(parent == grandfather->_left)
                uncle = grandfather->_right;
            else
                uncle = grandfather->_left;

            // 判断叔叔的情况，决定处理方式
            if(uncle && uncle->_col == RED) {
                // 叔叔存在且为红
                parent->_col = BLACK;
                uncle->_col = BLACK;

                grandfather->_col = RED;
                cur = grandfather;
                parent = cur->_parent;
            }
            else {
                // 叔叔不存在或者叔叔存在且为黑
                if(parent == grandfather->_left && cur == parent->_left) {
                    // 此时，左左，右单旋+变色
                    // 先变色也可以
                    parent->_col = BLACK;
                    grandfather->_col = RED;
                    RotateR(grandfather);
                }
                else if(parent == grandfather->_right && cur == parent->_right) {
                    // 右右，左单旋
                    parent->_col = BLACK;
                    grandfather->_col = RED;
                    RotateL(grandfather);
                }
                else if(parent == grandfather->_right && cur == parent->_left) {
                    // cur为红，parent为红，grandfather为黑。
                    // 右左双旋。
//                    RotateR(parent);
//                    RotateL(grandfather);
//                    // 记住这里是上黑，下面俩红即可。
//                    cur->_col = BLACK;
//                    grandfather->_col = RED;

                    // 第二种实现方法，即单旋后变为双旋。
                    RotateR(parent);
                    std::swap(cur, parent);
                    parent->_col = BLACK;
                    grandfather->_col = RED;
                    RotateL(grandfather);
                }
                else if(parent == grandfather->_left && cur == parent->_right) {
//                    RotateL(parent);
//                    RotateR(grandfather);
//                    // 记住这里是上黑，下面俩红即可。
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
            if(cur == _root) {  // 针对叔叔存在且为红时，变色之后，循环处理前，若此时的cur是根节点，则需要变一下色（parent为nullptr）
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

    // 看颜色还是看高度？
    // 看颜色，因为高度正确不一定是红黑树
    bool IsBalance()
    {
        if(_root == nullptr)
            return true;
        if(_root->_col == RED) {
            cout << "根节点为红色，错误" << endl;
            return false;
        }
        return PrevCheck(_root, 0, 0);
    }

private:
    bool PrevCheck(Node* root, int baseNum, int blackNum)
    {
        // 该结点为叶子结点的子结点，即空结点。
        if(root == nullptr)
        {
            if(baseNum == 0) {
                baseNum = blackNum;
                return true;
            }
            else if(blackNum != baseNum){
                cout << "某条路径黑色结点数量不同，错误" << endl;
                return false;
            }
            else
                return true;
        }
        // 该节点不是空结点，是红黑树中的某一个结点
        if(root->_col == BLACK)
            blackNum++;      // 包含root结点的路线中的黑色结点个数增加一个
        else {
            if((root->_left != nullptr && root->_left->_col == RED)
            || (root->_right != nullptr && root->_right->_col == RED)) {
                cout << "出现连续红色结点，错误" << endl;
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
