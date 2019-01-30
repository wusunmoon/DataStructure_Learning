#pragma once

/*************************************************************************************************
**删除位置x所指的节点
**目标x在此前经查找定位，并确认非NULL，故必删除成功
**返回值指向实际被删除节点的接替者，hot指向实际被删除节点的父亲----二者均有可能是NULL
**************************************************************************************************/
template<typename T>
static BinNodePosi(T) removeAt(BinNodePosi(T)& x, BinNodePosi(T)& hot)
{
	BinNodePosi(T) w = x;	//实际被摘除的节点，初值同x
	BinNodePosi(T) succ = NULL;	//实际被删除节点的接替者
	if (!HasLChild(*x))	//若*x的左子树为空，则可
		succ = x = x->rc;	//直接将*x替换为其右子树
	else if (!HasRChild(*x))	//若右子树为空，则可
		succ = x = x->lc;	//对称地处理----注意：此时succ ！= NULL
	else {	//若左右子树均存在，则选择x的直接后继作为实际被摘除节点，为此需要
		w = w->succ();	//(在右子树中)找到*x的直接后继*w
		std::swap(x->data, w->data);	//交换*x和*w数据元素
		BinNodePosi(T) u = w->parent;
		((u == x) ? u->rc : u->lc) = succ = w->rc;	//隔离节点*w
	}
	hot = w->parent;	//记录实际被删除节点的父亲
	if (succ) succ->parent = hot;	//并将被删除节点的接替者与hot相连
	delete w;	//释放被摘除节点
	return succ;	//返回接替者
}
template<typename T>
bool RedBlack<T>::remove(const T& e)	//从红黑树中删除关键码e
{
	BinNodePosi(T)& x = search(e);	if (!x) return false;
	BinNodePosi(T) r = removeAt(x, _hot); if (!(--_size)) return true;	//实施删除
//assert:_hot某一孩子刚被删除，且被r所指节点（可能是NULL）接替。以下检查是否失衡，并做必要调整
	if (!_hot) {	//若刚被删除的是根节点，则将其置黑，并更新黑高度
		_root->color = RB_BLACK;
		updateHeight(_root);
		return true;
	}
	//assert:以下，原x（现r）必非根，_hot必非空
	if (BlackHeightUpdated(*_hot))	return true;	//若所有祖先的黑深度依然平衡，则无需调整
	if (IsRed(r)) {	//否则，若r为红，则只需令其转黑
		r->color = RB_BLACK;
		r->height++;
		return true;
	}
	//assert:以下，原x（现r）均为黑色
	solveDoubleBlack(r);
	return true;	//经双黑调整后返回
}	//若目标节点存在且被删除，返回true；否则返回false
