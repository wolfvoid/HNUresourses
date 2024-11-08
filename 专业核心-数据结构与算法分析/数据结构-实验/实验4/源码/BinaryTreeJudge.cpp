//【问题描述】
// 基于实验三设计的ADT，对输入的两棵二叉树A和B，判断B是不是A的子树。
// 设T是一棵树，a是T中的一个顶点，由a以及a的所有后裔（后代）导出的子图称为树T的子树。
//【输入形式】
//每个输入文件的第一行为二叉树A的前序遍历顺序表示法（N≤30）。二叉树B的前序遍历顺序表示法。
//注意：用“#”代表空指针NULL。
//【输出形式】
//  yes 代表二叉树B就是二叉树A的一棵子树。
//  no  代表二叉树B不是二叉树A的一棵子树。 
//【样例输入1】
//    AB##C##
//    AB##C##
//【样例输出1】
//    yes
//【样例说明1】
//    二叉树B是二叉树A的一棵子树
//【样例输入2】
//	ABD##E##CGH###F##
//    CGH####
//【样例输出2】
//    no
//【样例说明2】
//    二叉树B不是二叉树A的一棵子树
//【样例输入3】
//    ABD##E##CGH###F##
//    CG##F##
//【样例输出3】
//    no
//【样例说明3】
//    二叉树B不是二叉树A的一棵子树
//【样例输入4】
//    ABD##E##CGH###F##
//    CGH###F##
//【样例输出4】
//    yes
//【样例说明4】
//	二叉树B是二叉树A的一棵子树


//解题思路：
//记输入的两个二叉树为分别为a1，a2
//记a2的根节点对应的值为h
//1）先创建二叉树的类来储存输入的元素
//2）a1中进行遍历查找h。
//3）在未查找到h，则输出‘no’并return
//4）若查到h则返回以h为根节点的二叉树记做e
//5）对a2和e分别进行先序遍历，并将遍历到的节点装入两个容器中，若遍历到的左节点或右节点为空则将‘#’装入容器
//（若不进行插“#”的操作，不能保证两个二叉树前序遍历相同则两个二叉树相同）
//6）对两个容器进行size的比较，
//若不同则输出“no”并返回
//若相同则对两个容器进行遍历逐个比较若有不同输出“no”并返回
//直到遍历完容器中所有元素，此时说明两个容器元素相同，即两个二叉树相同，也说明a2为a1的子树，输出“yes”并return
//原文链接：https://blog.csdn.net/qq_39682135/article/details/116210399 

#include <iostream>
#include"BinaryTree-realize.h"
#include"string"
#include<queue>
using namespace std;

int main()
{
	BinTree<string>* BT = new BinTree<string>;
	creatBinaryTree(BT);
	BinTree<string>* BT1 = new BinTree<string>;
	creatBinaryTree(BT1);
	BinNode<string>* tem = BT->find(BT->getRoot(), BT1->getRoot()->getValue());
	if (tem!=NULL)
	{
		
		if (compare(tem, BT1->getRoot()))

		{
			cout << "yes";
			return 0;
		}
	}
	else cout << "no";
	cout << "no";
	return 0;
}

