/*
* 带有父亲指针实现的伸展树，自底向上实现
*/

#include "Splaytree.h"
#include <stdlib.h>
#include <iostream>

SplayTree searchValue(ElementType x, SplayTree T)
{
	if (x < T->Element && T->Left)
		return searchValue(x, T->Left);
	else if (x > T->Element && T->Right)
		return searchValue(x, T->Right);
	else return T;
}

SplayTree Find(ElementType x, SplayTree T)
{
	if (T == NULL)
	{
		fprintf(stderr, "empty tree");
		return T;
	}

	Position newp = searchValue(x, T);
	if (newp != T)
		return Splay(newp, T);
	else return T;
}

SplayTree Insert(ElementType x, SplayTree T)
{
	if (T == NULL)
	{
		T = (SplayTree)malloc(sizeof(SplayNode));
		if (T == NULL)
		{
			fprintf(stderr, "not enought memory");
			exit(1);
		}
		T->Element = x;
		T->Left = T->Right = T->Parent = NULL;
		return T;
	}

	if (x == T->Element)
		return T;
	else
	{
		Position tempP = T;
		Position temp = T;
		while (temp != NULL)
		{
			if (x < temp->Element)
			{
				tempP = temp;
				temp = temp->Left;
			}
			else if (x > temp->Element)
			{
				tempP = temp;
				temp = temp->Right;
			}
			else
				break;
		}
		//没有值为x的节点，x可以插入
		if (temp == NULL)
		{
			Position newp = (SplayTree)malloc(sizeof(SplayNode));
			if (newp == NULL)
			{
				fprintf(stderr, "not enought memory");
				exit(1);
			}
			newp->Element = x;
			newp->Left = newp->Right = NULL;
			newp->Parent = tempP;
			if (x < tempP->Element)
				tempP->Left = newp;
			else
				tempP->Right = newp;

			temp = newp;
		}

		T = Splay(temp, T);
	}
	return T;
}

SplayTree Delete(ElementType x, SplayTree T)
{
	if (T == NULL)
	{
		fprintf(stderr, "%d don't exist", x);
	}
	T = Find(x, T);
	//要寻找的值已经变成根节点，如果相等则找到，不相等则不存在，此时在根节点的是最接近于要删除的值的节点
	if (x == T->Element)
	{
		//根的左右子树都存在
		if (T->Left && T->Right)
		{
			Position Ltemp, Rtemp;
			Ltemp = T->Left;
			Rtemp = T->Right;
			//左右子树的父亲节点设置为NULL
			Ltemp->Parent = Rtemp->Parent = NULL;

			free(T);
			Ltemp = maximum(Ltemp);
			Ltemp->Right = Rtemp;
			Rtemp->Parent = Ltemp;
			return Ltemp;			
		}
		else if (T->Left)
		{
			Position Ltemp = T->Left;
			Ltemp->Parent = NULL;
			free(T);
			return Ltemp;
		}
		else
		{
			Position Rtemp = T->Right;
			Rtemp->Parent = NULL;
			free(T);
			return Rtemp;
		}
	}
	else
	{
		fprintf(stderr, "%d do not exit", x);
		return T;
	}
}

SplayTree minimum(SplayTree T)
{
	Position newp = T;
	if (T != NULL)
	{
		while (newp->Left != NULL)
			newp = newp->Left;
		return Splay(newp, T);
	}
	return NULL;
}


SplayTree maximum(SplayTree T)
{
	Position newp = T;
	if (T != NULL)
	{
		while (newp->Right != NULL)
			newp = newp->Right;
		return Splay(newp, T);
	}
	return NULL;
}

SplayTree RightSingleRotation(SplayTree T)
{
	SplayTree k1, parent;

	parent = T->Parent;
	k1 = T->Left;
	k1->Parent = parent;

	if (k1->Right)
		k1->Right->Parent = T;
	T->Left = k1->Right;

	T->Parent = k1;
	k1->Right = T;

	//包括了LL，RL的第一步旋转（LL时先转祖父、父亲和先转父亲、儿子一眼的）
	if (parent)
	{
		if (parent->Left == T)
			parent->Left = k1;
		else
			parent->Right = k1;
	}

	return k1;
}

SplayTree LeftSingleRotation(SplayTree T)
{
	SplayTree k2, parent;

	parent = T->Parent;
	k2 = T->Right;

	k2->Parent = parent;

	if (k2->Left)
		k2->Left->Parent = T;
	T->Right = k2->Left;

	T->Parent = k2;
	k2->Left = T;

	if (parent)
	{
		if (parent->Left == T)
			parent->Left = k2;
		else
			parent->Right = k2;
	}

	return k2;
}

SplayTree RightDoubleRotation(SplayTree T)
{
	LeftSingleRotation(T->Left);
	return RightSingleRotation(T);
}

SplayTree LeftDoubleRotation(SplayTree T)
{
	RightSingleRotation(T->Right);
	return LeftSingleRotation(T);
}

SplayTree Splay(Position newp, SplayTree T)
{
	Position parent, grandp;

	parent = newp->Parent;

	while (parent != NULL)
	{
		grandp = parent->Parent;

		if (newp == parent->Left)
		{
			if (grandp == NULL)
				RightSingleRotation(parent);
			else if (grandp->Left == parent)
			{
				RightSingleRotation(grandp);
				RightSingleRotation(parent);
			}
			else
				LeftDoubleRotation(grandp);
		}
		else
		{
			if (grandp == NULL)
				LeftSingleRotation(parent);
			else if (grandp->Right == parent)
			{
				LeftSingleRotation(grandp);
				LeftSingleRotation(parent);
			}
			else
				RightDoubleRotation(grandp);
		}

		parent = newp->Parent;
	}

	return newp;
}

void PrintDepth(ElementType A, int depth)
{
	while (depth != 0)
	{
		printf("  ",depth);
		depth--;
	}
	printf("%d\n", A);
}

void PrintTree(SplayTree T, int depth)
{
	if (T == NULL)
	{
		perror("wrong tree");
		exit(1);
	}
	if (T->Left != NULL)
		PrintTree(T->Left, depth + 1);

	PrintDepth(T->Element, depth);

	if (T->Right != NULL)
		PrintTree(T->Right, depth + 1);
}

void PrintTree(SplayTree T)
{
	if (T == NULL)
	{
		perror("wrong tree");
		exit(1);
	}
	if (T->Left != NULL)
		PrintTree(T->Left);

	printf("%d ", T->Element);

	if (T->Right != NULL)
		PrintTree(T->Right);
}

SplayTree makeEmpty(SplayTree T)
{
	if (T != NULL)
	{
		makeEmpty(T->Left);
		makeEmpty(T->Right);
		free(T);
	}
	return NULL;
}

void PrintSplaytree(SplayTree tree, ElementType key, int direction)
{
	if (tree != NULL)
	{
		if (direction == 0)
			printf("%2d is root\n", tree->Element);
		else
			printf("%2d is %2d's %6s child\n", tree->Element, key, direction == -1 ? "left" : "right");

		PrintSplaytree(tree->Left, tree->Element, -1);
		PrintSplaytree(tree->Right, tree->Element, 1);
	}
}

//test
int main()
{
	int i;
	SplayTree T;

	T = NULL;
	//插入数据
	T = Insert(10, T);

	for (i = 0; i < 10; i++)
	{
		T = Insert(2 * i, T);
		PrintSplaytree(T, T->Element, 0);
	}

	for (i = 0; i < 10; i++)
	{
		T = Insert(2 * i + 1, T);
	}

	PrintTree(T, 0);
	printf("\n\n\n");

	T = Find(5, T);
	PrintTree(T, 0);
	printf("\n\n\n");

	T = Delete(11, T);
	T = Delete(3, T);
	T = Delete(21, T);
	printf("\n\n\n");
	printf("\n\n\n");

	T = Delete(3, T);
	T = Delete(8, T);
	T = Delete(16, T);
	PrintTree(T, 0);
	PrintSplaytree(T, T->Element, 0);
	std::cout << std::endl;
	system("PAUSE");
	return 0;
}