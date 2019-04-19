#ifndef _BINARY_SEARCH_TREE_H_
#define _BINARY_SEARCH_TREE_H_

typedef int Type;

typedef struct BSTreeNode{
	Type key;
	struct BSTreeNode *left;
	struct BSTreeNode *right;
	struct BSTreeNode *parent;
}Node, *BSTree;

//前序遍历二叉树
void preorder_bstree(BSTree tree);
//中序遍历二叉树
void inorder_bstree(BSTree tree);
//后序遍历二叉树
void postorder_bstree(BSTree tree);

//递归实现 查找二叉树x中值为key的结点
Node* bstree_search(BSTree x,Type key);
//非递归实现 查找二叉树x中值为key的结点
Node* iterative_bstree_search(BSTree x,Type key);

//查找最小结点：返回tree为根节点的二叉树的最小结点
Node* bstree_minimum(BSTree tree);
//查找最大结点：返回tree为根节点的二叉树的最大结点
Node* bstree_maximum(BSTree tree);

//找结点x的后继结点（中序），即查找二叉树中值大于x的key值的最小结点
Node* bstree_successor(Node *x);
//找结点x的前驱结点（中序），即查找二叉树中值小于x的key值的最大结点
Node* bstree_predecessor(Node *x);

//插入结点并返回插入后的树tree
Node* insert_bstree(BSTree, Type key);

//删除key为结点值的结点，并返回根节点
Node* delete_bstree(BSTree, Type key);

//销毁二叉树
void destroy_bstree(BSTree);

//打印二叉树
void print_bstree(BSTree tree, Type key, int direction);

#endif
