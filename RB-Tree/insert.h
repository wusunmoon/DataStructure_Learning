#pragma once

template<typename T>
BinNodePosi(T) RedBlack<T>::insert(const T& e)	//将e插入红黑树
{
	BinNodePosi(T)& x = search(e);	if (x) return x;	//确认目标不存在
	x = new BinNode<T>(e, _hot, NULL, NULL, -1);	_size++;	//创建红节点x：以_hot为父，黑高度-1
	solveDoubleRed(x);	//经双红修正后，即可返回
	return x ? x : _hot->parent;	//无论e是否存在于原树中，返回时总有x->data==e
}
