//
// Created by yangzilong on 2022/10/30.
//

#ifndef STL_BINARYSEARCHTREE_H
#define STL_BINARYSEARCHTREE_H

#include<iostream>

template <typename K>
struct BSTreeNode
{
    BSTreeNode(const K& key)
        :_key(key), _left(nullptr), _right(nullptr)
    { }
    BSTreeNode<K>* _left;
    BSTreeNode<K>* _right;
    K _key;
};

template <typename K>
class BinarySearchTree {
    typedef BSTreeNode<K> Node;
private:
    Node* _root = nullptr;   // 初始化列表中，_root默认初始化为nullptr
public:
    ~BinarySearchTree()
    {
        _Destroy(_root);
    }
    BinarySearchTree() = default;
    BinarySearchTree(const BinarySearchTree<K>& t)
    {
        _root = _Copy(t._root);
    }
    BinarySearchTree<K>& operator=(BinarySearchTree<K> t)
    {
        std::swap(_root, t._root);
        return *this;
    }
private:
    Node* _Copy(Node* root)
    {
        // 递归拷贝二叉搜索树，先构造根节点，然后构造左子树，构造右子树。
        if(root == nullptr)
            return nullptr;
        Node* newNode = new Node(root->_key);
        newNode->_left = _Copy(root->_left);
        newNode->_right = _Copy(root->_right);
        return newNode;
    }
    void _Destroy(Node* root)
    {
        // 递归销毁二叉搜索树，先销毁左，再销毁右，然后销毁根节点。
        if(root == nullptr)
            return;
        _Destroy(root->_left);
        _Destroy(root->_right);
        delete root;
    }
public:
    // 非递归
    bool Insert(const K& key) {
        // 空树
        if (_root == nullptr) {
            _root = new Node(key);
            return true;
        }
        // 非空树
        Node *cur = _root;
        Node *parent = nullptr;
        while (cur) {
            if (key > cur->_key) {
                parent = cur;
                cur = cur->_right;
            } else if (key < cur->_key) {
                parent = cur;
                cur = cur->_left;
            } else {
                return false; // 已经存在了
            }
        }
        // 此时，cur为空，parent不为空，即将插入的结点为parent的左结点或右结点，需要看key和parent的键值的比较
        if (key > parent->_key) {
            parent->_right = new Node(key);
        } else {
            parent->_left = new Node(key);
        }
        return true;
    }
    // 非递归查找，返回bool代表有或无
    bool Find(const K& key)
    {
        Node* cur = _root;
        while(cur)
        {
            if(key > cur->_key)
            {
                cur = cur->_right;
            }
            else if(key < cur->_key)
            {
                cur = cur->_left;
            }
            else
            {
                return true;
            }
        }
        return false;
    }
    // 非递归删除
    bool Erase(const K& key) {
        Node *cur = _root;
        Node *parent = _root;
        while (cur) {
            if (key > cur->_key) {
                parent = cur;
                cur = cur->_right;
            } else if (key < cur->_key) {
                parent = cur;
                cur = cur->_left;
            } else {
                if(cur == _root)
                {
                    // 此时，要删除的是整棵树的根节点，此时的parent不是cur的父节点。
                    if(_root->_left == nullptr) {
                        Node *del = _root;
                        _root = _root->_right;
                        delete del;
                        return true;
                    }
                    else if(_root->_right == nullptr) {
                        Node *del = _root;
                        _root = _root->_left;
                        delete del;
                        return true;
                    }
                    else {
                        Node *min = _root->_right;
                        Node *minP = _root;
                        while(min->_left) {
                            minP = min;
                            min = min->_left;
                        }
                        std::swap(_root->_key, min->_key);
                        // 此时需要删除min;
//                        return Erase(key);  // 此时key已经不是根节点了。
                        if(min == minP->_left) {
                            minP->_left = min->_right;
                        }
                        else {
                            minP->_right = min->_right;
                        }
                        delete min;
                        return true;
                    }
                }
                // 找到要删除的结点的，也就是cur，其父节点是parent（除了要删除root时，此时cur == parent）
                // edition 2
                // situation 1 - 情况1
                if(cur->_left == nullptr)
                {
                    if(parent->_left == cur)
                    {
                        parent->_left = cur->_right;
                        delete cur;
                    }
                    else
                    {
                        parent->_right = cur->_right;
                        delete cur;
                    }
                }
                else if(cur->_right == nullptr)
                {
                    if(parent->_left == cur)
                    {
                        parent->_left = cur->_left;
                        delete cur;
                    }
                    else
                    {
                        parent->_right = cur->_left;
                        delete cur;
                    }
                }
                else
                {
                    // 要删除结点的左右均不为空
                    // 去删除结点的右子树中找最小值，替换法删除
                    Node* min = cur->_right;  // 这里一定不为nullptr
                    Node* minParent = cur;
                    while(min->_left)
                    {
                        minParent = min;
                        min = min->_left;
                    }
                    // 这时，min一定是cur的右子树里面最小的
                    std::swap(cur->_key, min->_key);
                    // 此时min的左一定为空，且要删除掉min
                    if(min == minParent->_right)
                        minParent->_right = min->_right;
                    else
                        minParent->_left = min->_right;
                    delete min;
                }
                return true;
                // old
//                if (cur->_left == nullptr && cur->_right == nullptr) {
//                    // 叶子节点，直接删除
//                    if (parent->_left->_key == key) {
//                        delete parent->_left;
//                        parent->_left = nullptr;
//                    } else {
//                        delete parent->_right;
//                        parent->_right = nullptr;
//                    }
//                } else if (cur->_left != nullptr && cur->_right != nullptr) {
//                    // 找右子树的最小值，和cur交换值
//                    Node *minParent = cur;
//                    Node *min = cur->_right; // child一定不为nullptr
//                    while (min->_left) {
//                        minParent = min;
//                        min = min->_left;
//                    }
//                    std::swap(cur->_key, min->_key);
//                    if (minParent == cur) {
//                        minParent->_right = min->_right;  // 此时child->_left一定为nullptr
//                        delete min;
//                    } else {
//                        // 此时child和parent_2的关系一定是左子树和父节点
//                        minParent->_left = min->_right;
//                        delete min;
//                    }
//                } else {
//                    Node *child = nullptr;
//                    if (cur->_right != nullptr) {
//                        child = cur->_right;
//                    } else {
//                        child = cur->_left;
//                    }
//                    if (parent->_left != nullptr && parent->_left->_key == key) {
//                        delete parent->_left;
//                        parent->_left = child;
//                    } else {
//                        delete parent->_right;
//                        parent->_right = child;
//                    }
//                }
//                return true;
            }
        }
        return false;  // 没有要删除的key的结点
    }
    // 中序遍历，打印二叉搜索树（有序）
    void InOrder()
    {
        _InOrder(_root);
        std::cout<<std::endl;
    }
private:
    void _InOrder(Node* root)
    {
        // 典型中序遍历
        if(root == nullptr)
            return;
        _InOrder(root->_left);
        std::cout<<root->_key<<" ";
        _InOrder(root->_right);
    }
    ////////////////////////////////////////////////////////////////////////
    // 递归
public:
    bool Find_R(const K& key)
    {
        // 最多找h次，h为树的高度。
        return _Find_R(_root, key);
    }
    bool Insert_R(const K& key)
    {
        return _Insert_R(_root, key);
    }
    bool Erase_R(const K& key)
    {
        return _Erase_R(_root, key);
    }
private:
    bool _Erase_R(Node*& root, const K& key)
    {
        if(root == nullptr)
        {
            // 不存在
            return false;
        }
        if(key < root->_key)
        {
            return _Erase_R(root->_left, key);
        }
        else if(key > root->_key)
        {
            return _Erase_R(root->_right, key);
        }
        else
        {
            // 要删除的就是这个root，这个root实际上是父节点结构体里的right or left指针的别名！！！！！
            if(root->_left == nullptr) {
                Node* del = root;
                root = root->_right;
                delete del;
            }
            else if(root->_right == nullptr) {
                Node *del = root;
                root = root->_left;
                delete del;
            }
            else
            {
                Node* minParent = root;
                Node* min = root->_right;
                while(min->_left)
                {
                    minParent = min;
                    min = min->_left;
                }
                std::swap(root->_key, min->_key);
                // 上方交换时，root的key一定比min的key小，因为min在root的右子树中。
                // 此时交换完，需要删除的就是min了，min在root的右子树中。
                // 并且下方递归调用最后查找到时，一定会走左为空的情况。因为min的左就是空hhhhhhh
                return _Erase_R(root->_right, key);
//                if(minParent->_left == min)
//                {
//                    minParent->_left = min->_right;
//                }
//                else
//                {
//                    minParent->_right = min->_right;
//                }
//                delete min;
            }
            return true;
        }
    }
    bool _Insert_R(Node*& root, const K& key)
    {
        if(root == nullptr)
        {
            root = new Node(key);
            return true;
        }
        if(key < root->_key)
        {
            // 这里是把结构体里的指针成员传过去，参数用引用接收，改变参数就是改变这里结构体的指针成员。
            return _Insert_R(root->_left, key);
        }
        else if(key > root->_key)
        {
            // 这里是把结构体里的指针成员传过去，参数用引用接收，改变参数就是改变这里结构体的指针成员。
            return _Insert_R(root->_right, key);
        }
        else
        {
            return false;
        }
    }
//    bool _Insert_R(Node* root, const K& key)
//    {
//        if(root == nullptr)
//        {
//            _root = new Node(key);
//            return true;
//        }
//        if(root->_key < key && root->_right == nullptr)
//        {
//            root->_right = new Node(key);
//            return true;
//        }
//        else if(root->_key > key && root->_left == nullptr)
//        {
//            root->_left = new Node(key);
//            return true;
//        }
//        else if(root->_key > key)
//        {
//            return _Insert_R(root->_left, key);
//        }
//        else if(root->_key < key)
//        {
//            return _Insert_R(root->_right, key);
//        }
//        else
//        {
//            return false;
//        }
//    }
    bool _Find_R(Node* root, const K& key)
    {
        if(root == nullptr)
            return false;
        if(root->_key > key)
        {
            return _Find_R(root->_left, key);
        }
        else if(root->_key < key)
        {
            return _Find_R(root->_right, key);
        }
        else
        {
            return true;
        }
    }
};


#endif //STL_BINARYSEARCHTREE_H
