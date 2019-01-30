#pragma once

#include"BinNode.h"

#include<utility>

template<typename T>
class RedBlack {
protected:
	int _size;	//规模
	BinNodePosi(T) _root;	//根节点
	BinNodePosi(T) _hot;	//"命中"节点的父亲
	void release(BinNodePosi(T) x);	//释放树中所有节点
	BinNodePosi(T) connect34(	//按照“3+4”结构，联结3个节点及四棵子树
		BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c,
		BinNodePosi(T) T0, BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3);
	BinNodePosi(T) rotateAt(BinNodePosi(T) x);	//对x及其父亲、祖父做统一旋转调整
	void solveDoubleRed(BinNodePosi(T) x);	//双红修正
	void solveDoubleBlack(BinNodePosi(T) r);	//双黑修正
	int updateHeight(BinNodePosi(T) x);	//更新节点x的高度
public:
	RedBlack():_size(0),_root(NULL){}	//构造函数
	~RedBlack() { release(_root); }	//析构函数
	int size() const { return _size; }	//规模
	bool empty() const { return !_root; }	//判空
	BinNodePosi(T)& search(const T& e);	//查找
	BinNodePosi(T) insert(const T& e);	//插入
	bool remove(const T& e);	//删除
};

template<typename T>
void RedBlack<T>::release(BinNodePosi(T) x)
{
	if (!x) return;	//递归基：空树
	release(x->lc);
	release(x->rc);
	delete x;
}

#include"connect34.h"
#include"rotateAt.h"
#include"search.h"
#include"updateHeight.h"
#include"solveDoubleRed.h"
#include"insert.h"
#include"remove.h"
#include"solveDoubleBlack.h"
