#pragma once

template<typename T>	//在以v为根的子树中查找关键码e
static BinNodePosi(T)& searchIn(BinNodePosi(T)& v, const T& e, BinNodePosi(T)& hot)
{
	if (!v || (e == v->data))	//递归基：在节点v（或假想的通配节点）处命中
		return v;
	hot = v;	//一般情况：先记下当前节点，然后再
	return searchIn(((e < v->data) ? v->lc : v->rc), e, hot);	//深入一层，递归查找
}	//返回时，返回值指向命中节点（或假想的通配哨兵），hot指向其父亲（退化时为初始值NULL）
template<typename T>	//在红黑树中查找关键码e
BinNodePosi(T)& RedBlack<T>::search(const T& e)
{
	return searchIn(_root, e, _hot = NULL);	//返回目标节点位置的引用，以便后续插入、删除操作
}
