#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include <algorithm>
#include<assert.h>
#include<vector>
#include <stack>
#include<queue>
using namespace std;

typedef int BTDataType;
typedef struct BinaryTreeNode
{
	BTDataType data;
	struct BinaryTreeNode* left;
	struct BinaryTreeNode* right;
}BTNode;

BTNode* BuyNode(BTDataType x)
{
	BTNode* newnode = new BTNode();
	assert(newnode);

	newnode->data = x;
	newnode->right = nullptr;
	newnode->left = nullptr;

	return newnode;
}

BTNode* CreatBinaryTree()
{
	BTNode* node1 = BuyNode(1);
	BTNode* node2 = BuyNode(2);
	BTNode* node3 = BuyNode(3);
	BTNode* node4 = BuyNode(4);
	BTNode* node5 = BuyNode(5);
	BTNode* node6 = BuyNode(6);

	node1->left = node2;
	node1->right = node4;
	node2->left = node3;
	node4->left = node5;
	node4->right = node6;

	return node1;   // 根节点
}


// 一些对于二叉树的操作

// 二叉树前序遍历
void PreOrder(BTNode* root)
{
	if (root == nullptr)
	{
		cout << "# ";
		return;       // 空的话结束递归，输出#来表示这是一个空结点
	}
	cout << root->data << " ";   // 非空，对根节点的遍历操作：此处就是打印一下
	PreOrder(root->left);
	PreOrder(root->right);
}
// 二叉树前序非递归
vector<int> preorderTraversal(BTNode * root) {
    std::stack<BTNode *> st;
    vector<int> vec;
    st.push(root);
    while(!st.empty()) {
        BTNode *node = st.top();
        st.pop();
        // 取出了当前的根节点
        if(node != nullptr) {
            vec.push_back(node->data);
        }
        else {
            continue;
        }
        // 若node是叶子节点，则左右子树为空，到时候取出来之后，直接continue不影响~
        st.push(node->right);  // 先入右
        st.push(node->left);   // 后入左，取出时就是先取左，即先左子树，再右子树。
    }
    return vec;
}
// 二叉树中序遍历
void InOrder(BTNode* root)
{
	if (root == nullptr)
	{
		cout << "# ";
		return;
	}

	InOrder(root->left);
	cout << root->data << " ";   // 非空，对根节点的中序遍历操作：此处就是打印一下
	InOrder(root->right);
}
// 二叉树中序非递归
vector<int> inorderTraversal(BTNode *root) {
    stack<BTNode *> st;
    vector<int> vec;
    BTNode *cur = root;
    while(cur || !st.empty()) {
        // cur是某一个树（整棵树或者某子树）的根节点
        while(cur) {
            st.push(cur);
            cur = cur->left;
        }
        // 此时cur为空，代表着这个cur的父节点的左子树结束了
        BTNode *node = st.top();
        st.pop();
        // 此时的node的左子树结束了
        vec.push_back(node->data);  // 处理该结点，因为它的左子树结束了
        // 处理它的右子树，此时的右子树的情况是不知道的
        cur = node->right;
    }
    return vec;
}
// 二叉树后序遍历
void PostOrder(BTNode* root)
{
	if (root == nullptr)
	{
		cout << "# ";
		return;
	}

	PostOrder(root->left);
	PostOrder(root->right);
	cout << root->data << " ";  // 非空，对根节点的后序遍历时的操作：此处就是打印一下
}
// 二叉树后序非递归
vector<int> postorderTraversal(BTNode *root) {
    stack<BTNode *> st;
    vector<int> vec;
    st.push(root);
    while(!st.empty()) {
        BTNode *node = st.top();
        st.pop();
        if(node == nullptr) continue;
        vec.push_back(node->data);
        st.push(node->left);
        st.push(node->right);
    }
    std::reverse(vec.begin(), vec.end());
    return vec;
}
// 求二叉树结点个数
int count = 0;

void TreeSize1(BTNode* root)
{
	if (root == nullptr)
		return;

	++::count;
	TreeSize1(root->left);
	TreeSize1(root->right);
}

int TreeSize2(BTNode* root)
{
	if (root == NULL)
		return 0;

	return 1 + TreeSize2(root->left) + TreeSize2(root->right);
}

int LeafTreeNode(BTNode* root)
{
    // 23817
    if(root == nullptr) return 0;
    if(root->left || root->right) return LeafTreeNode(root->left) + LeafTreeNode(root->right);
    return 1;
}

int TreeKLevel(BTNode* root, int k)   //求第k层
{
    // 求第k层的结点个数时
    if(root == nullptr) return 0;
    if(k == 1) return 1;   // 有结点，且已经到了对应层了，就是一个计数的结点
    // 有结点，但是不是匹配层
    if(k > 1) return TreeKLevel(root->left, k-1) + TreeKLevel(root->right, k-1);
    else return 0;   // 此时，已经超过目标层了，没必要继续递归了
}


BTNode* TreeFind(BTNode* root, BTDataType x)
{
    if(root == nullptr) return nullptr;
    if(root->data == x) return root;
    // 此树的根节点不是目标节点
    BTNode *ret = TreeFind(root->left, x);  // 左子树找
    if(ret != nullptr) return ret;       // 左子树找到了就返回
    return TreeFind(root->right, x);   // 左子树没有，右子树找，不管找没找到，直接返回，因为现在唯一的希望就是右子树了
}

int  TreeDepth(BTNode* root)
{
    if(root == nullptr) return 0;
    int leftD = TreeDepth(root->left);
    int rightD = TreeDepth(root->right);
    return leftD > rightD ? leftD + 1 : rightD + 1;
}

// 销毁二叉树
void DestroyTree(BTNode* root)
{
    if(root == nullptr) return;
    DestroyTree(root->left);
    DestroyTree(root->right);
    delete root;
    root = nullptr;
}

// 层序遍历 利用队列
void LevelOrder(BTNode* root) {
    queue<BTNode *> que;
    que.push(root);
    while(!que.empty()) {
        BTNode *node = que.front();
        que.pop();
        if(node != nullptr) {
            std::cout << node->data << " ";
            que.push(node->left);   // 可能为空~
            que.push(node->right);
        }
        else {
//            std::cout << "# ";
            continue;
        }
    }
}

// 判断二叉树是否是完全二叉树
bool BinaryTreeComplete(BTNode* root)
{
    if(root == nullptr) return true;
    if((root->left != nullptr && root->right == nullptr)
    || (root->left == nullptr && root->right != nullptr)) {
        return false;
    }
    // 要么叶子结点，要么有两个子结点，都是符合要求的
    return BinaryTreeComplete(root->left) && BinaryTreeComplete(root->right);
}
bool BinaryTreeComplete2(BTNode* root)
{
    // 层序遍历检测完全二叉树
    queue<BTNode *> que;
    que.push(root);
    while(!que.empty()) {
        BTNode *node = que.front();
        que.pop();
        if(node == nullptr) continue;
        if((node->left != nullptr && node->right == nullptr)
           || (node->left == nullptr && node->right != nullptr)) {
            return false;
        }
        // 非空结点， 符合条件
        que.push(node->left);
        que.push(node->right);
    }
    return true;
}
bool BinaryTreeComplete3(BTNode* root)
{
    queue<BTNode*> q;
    if (root != nullptr) q.push(root);

    while (!q.empty()) {
        BTNode* root = q.front();
        q.pop();
        if (root != nullptr) {
            q.push(root->left);
            q.push(root->right);
        }
        else {
            break;
        }
    }
    while (!q.empty()) {
        if (q.front() != nullptr)
            return false;
        q.pop();
    }
    return true;
}
// 根据先序的数组来构造二叉树
BTNode* BinaryTreeCreate(BTDataType* arr, int n, int *pos) {
    if(*pos >= n || arr[*pos] == '#') {
        ++*pos;
        return nullptr;
    }
    BTNode *node = BuyNode(arr[*pos]);
    ++*pos;
    node->left = BinaryTreeCreate(arr, n, pos);
    node->right = BinaryTreeCreate(arr, n, pos);
    return node;
}
// 根据层序顺序的数组构建二叉树
BTNode *BinaryTreeCreate2(BTDataType *arr, int n, int pos) {
    if(pos >= n || arr[pos] == '#') {
        return nullptr;
    }
    BTNode *node = BuyNode(arr[pos]);
    node->left = BinaryTreeCreate2(arr, n, pos * 2 + 1);
    node->right = BinaryTreeCreate2(arr, n, pos * 2 + 2);
    return node;
}
void testBT()
{
//	BTNode* root = CreatBinaryTree();
    BTDataType arr[] = {1, 2, 3, '#', '#', '#',4, 5, '#', '#', 6, '#', '#'};
    BTDataType arr2[] = {1, 2,4,3,'#',5,6};
    int n = 0;
    BTNode *root = BinaryTreeCreate(arr, sizeof arr / sizeof arr[0], &n);
    BTNode *root2 = BinaryTreeCreate2(arr2, sizeof arr2 / sizeof arr[0], 0);
	PreOrder(root);
	cout << endl;
	InOrder(root);
	cout << endl;
	PostOrder(root);
	cout << endl;

	TreeSize1(root);
	cout << "结点个数1：" << ::count << endl;
	cout << "结点个数2：" << TreeSize2(root) << endl;
	cout << "二叉树的深度：" << TreeDepth(root) << endl;
	cout << "叶子结点个数：" << LeafTreeNode(root) << endl;
	cout << "第K层的结点个数(3)：" <<TreeKLevel(root, 3) << endl;
	cout << "查找data为5的结点：" << TreeFind(root, 5)->data << endl;
    cout << "完全二叉树？：" << BinaryTreeComplete(root) << endl;
    cout << "完全二叉树？：" << BinaryTreeComplete2(root) << endl;
    cout << "完全二叉树？：" << BinaryTreeComplete3(root) << endl;

    PreOrder(root2);
    cout << endl;
    InOrder(root2);
    cout << endl;
    PostOrder(root2);
    cout << endl;

    cout << "结点个数2：" << TreeSize2(root2) << endl;
    cout << "二叉树的深度：" << TreeDepth(root2) << endl;
    cout << "叶子结点个数：" << LeafTreeNode(root2) << endl;
    cout << "第K层的结点个数(3)：" <<TreeKLevel(root2, 3) << endl;
    cout << "查找data为5的结点：" << TreeFind(root2, 5)->data << endl;
    cout << "完全二叉树？：" << BinaryTreeComplete(root2) << endl;
    cout << "完全二叉树？：" << BinaryTreeComplete2(root2) << endl;
    cout << "完全二叉树？：" << BinaryTreeComplete3(root2) << endl;
}

void testBT2()
{
	BTNode* root = CreatBinaryTree();
    auto ret = preorderTraversal(root);
    for(auto & i : ret) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    ret = postorderTraversal(root);
    for(auto & i : ret) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    ret = inorderTraversal(root);
    for(auto & i : ret) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    LevelOrder(root);
}



int main()
{
    testBT();
	testBT2();
	return 0;
}