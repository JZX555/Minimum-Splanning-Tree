#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#include <iostream>
#include <iomanip>
using namespace std;

// 重定义变量名，便于操作与辨认用途
typedef int SetType;

/* Disjoint_Set类（不相交集）
 * 接口:
 * Find:查找功能:查找对应元素所对应的集合
 * SetUnion:联合功能:将对应两个元素所在的集合链接
 */
class Disjoint_Set
{
public:
	// 构造函数
	Disjoint_Set(int = 10);
	// 析构函数
	~Disjoint_Set();

	// 接口函数
	SetType Find(int);
	void SetUnion(SetType, SetType);

private:
	int NumSets; // 储存总集合中元素的个数
	int *DisjSet; // 储存等价类森林
};

#endif