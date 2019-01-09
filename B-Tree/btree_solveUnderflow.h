#pragma once

#include"utilities.h"

template<typename T>	//关键码删除后若节点下溢，则做节点旋转或合并处理
void BTree<T>::solveUnderflow(BTNodePosi(T) v) 
{
	if ((_order + 1) / 2 <= v->child.size()) return;	//递归基：当前节点并未下溢
	BTNodePosi(T) p = v->parent;
	if (!p) {	//递归基：已到根节点，没有孩子的下限
		if (!v->key.size() && v->child[0]) {
			//但倘若作为树根的v已不含关键码，却有（唯一的）非空孩子，则
			_root = v->child[0];	_root->parent = NULL;	//这个节点可被跳过
			v->child[0] = NULL;	release(v);	//并因不再有用而被销毁
		}	//整树高度降低一层
		return;
	}
	int r = 0; while (p->child[r] != v)	r++;
	//确定v是p的第r个孩子----此时v可能不含关键码，故不能通过关键码查找
	
	//情况1：向左兄弟借关键码
	if (0 < r) {	//若v不是p的第一个孩子，则
		BTNodePosi(T) ls = p->child[r - 1];	//左兄弟必存在
		if ((_order + 1) / 2 < ls->child.size()) {	//若该兄弟足够“胖”，则
			VecInsert(v->key, 0, p->key[r - 1]);	//p借出一个关键码给v（作为最小关键码）
			p->key[r - 1] = VecRemove(ls->key, ls->key.size() - 1);	//ls的最大关键码转入p
			VecInsert(v->child, 0, VecRemove(ls->child, ls->child.size() - 1));	//同时ls的最右侧孩子过继给v
			if (v->child[0])
				v->child[0]->parent = v;	//作为v的最左侧孩子(当v为叶子节点时v->child[0]为NULL)
			return;	//至此，通过右旋已完成当前层（以及所有层）的下溢处理
		}
	}	//至此，左兄弟要么为空，要么太“瘦”

	//情况2：向右兄弟借关键码
	if (p->child.size() - 1 > r) {	//若v不是p的最后一个孩子，则
		BTNodePosi(T) rs = p->child[r + 1];	//右兄弟必存在
		if ((_order + 1) / 2 < rs->child.size()) {	//若该兄弟足够“胖”，则
			VecInsert(v->key, v->key.size(), p->key[r]);	//p借出一个关键码给v（作为最大关键码）
			p->key[r] = VecRemove(rs->key, 0);	//rs的最小关键码转入p
			VecInsert(v->child, v->child.size(), VecRemove(rs->child, 0));	//同时rs的最左侧孩子过继给v
			if (v->child[v->child.size() - 1])	//作为v的最右侧孩子
				v->child[v->child.size() - 1]->parent = v;
			return;	//至此，通过左旋已完成当前层（以及所有层）的下溢处理
		}
	}	//至此，右兄弟要么为空，要么太“瘦”

	//情况3：左、右兄弟要么为空（但不可能同时），要么都太“瘦”----合并
	if (0 < r) {	//与左兄弟合并
		BTNodePosi(T) ls = p->child[r - 1];	//左兄弟必存在
		VecInsert(ls->key, ls->key.size(), VecRemove(p->key, r - 1));
		VecRemove(p->child, r);	//p的第r-1个关键码转入ls，v不再是p的第r个孩子
		VecInsert(ls->child, ls->child.size(), VecRemove(v->child, 0));
		if (ls->child[ls->child.size() - 1])	//v的最左侧孩子过继给ls做最右侧孩子
			ls->child[ls->child.size() - 1]->parent = ls;
		while (!v->key.empty()) {	//v剩余的关键码和孩子，依次转入ls
			VecInsert(ls->key, ls->key.size(), VecRemove(v->key, 0));
			VecInsert(ls->child, ls->child.size(), VecRemove(v->child, 0));
			if (ls->child[ls->child.size() - 1])
				ls->child[ls->child.size() - 1]->parent = ls;
		}
		release(v);	//释放v
	}
	else {	//与右兄弟合并
		BTNodePosi(T) rs = p->child[r + 1];	//右兄弟必存在
		VecInsert(rs->key, 0, VecRemove(p->key, r));	VecRemove(p->child, r);
		//p的第r个关键码转入rs，v不再是p的第r个孩子
		VecInsert(rs->child, 0, VecRemove(v->child, v->child.size() - 1));
		if (rs->child[0])
			rs->child[0]->parent = rs;	//v的最右侧孩子过继给rs做最左侧孩子
		while (!v->key.empty()) {	//v剩余的关键码和孩子，依次转入rs
			VecInsert(rs->key, 0, VecRemove(v->key, v->key.size() - 1));
			VecInsert(rs->child, 0, VecRemove(v->child, v->child.size() - 1));
			if (rs->child[0])
				rs->child[0]->parent = rs;
		}
		release(v);	//释放v
	}
	solveUnderflow(p);	//上升一层，如有必要则继续分裂----至多递归O（logn）层
	return;
}
