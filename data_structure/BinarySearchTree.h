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
    Node* _root = nullptr;   // ��ʼ���б��У�_rootĬ�ϳ�ʼ��Ϊnullptr
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
        // �ݹ鿽���������������ȹ�����ڵ㣬Ȼ������������������������
        if(root == nullptr)
            return nullptr;
        Node* newNode = new Node(root->_key);
        newNode->_left = _Copy(root->_left);
        newNode->_right = _Copy(root->_right);
        return newNode;
    }
    void _Destroy(Node* root)
    {
        // �ݹ����ٶ��������������������������ң�Ȼ�����ٸ��ڵ㡣
        if(root == nullptr)
            return;
        _Destroy(root->_left);
        _Destroy(root->_right);
        delete root;
    }
public:
    // �ǵݹ�
    bool Insert(const K& key) {
        // ����
        if (_root == nullptr) {
            _root = new Node(key);
            return true;
        }
        // �ǿ���
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
                return false; // �Ѿ�������
            }
        }
        // ��ʱ��curΪ�գ�parent��Ϊ�գ���������Ľ��Ϊparent��������ҽ�㣬��Ҫ��key��parent�ļ�ֵ�ıȽ�
        if (key > parent->_key) {
            parent->_right = new Node(key);
        } else {
            parent->_left = new Node(key);
        }
        return true;
    }
    // �ǵݹ���ң�����bool�����л���
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
    // �ǵݹ�ɾ��
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
                    // ��ʱ��Ҫɾ�������������ĸ��ڵ㣬��ʱ��parent����cur�ĸ��ڵ㡣
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
                        // ��ʱ��Ҫɾ��min;
//                        return Erase(key);  // ��ʱkey�Ѿ����Ǹ��ڵ��ˡ�
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
                // �ҵ�Ҫɾ���Ľ��ģ�Ҳ����cur���丸�ڵ���parent������Ҫɾ��rootʱ����ʱcur == parent��
                // edition 2
                // situation 1 - ���1
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
                    // Ҫɾ���������Ҿ���Ϊ��
                    // ȥɾ������������������Сֵ���滻��ɾ��
                    Node* min = cur->_right;  // ����һ����Ϊnullptr
                    Node* minParent = cur;
                    while(min->_left)
                    {
                        minParent = min;
                        min = min->_left;
                    }
                    // ��ʱ��minһ����cur��������������С��
                    std::swap(cur->_key, min->_key);
                    // ��ʱmin����һ��Ϊ�գ���Ҫɾ����min
                    if(min == minParent->_right)
                        minParent->_right = min->_right;
                    else
                        minParent->_left = min->_right;
                    delete min;
                }
                return true;
                // old
//                if (cur->_left == nullptr && cur->_right == nullptr) {
//                    // Ҷ�ӽڵ㣬ֱ��ɾ��
//                    if (parent->_left->_key == key) {
//                        delete parent->_left;
//                        parent->_left = nullptr;
//                    } else {
//                        delete parent->_right;
//                        parent->_right = nullptr;
//                    }
//                } else if (cur->_left != nullptr && cur->_right != nullptr) {
//                    // ������������Сֵ����cur����ֵ
//                    Node *minParent = cur;
//                    Node *min = cur->_right; // childһ����Ϊnullptr
//                    while (min->_left) {
//                        minParent = min;
//                        min = min->_left;
//                    }
//                    std::swap(cur->_key, min->_key);
//                    if (minParent == cur) {
//                        minParent->_right = min->_right;  // ��ʱchild->_leftһ��Ϊnullptr
//                        delete min;
//                    } else {
//                        // ��ʱchild��parent_2�Ĺ�ϵһ�����������͸��ڵ�
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
        return false;  // û��Ҫɾ����key�Ľ��
    }
    // �����������ӡ����������������
    void InOrder()
    {
        _InOrder(_root);
        std::cout<<std::endl;
    }
private:
    void _InOrder(Node* root)
    {
        // �����������
        if(root == nullptr)
            return;
        _InOrder(root->_left);
        std::cout<<root->_key<<" ";
        _InOrder(root->_right);
    }
    ////////////////////////////////////////////////////////////////////////
    // �ݹ�
public:
    bool Find_R(const K& key)
    {
        // �����h�Σ�hΪ���ĸ߶ȡ�
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
            // ������
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
            // Ҫɾ���ľ������root�����rootʵ�����Ǹ��ڵ�ṹ�����right or leftָ��ı�������������
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
                // �Ϸ�����ʱ��root��keyһ����min��keyС����Ϊmin��root���������С�
                // ��ʱ�����꣬��Ҫɾ���ľ���min�ˣ�min��root���������С�
                // �����·��ݹ���������ҵ�ʱ��һ��������Ϊ�յ��������Ϊmin������ǿ�hhhhhhh
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
            // �����ǰѽṹ�����ָ���Ա����ȥ�����������ý��գ��ı�������Ǹı�����ṹ���ָ���Ա��
            return _Insert_R(root->_left, key);
        }
        else if(key > root->_key)
        {
            // �����ǰѽṹ�����ָ���Ա����ȥ�����������ý��գ��ı�������Ǹı�����ṹ���ָ���Ա��
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
