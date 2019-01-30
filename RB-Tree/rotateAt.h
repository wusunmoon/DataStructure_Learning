#pragma once

/****************************************************************************************
**节点旋转变换统一算法（3节点+4子树），返回调整之后局部子树根节点的位置
**注意：尽管子树根会正确指向上层节点（如果存在），但反向的连接须由上层函数完成
*****************************************************************************************/
template<typename T>
BinNodePosi(T) RedBlack<T>::rotateAt(BinNodePosi(T) v)	//v为非空孙辈节点
{
	BinNodePosi(T) p = v->parent;
	BinNodePosi(T) g = p->parent;
	if (IsLChild(*p))	/*zig*/
		if (IsLChild(*v)) {	/*zig-zig*/
			p->parent = g->parent;	//向上联接
			return connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);
		}
		else {
			v->parent = g->parent;	//向上连接
			return connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
		}
	else
		if (IsRChild(*v)) {
			p->parent = g->parent;	//向上连接
			return connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
		}
		else {
			v->parent = g->parent;	//向上连接
			return connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
		}
}
