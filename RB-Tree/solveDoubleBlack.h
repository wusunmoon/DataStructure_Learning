#pragma once
/****************************************************************************************
*RedBlack双黑调整算法：解决节点x与被其替代的节点均为黑色的问题
*分为三大类共四种情况：
*	BB-1	:2次颜色翻转，2次黑高度更新，1-2次旋转，不再递归
*	BB-2R	:2次颜色翻转，2次黑高度更新，0次旋转，不在递归
*	BB-2B	:1次颜色翻转，1次黑高度更新，0次旋转，需要递归
*	BB-3	:2次颜色翻转，2次黑高度更新，1次旋转，转为BB-1或BB-2R
****************************************************************************************/
template<typename T>
void RedBlack<T>::solveDoubleBlack(BinNodePosi(T) r)
{
	BinNodePosi(T) p = r ? r->parent : _hot;	if (!p) return;	//r的父亲
	BinNodePosi(T) s = (r == p->lc) ? p->rc : p->lc;	//r的兄弟
	if (IsBlack(s)) {	//兄弟s为黑
		BinNodePosi(T) t = NULL;	//s的红孩子（若左、右孩子皆红，左者优先；皆黑时为NULL）
		if (IsRed(s->rc))	t = s->rc;	//右子
		if (IsRed(s->lc))	t = s->lc;	//左子
		if (t) {	//黑s有红孩子：BB-1
			RBColor oldColor = p->color;	//备份原子数根节点p颜色，并对t及其父亲、祖父
											//以下，通过旋转重平衡，并将新子树的左、右孩子染黑
			BinNodePosi(T) b = FromParentTo(*p) = rotateAt(t);	//旋转
			if (HasLChild(*b)) {
				b->lc->color = RB_BLACK;
				updateHeight(b->lc);
			}	//左子
			if (HasRChild(*b)) {
				b->rc->color = RB_BLACK;
				updateHeight(b->rc);
			}	//右子
			b->color = oldColor;
			updateHeight(b);	//新子树根节点继承原根节点的颜色
		}
		else {	//黑s无红孩子
			s->color = RB_RED;	//s转红
			s->height--;
			if (IsRed(p)) {	//BB-2R
				p->color = RB_BLACK;	//p转黑，但黑高度不变
			}
			else {
				p->height--;	//p保持黑，但黑高度下降
				solveDoubleBlack(p);	//递归上溯
			}
		}
	}
	else {	//兄弟s为红：BB-3
		s->color = RB_BLACK;	//s转黑
		p->color = RB_RED;	//p转红
		BinNodePosi(T) t = IsLChild(*s) ? s->lc : s->rc;	//取t与其父s同侧
		_hot = p;
		FromParentTo(*p) = rotateAt(t);	//对t及其父亲、祖父做平衡调整
		solveDoubleBlack(r);	//继续修正r处双黑----此时的p已转红，故后续只能是BB-1或BB-2R
	}
}
