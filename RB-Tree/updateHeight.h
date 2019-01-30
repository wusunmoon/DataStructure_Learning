#pragma once

#include<algorithm>

template<typename T>
int RedBlack<T>::updateHeight(BinNodePosi(T) x)	//更新节点高度
{
	x->height = std::max(stature(x->lc), stature(x->rc));	//孩子一般黑高度相等，除非出现双黑
	return IsBlack(x) ? x->height++ : x->height;	//若当前节点为黑，则计入黑高度
}	//因统一定义stature(NULL) = -1,故height比黑高度少一，好在不致影响到各种算法中的比较判断

