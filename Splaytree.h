#pragma once
/*
 * 带有父亲指针实现的伸展树，自底向上实现伸展
 */

#ifndef _SPLAYTREE_H_
#define _SPLAYTREE_H_

struct SplayNode;
typedef int ElementType;
typedef SplayNode* Position;
typedef SplayNode* SplayTree;

struct SplayNode
{
	ElementType Element;
	SplayTree Parent;
	SplayTree Left;
	SplayTree Right;
};

SplayTree Insert(ElementType x, SplayTree T);
SplayTree Delete(ElementType x, SplayTree T);
SplayTree Find(ElementType x, SplayTree T);
SplayTree makeEmpty(SplayTree T);
SplayTree minimum(SplayTree T);
SplayTree maximum(SplayTree T);

/*
SplayTree LeftLeftRotation(SplayTree T);
SplayTree RightRightRotation(SplayTree T);
SplayTree LeftRightRotation(SplayTree T);
SplayTree RightLeftRotation(SplayTree T);
*/

SplayTree LeftSingleRotation(SplayTree T);
SplayTree RightSingleRotation(SplayTree T);
SplayTree LeftDoubleRotation(SplayTree T);
SplayTree RightDoubleRotation(SplayTree T);

SplayTree Splay(Position P, SplayTree T);

void PrintTree(SplayTree T, int depth);
void PrintTree(SplayTree T);
void PrintDepth(ElementType A, int depth);
void PrintSplaytree(SplayTree tree, ElementType key, int direction);
#endif // !_SPLAYTREE_H_
