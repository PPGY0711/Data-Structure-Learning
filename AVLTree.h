#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

typedef int Type;

typedef struct AVLTreeNode{
	Type key; //��ֵ 
	int height; //�߶� 
	struct AVLTreeNode *left; //���� 
	struct AVLTreeNode *right; //�Һ��� 
}Node, *AVLTree;

//��ȡAVL���ĸ߶� 
int avltree_height(AVLTree tree);

//ǰ�����
void preorder_avltree(AVLTree tree);
//�������
void inorder_avltree(AVLTree tree);
//�������
void postorder_avltree(AVLTree tree);

void print_avltree(AVLTree tree, Type key, int direction);

//�ݹ�ʵ�� ���Ҽ�ֵΪkey�Ľڵ� 
Node* avltree_search(AVLTree x, Type key);
// �ǵݹ�ʵ�� ���Ҽ�ֵΪkey�Ľڵ�
Node* iterative_avltree_search(AVLTree tree, Type key);

//������С��㣺����treeΪ���ڵ��AVL������С���
Node* avltree_minimum(AVLTree tree);
//��������㣺����treeΪ���ڵ��AVL���������
Node* avltree_maximum(AVLTree tree);

//�������뵽AVL���У����ظ��ڵ�
Node* avltree_insert(AVLTree tree, Type key);

//ɾ����ֵΪkey�Ľڵ㣬���ظ��ڵ�
Node* avltree_delete(AVLTree tree, Type key);

//����AVL��
void destroy_avltree(AVLTree tree);

#endif
 
