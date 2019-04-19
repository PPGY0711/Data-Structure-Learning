#pragma once
#ifndef _RED_BLACK_TREE_H_
#define _RED_BLACK_TREE_H_

#define RED 0
#define BLACK 1

typedef int ElementType;

//红黑树节点
typedef struct RBTreeNode
{
	unsigned char color;
	ElementType key;
	struct RBTreeNode *left;
	struct RBTreeNode *right;
	struct RBTreeNode *parent;
}*RBTree,*Position;

typedef struct re_root
{
	RBTree root;
}RBRoot;

//创建红黑树，返回红黑树的根
RBRoot* create_rbtree();

//销毁红黑树
void destroy_rbtree(RBRoot *root);

//将节点插入到红黑树中，插入成功，返回0；失败，返回-1
int insert_rbtree(RBRoot *root, ElementType key);
//删除
void delete_rbtree(RBRoot *root, ElementType key);

// 前序遍历"红黑树"
void preorder_rbtree(RBRoot *root);
// 中序遍历"红黑树"
void inorder_rbtree(RBRoot *root);
// 后序遍历"红黑树"
void postorder_rbtree(RBRoot *root);

// (递归实现)查找"红黑树"中键值为key的节点。找到的话，返回0；否则，返回-1。
int rbtree_search(RBRoot *root, ElementType key);
// (非递归实现)查找"红黑树"中键值为key的节点。找到的话，返回0；否则，返回-1。
//int iterative_rbtree_search(RBRoot *root, ElementType key);

// 返回最小结点的值(将值保存到val中)。找到的话，返回0；否则返回-1。
int rbtree_minimum(RBRoot *root, int *val);
// 返回最大结点的值(将值保存到val中)。找到的话，返回0；否则返回-1。
int rbtree_maximum(RBRoot *root, int *val);

// 打印红黑树
void print_rbtree(RBRoot *root);

#endif // !_RED_BLACK_TREE_H_
