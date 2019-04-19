#include <stdio.h>
#include <stdlib.h>
#include "AVLTree.h"

#define HEIGHT(p) ((p==NULL) ? 0 : (((Node*)(p))->height))
#define MAX(a,b) ((a) > (b) ? (a) : (b))

//��ȡAVL���ĸ߶� 
int avltree_height(AVLTree tree)
{
	return HEIGHT(tree);
}

//ǰ�����
void preorder_avltree(AVLTree tree)
{
	if(tree != NULL)
	{
		printf("%d ",tree->key);
		preorder_avltree(tree->left);
		preorder_avltree(tree->right);
	}
}
//�������
void inorder_avltree(AVLTree tree)
{
	if(tree != NULL)
	{
		inorder_avltree(tree->left);
		printf("%d ",tree->key);
		inorder_avltree(tree->right);
	}
}
//�������
void postorder_avltree(AVLTree tree)
{
	if(tree != NULL)
	{
		postorder_avltree(tree->left);	
		postorder_avltree(tree->right);
		printf("%d ",tree->key);
	}
}

void print_avltree(AVLTree tree, Type key, int direction)
{
	if(tree != NULL)
	{
		if(direction == 0)
			printf("%2d is root\n",tree->key);
		else
			printf("%2d is %2d's %6s child\n", tree->key, key,direction == -1?"left":"right");
		
		print_avltree(tree->left,tree->key,-1);
		print_avltree(tree->right,tree->key,1);	
	}
}

//�ݹ�ʵ�� ���Ҽ�ֵΪkey�Ľڵ� 
Node* avltree_search(AVLTree x, Type key)
{
	if(x == NULL || x->key == key)
		return x;
	
	if(x->key > key)
		return avltree_search(x->left, key);
	else
		return avltree_search(x->right, key);
}

// �ǵݹ�ʵ�� ���Ҽ�ֵΪkey�Ľڵ�
Node* iterative_avltree_search(AVLTree x, Type key)
{
	while(x != NULL && (x->key) != key)
	{
		if(key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	
	return x;
}

//������С��㣺����treeΪ���ڵ��AVL������С���
Node* avltree_minimum(AVLTree tree)
{
	if(tree == NULL)
		return NULL;
	
	while(tree->left != NULL)
		tree = tree->left;
	return tree;
}

//��������㣺����treeΪ���ڵ��AVL���������
Node* avltree_maximum(AVLTree tree)
{
	if(tree == NULL)
		return NULL;
		
	while(tree->right != NULL)
		tree = tree->right;
	return tree;
}

// LL��ת 
static Node* left_left_rotation(AVLTree k2)
{
	AVLTree k1;
	
	k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	
	k2->height = MAX(HEIGHT(k2->left),HEIGHT(k2->right)) + 1;
	k1->height = MAX(HEIGHT(k1->left),k2->height) + 1;
	
	return k1;
	
}

// RR��ת 
static Node* right_right_rotation(AVLTree k1)
{
	AVLTree k2;
	
	k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;
	
	k1->height = MAX(HEIGHT(k1->left),HEIGHT(k1->right)) + 1;
	k2->height = MAX(HEIGHT(k1->right),k1->height) + 1;
	
	return k2;
	
}

// LR ������ת 
static Node* left_right_rotation(AVLTree k3)
{
	k3->left = right_right_rotation(k3->left);
	
	k3 = left_left_rotation(k3);
	
	return k3;
}

// RL ������ת 
static Node* right_left_rotation(AVLTree k1)
{
	k1->right = left_left_rotation(k1->right);
	
	k1 = right_right_rotation(k1);
	
	return k1;
}

// ����AVL���ڵ�
static Node* avltree_create_node(Type key, Node* left, Node* right)
{
	Node *p;
	
	if((p = (Node*)malloc(sizeof(Node))) == NULL)
		return NULL;
	p->key = key;
	p->left = left;
	p->right = right;
	p->height = 0;
	
	return p;	
} 

//�������뵽AVL���У����ظ��ڵ�
Node* avltree_insert(AVLTree tree, Type key)
{
	if(tree == NULL)
	{
		tree = avltree_create_node(key, NULL, NULL);
		if(tree == NULL)
		{
			printf("ERROR: create avltree node failed!\n");
			return NULL;
		}
	}
	else if(key < tree->key)
	{
		tree->left = avltree_insert(tree->left , key);
		if(HEIGHT(tree->left) - HEIGHT(tree->right) == 2)
		{
			 //printf("1here\n");
			if(key < tree->left->key)
				tree = left_left_rotation(tree);
			else
				tree = left_right_rotation(tree);
		}
	}
	else if(key > tree->key)
	{
		tree->right = avltree_insert(tree->right, key);
		if(HEIGHT(tree->right) - HEIGHT(tree->left) == 2)
		{
			//printf("2here\n");
			if(key > tree->right->key)
				tree = right_right_rotation(tree);
			else
				tree = right_left_rotation(tree);
		}
	}
	else //key == tree->key
	{
		printf("insertion failed: nodes with the same key value are not allowed!\n"); 
	} 
	//printf("3here\n");
	tree->height = MAX(HEIGHT(tree->left),HEIGHT(tree->right)) + 1;
	//printf("The height of key %d is %d \n",tree->key,tree->height);
	return tree;
}

//ɾ�����z 
static Node* delete_node(AVLTree tree, Node* z)
{
	if(tree == NULL || z == NULL)
		return NULL;
		
	if(z->key < tree->key)
	{
		tree->left = delete_node(tree->left,z);
		if(HEIGHT(tree->right) - HEIGHT(tree->left) == 2)
		{
			Node *r = tree->right;
			
			if(HEIGHT(r->right) > HEIGHT(r->left))
				tree = right_right_rotation(tree);
			else
				tree = right_left_rotation(tree);
		}
	}
	else if(z->key > tree->key)
	{
		tree->right = delete_node(tree->right,z);
		
		if(HEIGHT(tree->left)-HEIGHT(tree->right) == 2)
		{
			Node *l = tree->left;
			if(HEIGHT(l->left) > HEIGHT(l->right))
				tree = left_left_rotation(tree);
			else
				tree = left_right_rotation(tree);
		}
	}
	else //tree��Ҫɾ���Ľڵ�
	{
		printf("\n==�������߶�: %d", avltree_height(tree->left));
		printf("\n==�������߶�: %d", avltree_height(tree->right));

		if((tree->left) && (tree->right))
		{
			if(HEIGHT(tree->left) >HEIGHT(tree->right))
			{
				Node *max = avltree_maximum(tree->left);
				tree->key = max->key;
				tree->left = delete_node(tree->left,max);
			}
			else
			{
				Node *min = avltree_minimum(tree->right);
				tree->key = min->key;
				tree->right = delete_node(tree->right,min);
			}
		}
		else
		{
			Node *tmp = tree;
			tree = tree->left ? tree->left : tree->right;
			free(tmp);
		}
	}
	
	//ÿ��ɾ������ʱ�����ĸ߶Ƚ��и���
	if (tree != NULL)
	{
		if ((tree->left) && (tree->right))
		{
			tree->left->height = MAX(HEIGHT(tree->left->left), HEIGHT(tree->left->right)) + 1;
			tree->right->height = MAX(HEIGHT(tree->right->right), HEIGHT(tree->right->right)) + 1;
			tree->height = MAX(HEIGHT(tree->left), HEIGHT(tree->right)) + 1;
		}
		else if (tree->left)
		{
			tree->height = 2;
		}
		else if (tree->right)
		{
			tree->height = 2;
		}
		else
		{
			tree->height = 1;
		}
	}
	
	return tree; 
}

//ɾ����ֵΪkey�Ľڵ㣬���ظ��ڵ�
Node* avltree_delete(AVLTree tree, Type key)
{
	Node *z;
	
	if((z = avltree_search(tree, key)) != NULL)
		tree = delete_node(tree, z);
	return tree;
}

//����AVL��
void destroy_avltree(AVLTree tree)
{
	if(tree == NULL)
		return ;
	
	if(tree->left != NULL)
		destroy_avltree(tree->left);
	if(tree->right != NULL)
		destroy_avltree(tree->right);
		
	free(tree);
}

//for test 
//static int arr[]= {3,2,1,4,5,6,7,16,15,14,13,12,11,10,8,9};
static int arr[]= {3,2,1,4,5,6,7};

#define TBL_SIZE(a) ( (sizeof(a)) / (sizeof(a[0])) )

int main()
{
    int i,ilen;
    AVLTree root=NULL;

    printf("== �߶�: %d\n", avltree_height(root));
    printf("== �������: ");
    ilen = TBL_SIZE(arr);
    for(i=0; i<ilen; i++)
    { 
        //printf("test\n");
		printf("%d ", arr[i]);
        root = avltree_insert(root, arr[i]);
         
        //printf("test\n");
		//preorder_avltree(root);
    }

    printf("\n== ǰ�����: ");
    preorder_avltree(root);

    printf("\n== �������: ");
    inorder_avltree(root);

    printf("\n== �������: ");
    postorder_avltree(root);
    printf("\n");

    printf("== �߶�: %d\n", avltree_height(root));
    printf("== ��Сֵ: %d\n", avltree_minimum(root)->key);
    printf("== ���ֵ: %d\n", avltree_maximum(root)->key);
    printf("== ������ϸ��Ϣ: \n");
    print_avltree(root, root->key, 0);

//���Ľṹ��ȷ����Ϊÿ��rotate������¸߶ȣ������������ĸ߶��Ǵ�ġ�
	//update:���ϴ����Ѹ���
    i = 6;
    printf("\n== ɾ�����ڵ�: %d\n", i);
    root = avltree_delete(root, i);
    print_avltree(root, root->key, 0);
    
	i = 5;
    printf("\n== ɾ�����ڵ�: %d\n", i);
    root = avltree_delete(root, i);
    print_avltree(root, root->key, 0);
    
	i = 4;
    printf("\n== ɾ�����ڵ�: %d\n", i);
    root = avltree_delete(root, i);
    print_avltree(root, root->key, 0);

    /*
	i = 3;
    printf("\n== ɾ�����ڵ�: %d\n", i);
    root = avltree_delete(root, i);
    print_avltree(root, root->key, 0);
    
    i = 2;
    printf("\n== ɾ�����ڵ�: %d\n", i);
    root = avltree_delete(root, i);
    print_avltree(root, root->key, 0);
    */
/*    
    if((root->left) && (root->right))
    {
		root->left->height = MAX(HEIGHT(root->left->left),HEIGHT(root->left->right)) + 1;
	    root->right->height = MAX(HEIGHT(root->right->right),HEIGHT(root->right->right)) + 1;
	    root->height = MAX(HEIGHT(root->left),HEIGHT(root->right)) + 1;
	}
    else if(root->left)
    {
    	root->height = 2;
	}
	else if(root->right)
	{
		root->height = 2;
	}
	else
	{
		root->height = 1;
	}
*/   
	printf("\n==�������߶ȣ� %d",avltree_height(root->left));
    printf("\n==�������߶ȣ� %d",avltree_height(root->right));
	printf("\n== �߶�: %d", avltree_height(root));
    printf("\n== �������: ");
    inorder_avltree(root);
    printf("\n== ������ϸ��Ϣ: \n");
    print_avltree(root, root->key, 0);

    // ���ٶ�����
    destroy_avltree(root);
	system("PAUSE");
    return 0;
	
}
