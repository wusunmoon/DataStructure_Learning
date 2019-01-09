#pragma once

/******************************************************************************************
* 将BTree各方法的实现部分，简洁地引入BTree.h
* 效果等同于将这些实现直接汇入BTree.h
* 在export尚未被编译器支持前，如此可将定义与实现分离
******************************************************************************************/
#include"btree_solveOverflow.h"
#include"btree_solveUnderflow.h"
#include"btree_search.h"
#include"btree_insert.h"
#include"btree_remove.h"