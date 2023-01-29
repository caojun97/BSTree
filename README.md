# BSTree

## 一、简介

数据结构之二叉树，该项目主要用来二叉树的使用，包括**二叉树的定义、创建结点、插入结点、查找最大key值的结点、查找最小key值的结点、查找指定key值的结点、删除结点、销毁二叉树、前序遍历、中序遍历、后续遍历、查找指定key值结点的前驱结点和后继结点**

项目地址：`https://github.com/caojun97/BSTree`

## 二、功能介绍

### 2-1 二叉树的定义

二叉树（Binary Tree）是 n（n >= 0）个结点所构成的集合，它可以是空树（n=0）; 也可以是非空树，对于非空树T：

​	1）**有且仅有**一个称之为根的结点

​	2）除根结点以外的其余结点分为两个互不相交的子集 T1 和 T2 ，分别称之为T的左子树和右子树，且 T1 和 T2 本身又都是二叉树

转换成C语言格式：

```c
typedef struct BSTreeNode
{
	int    key;                 // 关键字(键值)
	struct BSTreeNode *left;    // 左孩子
	struct BSTreeNode *right;   // 右孩子
	struct BSTreeNode *parent;  // 父结点
}Node, *BSTree;
```





