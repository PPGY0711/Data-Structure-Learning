#pragma once
#ifndef _RED_BLACK_TREE_H_
#define _RED_BLACK_TREE_H_

#define RED 0
#define BLACK 1

typedef int ElementType;

//������ڵ�
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

//��������������غ�����ĸ�
RBRoot* create_rbtree();

//���ٺ����
void destroy_rbtree(RBRoot *root);

//���ڵ���뵽������У�����ɹ�������0��ʧ�ܣ�����-1
int insert_rbtree(RBRoot *root, ElementType key);
//ɾ��
void delete_rbtree(RBRoot *root, ElementType key);

// ǰ�����"�����"
void preorder_rbtree(RBRoot *root);
// �������"�����"
void inorder_rbtree(RBRoot *root);
// �������"�����"
void postorder_rbtree(RBRoot *root);

// (�ݹ�ʵ��)����"�����"�м�ֵΪkey�Ľڵ㡣�ҵ��Ļ�������0�����򣬷���-1��
int rbtree_search(RBRoot *root, ElementType key);
// (�ǵݹ�ʵ��)����"�����"�м�ֵΪkey�Ľڵ㡣�ҵ��Ļ�������0�����򣬷���-1��
//int iterative_rbtree_search(RBRoot *root, ElementType key);

// ������С����ֵ(��ֵ���浽val��)���ҵ��Ļ�������0�����򷵻�-1��
int rbtree_minimum(RBRoot *root, int *val);
// ����������ֵ(��ֵ���浽val��)���ҵ��Ļ�������0�����򷵻�-1��
int rbtree_maximum(RBRoot *root, int *val);

// ��ӡ�����
void print_rbtree(RBRoot *root);

#endif // !_RED_BLACK_TREE_H_
