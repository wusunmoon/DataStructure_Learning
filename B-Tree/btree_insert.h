#pragma once

#include"utilities.h"

template<typename T>
bool BTree<T>::insert(const T& e)	//将关键码e插入B-树中
{
	BTNodePosi(T) v = search(e);	if (v) return false;	//确认目标节点不存在
	int r = VecSearch(_hot->key, e);	//在节点_hot的有序关键码向量中查找合适的插入位置
	VecInsert(_hot->key, r + 1, e);	//将新关键码插至对应的位置
	VecInsert(_hot->child, r + 2, (BTNodePosi(T))NULL);	//创建一个空子树指针
	_size++;	//更新全树规模
	solveOverflow(_hot);	//如有必要，需做分裂
	return true;	//插入成功
}

