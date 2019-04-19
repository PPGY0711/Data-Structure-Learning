#include "RBTree.h"
#include <stdio.h>
#include <stdlib.h>

#define rb_parent(r) ((r)->parent)
#define rb_color(r) ((r)->color)
#define rb_is_red(r) ((r)->color==RED)
#define rb_is_black(r) ((r)->color==BLACK)
#define rb_set_black(r) do{(r)->color = BLACK;} while(0)
#define rb_set_red(r) do{(r)->color = RED;} while(0)
#define rb_set_parent(r,p) do{(r)->parent = (p);} while(0)
#define rb_set_color(r,c) do{(r)->color = c;} while(0)

/*
	��������������غ�����ĸ�
*/

RBRoot* create_rbtree()
{
	RBRoot *root = (RBRoot*)malloc(sizeof(RBRoot));
	root->root = NULL;

	return root;
}

static void preorder(RBTree T)
{
	if (T != NULL)
	{
		printf("%d ", T->key);
		preorder(T->left);
		preorder(T->right);
	}
}

void preorder_rbtree(RBRoot *root)
{
	if (root)
		preorder(root->root);
}

static void inorder(RBTree T)
{
	if (T != NULL)
	{
		inorder(T->left);
		printf("%d ", T->key);
		inorder(T->right);
	}
}

void inorder_rbtree(RBRoot *root)
{
	if (root)
		inorder(root->root);
}

static void postorder(RBTree T)
{
	if (T != NULL)
	{
		postorder(T->left);
		postorder(T->right);
		printf("%d ", T->key);
	}
}

void postorder_rbtree(RBRoot *root)
{
	if (root)
		postorder(root->root);
}

static Position search(RBTree x, ElementType key)
{
	if (x == NULL || x->key == key)
	{
		return x;
	}

	if (key < x->key)
		return search(x->left, key);
	else
		return search(x->right, key);
}

int rbtree_search(RBRoot *root, ElementType key)
{
	if (root)
		return search(root->root, key) ? 0 : -1;
}

static Position minimum(RBTree T)
{
	if (T == NULL)
		return NULL;
	
	while(T != NULL)
	{
		T = T->left;
	}
	return T;
}

int rbtree_minimum(RBRoot *root, ElementType *val)
{
	Position node = NULL;

	if (root)
		node = minimum(root->root);

	if (node == NULL)
		return -1;

	*val = node->key;

	return 0;
}

static Position maximum(RBTree T)
{
	if (T == NULL)
		return NULL;

	while (T != NULL)
	{
		T = T->right;
	}
	return T;
}

int rbtree_maximum(RBRoot *root, ElementType *val)
{
	Position node = NULL;

	if (root)
		node = maximum(root->root);

	if (node == NULL)
		return -1;

	*val = node->key;

	return 0;
}

static Position rbtree_successor(RBTree x)
{
	if (x->right != NULL)
		return minimum(x->right);

	Position y = x->parent;
	while ((y != NULL) && (x == y->right))
	{
		x = y;
		y = y->parent;
	}
	return y;
}

static Position rbtree_predecessor(RBTree x) 
{
	if (x->left != NULL)
		return maximum(x->left);

	Position y = x->parent;
	while ((y != NULL) && (x == y->left))
	{
		x = y;
		y = y->parent;
	}
	return y;
}

static void rbtree_left_rotate(RBRoot *root, Position x)
{
	Position y = x->right;

	x->right = y->left;
	if (y->left)
		y->left->parent = x;
	y->parent = x->parent;

	if (x->parent == NULL)
	{
		root->root = y;
	}
	else
	{
		if (x->parent->left == x)
			x->parent->left = y;
		else
			x->parent->right = y;
	}

	y->left = x;
	x->parent = y;
}

static void rbtree_right_rotate(RBRoot *root, Position y)
{
	Position x = y->left;

	y->left = x->right;
	if (x->right)
		x->right->parent = x;
	x->parent = y->parent;

	if (y->parent == NULL)
	{
		root->root = x;
	}
	else
	{
		if (y->parent->left == y)
			y->parent->left = x;
		else
			y->parent->right = x;
	}

	x->right = y;
	y->parent = x;
}

static void rbtree_insert_fixup(RBRoot *root, Position node)
{
	Position parent, grandp;
	while ((parent = rb_parent(node)) && rb_is_red(parent))
	{
		grandp = rb_parent(parent);
		//�����ڵ����游�ڵ������
		if (parent == grandp->left)
		{
			{
				Position uncle = grandp->right;
				//Case 1 :�������ڵ��Ǻ�ɫ
				if (uncle && rb_is_red(uncle))
				{
					rb_set_black(uncle);
					rb_set_black(parent);
					rb_set_red(grandp);
					node = grandp;
					continue;
				}
			}

			//Case 2������ڵ��Ǻ�ɫ���ҵ�ǰ�ڵ����Һ���
			if (parent->right == node)
			{
				Position tmp;
				rbtree_left_rotate(root, parent);
				tmp = parent;
				parent = node;
				node = tmp;
			}
			//Case 3�������Ǻ�ɫ���ҵ�ǰ�ڵ�������
			rb_set_black(parent);
			rb_set_red(grandp);
			rbtree_right_rotate(root, grandp);
		}

		//��֮��ԳƵ�����case
		else
		{
			{
				Position uncle = grandp->left;
				//Case 1 :�������ڵ��Ǻ�ɫ
				if (uncle && rb_is_red(uncle))
				{
					rb_set_black(uncle);
					rb_set_black(parent);
					rb_set_red(grandp);
					node = grandp;
					continue;
				}
			}

			//Case 2������ڵ��Ǻ�ɫ���ҵ�ǰ�ڵ�������
			if (parent->left == node)
			{
				Position tmp;
				rbtree_right_rotate(root, parent);
				tmp = parent;
				parent = node;
				node = tmp;
			}
			//Case 3�������Ǻ�ɫ���ҵ�ǰ�ڵ�������
			rb_set_black(parent);
			rb_set_red(grandp);
			rbtree_left_rotate(root, grandp);
		}
	}
	rb_set_black(root->root);
}

static void rbtree_insert(RBRoot *root, Position node)
{
	Position y = NULL;
	Position x = root->root;

	while (x != NULL)
	{
		y = x;
		if (node->key < x->key)
			x = x->left;
		else
			x = x->right;
	}

	rb_parent(node) = y;
	if (y != NULL)
	{
		if (node->key < y->key)
			y->left = node;
		else
			y->right = node;
	}
	else
	{
		root->root = node;
	}

	node->color = RED;

	rbtree_insert_fixup(root, node);
}

static Position create_rbtree_node(ElementType key, Position parent, Position left, Position right)
{
	Position newp;
	if ((newp = (Position)malloc(sizeof(RBTreeNode))) == NULL)
	{
		return NULL;
	}
	newp->parent = parent;
	newp->left = left;
	newp->right = right;
	newp->key = key;
	newp->color = BLACK;

	return newp;
}


//�������ڵ�ӿ�
int insert_rbtree(RBRoot *root, ElementType key)
{
	Position node;

	if (search(root->root, key) != NULL)
		return -1;
	if ((node = create_rbtree_node(key, NULL, NULL, NULL)) == NULL)
		return -1;

	rbtree_insert(root, node);

	return 0;
}

static void rbtree_delete_fixup(RBRoot *root, Position node, Position parent)
{
	Position sibling;

	while ((!node || rb_is_black(node)) && node != root->root)
	{
		if (parent->left == node)
		{
			sibling = parent->right;
			if (rb_is_red(sibling))
			{
				//case 1�� x���ֵ�w�Ǻ�ɫ��
				rb_set_black(sibling);
				rb_set_red(parent);
				rbtree_left_rotate(root, parent);
				sibling = parent->right;
			}
			if ((!sibling->left || rb_is_black(sibling->left))
				&& (!sibling->right || rb_is_black(sibling->right)))
			{
				//case 2��x���ֵ�w�Ǻ�ɫ��w���������Ӷ��Ǻ�ɫ��
				rb_set_red(sibling);
				node = parent;
				parent = rb_parent(node);
			}
			else
			{
				if (!sibling->right || rb_is_black(sibling->right))
				{
					//case 3��x���ֵ�w�Ǻ�ɫ�ģ�����w�������Ǻ�ɫ���Һ����Ǻ�ɫ
					rb_set_black(sibling->left);
					rb_set_red(sibling);
					rbtree_right_rotate(root, sibling);
					sibling = parent->right;
				}
				//Case 4��x���ֵ�w�Ǻ�ɫ�������Ǻ�ɫ���Һ����Ǻ�ɫ
				rb_set_color(sibling, rb_color(parent));
				rb_set_black(parent);
				rb_set_black(sibling->right);
				rbtree_left_rotate(root, parent);
				node = root->root;
				break;
			}
		}
		else
		{
			sibling = parent->left;
			if (rb_is_red(sibling))
			{
				//case 1�� x���ֵ�w�Ǻ�ɫ��
				rb_set_black(sibling);
				rb_set_red(parent);
				rbtree_left_rotate(root, parent);
				sibling = parent->left;
			}
			if ((!sibling->left || rb_is_black(sibling->left))
				&& (!sibling->right || rb_is_black(sibling->right)))
			{
				//case 2��x���ֵ�w�Ǻ�ɫ��w���������Ӷ��Ǻ�ɫ��
				rb_set_red(sibling);
				node = parent;
				parent = rb_parent(node);
			}
			else
			{
				if (!sibling->left || rb_is_black(sibling->left))
				{
					//case 3��x���ֵ�w�Ǻ�ɫ�ģ�����w�������Ǻ�ɫ���Һ����Ǻ�ɫ
					rb_set_black(sibling->right);
					rb_set_red(sibling);
					rbtree_left_rotate(root, sibling);
					sibling = parent->left;
				}
				//Case 4��x���ֵ�w�Ǻ�ɫ�������Ǻ�ɫ���Һ����Ǻ�ɫ
				rb_set_color(sibling, rb_color(parent));
				rb_set_black(parent);
				rb_set_black(sibling->left);
				rbtree_right_rotate(root, parent);
				node = root->root;
				break;
			}
		}
	}
	if (node)
		rb_set_black(node);
}

void rbtree_delete(RBRoot *root, Position node)
{
	Position child, parent;
	int color;

	//��ɾ���������Һ��Ӷ���Ϊ��
	if ((node->left != NULL) && (node->right != NULL))
	{
		//��ɾ�ڵ�ĺ�̽�㣬��Ϊ��ȡ����㡱
		//������ȡ����ɾ�ڵ�����֣�Ȼ���ٽ�����ɾ�ڵ㡱ȥ��
		Position replace = node;

		replace = replace->right;
		while (replace->left != NULL)
		{
			replace = replace->left;
		}
		if (rb_parent(node))
		{
			if (rb_parent(node)->left == node)
				rb_parent(node)->left = replace;
			else
				rb_parent(node)->right = replace;
		}
		else
			root->root = replace;

		//child��ȡ���ڵ���Һ��ӣ�Ҳ����Ҫ�����Ľڵ�
		//��������Ĳ��裬ȡ���ڵ�϶����������ӣ���Ϊ����һ����̽ڵ�
		child = replace->right;
		parent = rb_parent(replace);
		//����ȡ���ڵ����ɫ
		color = rb_color(replace);
		//�����ɾ�ڵ��Ǻ�̽ڵ�ĸ��ڵ�
		if (parent == node)
		{
			parent = replace;
		}
		else
		{
			//child��Ϊ��
			if (child)
				rb_set_parent(child, parent);
			parent->left = child;

			replace->right = node->right;
			rb_set_parent(node->right, replace);
		}

		replace->parent = node->parent;
		replace->color = node->color;
		replace->left = node->left;
		node->left->parent = replace;

		if (color == BLACK)
			rbtree_delete_fixup(root, child, parent);
		free(node);

		return;
	}

	if (node->left != NULL)
		child = node->left;
	else
		child = node->right;

	parent = node->parent;
	color = node->color;

	if (child)
		child->parent = parent;

	if (parent)
	{
		if (parent->left == node)
			parent->left = child;
		else
			parent->right = child;
	}
	else
		root->root = child;

	if (color == BLACK)
		rbtree_delete_fixup(root, child, parent);
	free(node);

}

void delete_rbtree(RBRoot *root, ElementType key)
{
	Position z, node;
	if ((z = search(root->root, key)) != NULL)
		rbtree_delete(root, z);
}

static void rbtree_destroy(RBTree T)
{
	if (T == NULL)
		return;
	if (T->left != NULL)
		rbtree_destroy(T->left);
	if (T->right != NULL)
		rbtree_destroy(T->right);

	free(T);
}

void destroy_rbtree(RBRoot *root)
{
	if (root)
		rbtree_destroy(root->root);

	free(root);
}

static void rbtree_print(RBTree T, ElementType key, int direction)
{
	if (T)
	{
		if (direction == 0)
			printf("%2d(B) is root\n", T->key);
		else
			printf("%2d(%s) is %2d's %6s child\n", T->key, rb_is_red(T) ? "R" : "B",
				key, direction == 1 ? "right" : "left");
		rbtree_print(T->left, T->key, -1);
		rbtree_print(T->right, T->key, 1);
	}
}

void print_rbtree(RBRoot *root)
{
	if (root != NULL && root->root != NULL)
		rbtree_print(root->root, root->root->key, 0);
}



#define CHECK_INSERT 0    // "����"�����ļ�⿪��(0���رգ�1����)
#define CHECK_DELETE 0    // "ɾ��"�����ļ�⿪��(0���رգ�1����)
#define LENGTH(a) ( (sizeof(a)) / (sizeof(a[0])) )

int main()
{
	int a[] = { 10, 40, 30, 60, 90, 70, 20, 50, 80 };
	int i, ilen = LENGTH(a);
	RBRoot *root = NULL;

	root = create_rbtree();
	printf("== ԭʼ����: ");
	for (i = 0; i<ilen; i++)
		printf("%d ", a[i]);
	printf("\n");

	for (i = 0; i<ilen; i++)
	{
		insert_rbtree(root, a[i]);
#if CHECK_INSERT
		printf("== ��ӽڵ�: %d\n", a[i]);
		printf("== ������ϸ��Ϣ: \n");
		print_rbtree(root);
		printf("\n");
#endif
	}

	printf("== ǰ�����: ");
	preorder_rbtree(root);

	printf("\n== �������: ");
	inorder_rbtree(root);

	printf("\n== �������: ");
	postorder_rbtree(root);
	printf("\n");

	if (rbtree_minimum(root, &i) == 0)
		printf("== ��Сֵ: %d\n", i);
	if (rbtree_maximum(root, &i) == 0)
		printf("== ���ֵ: %d\n", i);
	printf("== ������ϸ��Ϣ: \n");
	print_rbtree(root);
	printf("\n");

#if CHECK_DELETE
	for (i = 0; i<ilen; i++)
	{
		delete_rbtree(root, a[i]);

		printf("== ɾ���ڵ�: %d\n", a[i]);
		if (root)
		{
			printf("== ������ϸ��Ϣ: \n");
			print_rbtree(root);
			printf("\n");
		}
	}
#endif

	destroy_rbtree(root);

	system("PAUSE");
	return 0;
}