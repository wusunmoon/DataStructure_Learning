#pragma once

#define BinNodePosi(T) BinNode<T>*	//节点位置
#define stature(p) ((p)?(p)->height:-1)	//节点高度（与“空树高度为-1”的约定相统一）
typedef enum{RB_RED,RB_BLACK} RBColor;	//节点颜色
/*************************************************************************************
*BinNode状态与性质的判断
**************************************************************************************/
#define IsRoot(x) (!((x).parent))
#define IsLChild(x) (!IsRoot(x) && (&(x)==(x).parent->lc))
#define IsRChild(x) (!IsRoot(x) && (&(x)==(x).parent->rc))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lc)
#define HasRChild(x) ((x).rc)
#define HasChild(x) (HasLChild(x) || HasRChild(x))	//至少拥有一个孩子
#define HasBothChild(x) (HasLChild(x) && HasRChild(x))	//同时拥有两个孩子
#define IsLeaf(x) (!HasChild(x))
/************************************************************************************
*与BinNode具有特定关系的节点及指针
*************************************************************************************/
#define sibling(p) (IsLChild(*(p))?(p)->parent->rc:(p)->parent->lc)	//兄弟
#define uncle(x) sibling((x)->parent)	//叔叔
#define FromParentTo(x) /*来自父亲的引用*/\
	(IsRoot(x)?_root:(IsLChild(x)?(x).parent->lc:(x).parent->rc))

#define IsBlack(p) (!(p) || (RB_BLACK == (p)->color))	//外部节点也视作黑节点
#define IsRed(p) (!IsBlack(p))	//非黑即红
#define BlackHeightUpdated(x) (/*RedBlack高度更新条件*/ \
	(stature((x).lc)==stature((x).rc)) && \
	((x).height == (IsRed(&x)?stature((x).lc):stature((x).lc)+1)) \
)

template<typename T>
struct BinNode {	//二叉树节点模板类
	//成员
	T data;	//数值
	BinNodePosi(T) parent;	//父节点
	BinNodePosi(T) lc;	//左孩子
	BinNodePosi(T) rc;	//右孩子
	int height;	//高度
	RBColor color;	//颜色
	//构造函数
	BinNode() :parent(NULL),lc(NULL),rc(NULL),height(0),color(RB_RED){}
	BinNode(T e,BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL,
			int h = 0, RBColor c = RB_RED):
		data(e),parent(p),lc(lc),rc(rc),height(h),color(c){}
	//操作接口
	int size();	//统计当前节点后代总数，亦即以其为根的子树的规模
	BinNodePosi(T) succ();	//取当前节点的直接后继

	//比较器、判等器
	bool operator<(const BinNode& bn) { return data < bn.data; }	//小于
	bool operator==(const BinNode& bn) { return data == bn.data; }	//等于
	bool operator!=(const BinNode& bn) { return data != bn.data; }	//不等于
};

template<typename T>
int BinNode<T>::size()	//统计当前节点后代总数，即以其为根的子树规模
{
	int s = 1;	//计入本身
	if (lc) s += lc->size();	//计入左子树规模
	if (rc) s += rc->size();	//计入右子树规模
	return s;
}

template<typename T>
BinNodePosi(T) BinNode<T>::succ()	//定位节点v的直接后继
{
	BinNodePosi(T) s = this;	//记录后继的临时变量
	if (rc) {	//若有右孩子，则直接后继必在右子树中，具体地就是
		s = rc;	//右子树中
		while (HasLChild(*s))
			s = s->lc;	//最靠左（最小）的节点
	}else{	//否则，直接后继应是“将当前节点包含于其左子树中的最低祖先”，具体地就是
		while (IsRChild(*s))
			s = s->parent;	//逆向地沿右向分支，不断朝左上方移动
		s = s->parent;
	}
	return s;
}