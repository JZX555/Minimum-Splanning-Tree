#ifndef ALGRAPH_H
#define ALGRAPH_H

#include <iostream>
#include <iomanip>
#include <queue>
#include "Disjoint_Set.h"
using namespace std;

// 重定义边节点，便于操作
typedef struct ArcNode *Position;

/* 边节点 
 * 储存元素:
 * AdjName:该有向边的尾结点
 * Weight:该有向边的权重
 * Next:该有向边的头结点的其他有向边
 */
struct ArcNode {
	int AdjName;
	int Weight;
	Position Next;

};

/* 边节点:（用于KrusKal算法）
 * 储存元素:
 * Vex1:该无向边的节点
 * Vex2:该无向边的另一个节点
 * Weight:该无向边的权重
 */
struct Edge {
	int Vex1;
	int Vex2;
	int Weight;

	// 重载“<”符号，用于KrusKal算法
	friend bool operator < (const Edge &a, const Edge &b) {
		return a.Weight > b.Weight;
	}
};

/* 顶点节点
 * 储存元素:
 * Name:该顶点的名称
 * FirstArc:以该顶点为头结点的第一个有向边
 */
struct VexNode {
	int Name;
	Position FirstArc;
};

/* 表节点
 * 储存元素:
 * Known:该节点的状态
 * Dist:该节点距指定节点的距离
 * Path:指向该节点的节点
 */
struct TableNode {
	bool Known;
	int Dist;
	int Path;
};

/* ALGraph类
 * 接口:
 * Display:展示功能，展示距离表中的信息
 * MakeEmpty:重置功能，重置该图中的所有边
 * Creat:构建功能，在图中构建边
 * KrusKal:KrusKal算法，在图中寻找最小生成树
 * Prim:Prim算法，在图中寻找最小生成树
 */
class ALGraph
{
public:
	// 构造函数
	ALGraph(int = 10);
	// 析构函数
	~ALGraph();

//--------- 接口函数------------

	// 基础函数
	void Display();
	void MakeEmpty();
	void Creat();

	// 最小生成树函数
	void KrusKal();
	void Prim();

//-------------------------------

private:
	// 辅助函数
	void InitTable();

	// 数据成员
	int VexNum; // 储存顶点数
	int ArcNum; // 储存边数
	VexNode *AdjList; // 储存邻接表
	TableNode *Table; // 储存距离表
	priority_queue <Edge> H; // 储存优先队列（用于KrusKal算法）
};

#endif