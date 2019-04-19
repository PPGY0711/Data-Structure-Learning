#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

typedef int Type;

typedef struct AVLTreeNode{
	Type key; //键值 
	int height; //高度 
	struct AVLTreeNode *left; //左孩子 
	struct AVLTreeNode *right; //右孩子 
}Node, *AVLTree;

//获取AVL树的高度 
int avltree_height(AVLTree tree);

//前序遍历
void preorder_avltree(AVLTree tree);
//中序遍历
void inorder_avltree(AVLTree tree);
//后序遍历
void postorder_avltree(AVLTree tree);

void print_avltree(AVLTree tree, Type key, int direction);

//递归实现 查找键值为key的节点 
Node* avltree_search(AVLTree x, Type key);
// 非递归实现 查找键值为key的节点
Node* iterative_avltree_search(AVLTree tree, Type key);

//查找最小结点：返回tree为根节点的AVL树的最小结点
Node* avltree_minimum(AVLTree tree);
//查找最大结点：返回tree为根节点的AVL树的最大结点
Node* avltree_maximum(AVLTree tree);

//将结点插入到AVL树中，返回根节点
Node* avltree_insert(AVLTree tree, Type key);

//删除键值为key的节点，返回根节点
Node* avltree_delete(AVLTree tree, Type key);

//销毁AVL树
void destroy_avltree(AVLTree tree);

#endif
 
