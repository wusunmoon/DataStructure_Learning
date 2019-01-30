#pragma once

/***************************************************************************************
**按照“3+4”结构连接三个节点及其四棵子树，返回重组之后的局部子树根节点位置（即b）
**子树根节点与上层节点之间的双向连接，均须由上层调用者完成
****************************************************************************************/
template<typename T>
BinNodePosi(T) RedBlack<T>::connect34(
	BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c,
	BinNodePosi(T) T0, BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3)
{
	a->lc = T0;	if (T0) T0->parent = a;
	a->rc = T1; if (T1) T1->parent = a;	updateHeight(a);
	c->lc = T2; if (T2) T2->parent = c;
	c->rc = T3; if (T3) T3->parent = c; updateHeight(c);
	b->lc = a; a->parent = b;
	b->rc = c; c->parent = b; updateHeight(b);
	return b;	//该子树新的根节点
}