#include <stdio.h>
#include <stdlib.h>
#include "AVLTree.h"

#define HEIGHT(p) ((p==NULL) ? 0 : (((Node*)(p))->height))
#define MAX(a,b) ((a) > (b) ? (a) : (b))

//获取AVL树的高度 
int avltree_height(AVLTree tree)
{
	return HEIGHT(tree);
}

//前序遍历
void preorder_avltree(AVLTree tree)
{
	if(tree != NULL)
	{
		printf("%d ",tree->key);
		preorder_avltree(tree->left);
		preorder_avltree(tree->right);
	}
}
//中序遍历
void inorder_avltree(AVLTree tree)
{
	if(tree != NULL)
	{
		inorder_avltree(tree->left);
		printf("%d ",tree->key);
		inorder_avltree(tree->right);
	}
}
//后序遍历
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

//递归实现 查找键值为key的节点 
Node* avltree_search(AVLTree x, Type key)
{
	if(x == NULL || x->key == key)
		return x;
	
	if(x->key > key)
		return avltree_search(x->left, key);
	else
		return avltree_search(x->right, key);
}

// 非递归实现 查找键值为key的节点
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

//查找最小结点：返回tree为根节点的AVL树的最小结点
Node* avltree_minimum(AVLTree tree)
{
	if(tree == NULL)
		return NULL;
	
	while(tree->left != NULL)
		tree = tree->left;
	return tree;
}

//查找最大结点：返回tree为根节点的AVL树的最大结点
Node* avltree_maximum(AVLTree tree)
{
	if(tree == NULL)
		return NULL;
		
	while(tree->right != NULL)
		tree = tree->right;
	return tree;
}

// LL旋转 
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

// RR旋转 
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

// LR 左右旋转 
static Node* left_right_rotation(AVLTree k3)
{
	k3->left = right_right_rotation(k3->left);
	
	k3 = left_left_rotation(k3);
	
	return k3;
}

// RL 右左旋转 
static Node* right_left_rotation(AVLTree k1)
{
	k1->right = left_left_rotation(k1->right);
	
	k1 = right_right_rotation(k1);
	
	return k1;
}

// 创建AVL树节点
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

//将结点插入到AVL树中，返回根节点
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

//删除结点z 
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
	else //tree是要删除的节点
	{
		printf("\n==左子树高度: %d", avltree_height(tree->left));
		printf("\n==右子树高度: %d", avltree_height(tree->right));

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
	
	//每次删除返回时对树的高度进行更新
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

//删除键值为key的节点，返回根节点
Node* avltree_delete(AVLTree tree, Type key)
{
	Node *z;
	
	if((z = avltree_search(tree, key)) != NULL)
		tree = delete_node(tree, z);
	return tree;
}

//销毁AVL树
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

    printf("== 高度: %d\n", avltree_height(root));
    printf("== 依次添加: ");
    ilen = TBL_SIZE(arr);
    for(i=0; i<ilen; i++)
    { 
        //printf("test\n");
		printf("%d ", arr[i]);
        root = avltree_insert(root, arr[i]);
         
        //printf("test\n");
		//preorder_avltree(root);
    }

    printf("\n== 前序遍历: ");
    preorder_avltree(root);

    printf("\n== 中序遍历: ");
    inorder_avltree(root);

    printf("\n== 后序遍历: ");
    postorder_avltree(root);
    printf("\n");

    printf("== 高度: %d\n", avltree_height(root));
    printf("== 最小值: %d\n", avltree_minimum(root)->key);
    printf("== 最大值: %d\n", avltree_maximum(root)->key);
    printf("== 树的详细信息: \n");
    print_avltree(root, root->key, 0);

//树的结构正确，因为每次rotate都会更新高度，但是最终树的高度是错的。
	//update:以上错误已更新
    i = 6;
    printf("\n== 删除根节点: %d\n", i);
    root = avltree_delete(root, i);
    print_avltree(root, root->key, 0);
    
	i = 5;
    printf("\n== 删除根节点: %d\n", i);
    root = avltree_delete(root, i);
    print_avltree(root, root->key, 0);
    
	i = 4;
    printf("\n== 删除根节点: %d\n", i);
    root = avltree_delete(root, i);
    print_avltree(root, root->key, 0);

    /*
	i = 3;
    printf("\n== 删除根节点: %d\n", i);
    root = avltree_delete(root, i);
    print_avltree(root, root->key, 0);
    
    i = 2;
    printf("\n== 删除根节点: %d\n", i);
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
	printf("\n==左子树高度： %d",avltree_height(root->left));
    printf("\n==右子树高度： %d",avltree_height(root->right));
	printf("\n== 高度: %d", avltree_height(root));
    printf("\n== 中序遍历: ");
    inorder_avltree(root);
    printf("\n== 树的详细信息: \n");
    print_avltree(root, root->key, 0);

    // 销毁二叉树
    destroy_avltree(root);
	system("PAUSE");
    return 0;
	
}
