#pragma once

#include"utilities.h"

template<typename T>
BTNodePosi(T) BTree<T>::search(const T& e)	//在B-树中查找关键码e
{
	BTNodePosi(T) v = _root;	_hot = NULL;	//从根节点出发
	while (v) {	//逐层查找
		int r = VecSearch(v->key,e);	//在当前节点中，找到不大于e的最大关键码
		if ((0 <= r) && (e == v->key[r]))
			return v;	//成功：在当前节点中命中目标关键码

		_hot = v;	v = v->child[r + 1];	//否则，转入对应子树（_hot指向其父）----需做I/O，最费时间
	}//在同一节点内部的查找完全在内存中进行，在考虑各节点所含关键码数量通常在128~512之间，故可直接使用顺序查找

	return NULL;
}