#ifndef _BINARY_SEARCH_TREE_H_
#define _BINARY_SEARCH_TREE_H_

typedef int Type;

typedef struct BSTreeNode{
	Type key;
	struct BSTreeNode *left;
	struct BSTreeNode *right;
	struct BSTreeNode *parent;
}Node, *BSTree;

//ǰ�����������
void preorder_bstree(BSTree tree);
//�������������
void inorder_bstree(BSTree tree);
//�������������
void postorder_bstree(BSTree tree);

//�ݹ�ʵ�� ���Ҷ�����x��ֵΪkey�Ľ��
Node* bstree_search(BSTree x,Type key);
//�ǵݹ�ʵ�� ���Ҷ�����x��ֵΪkey�Ľ��
Node* iterative_bstree_search(BSTree x,Type key);

//������С��㣺����treeΪ���ڵ�Ķ���������С���
Node* bstree_minimum(BSTree tree);
//��������㣺����treeΪ���ڵ�Ķ������������
Node* bstree_maximum(BSTree tree);

//�ҽ��x�ĺ�̽�㣨���򣩣������Ҷ�������ֵ����x��keyֵ����С���
Node* bstree_successor(Node *x);
//�ҽ��x��ǰ����㣨���򣩣������Ҷ�������ֵС��x��keyֵ�������
Node* bstree_predecessor(Node *x);

//�����㲢���ز�������tree
Node* insert_bstree(BSTree, Type key);

//ɾ��keyΪ���ֵ�Ľ�㣬�����ظ��ڵ�
Node* delete_bstree(BSTree, Type key);

//���ٶ�����
void destroy_bstree(BSTree);

//��ӡ������
void print_bstree(BSTree tree, Type key, int direction);

#endif
