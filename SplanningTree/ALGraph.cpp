#include "stdafx.h"
#include "ALGraph.h"

/* 构造函数:初始化对象
 * 返回值:无
 * 参数:vnum:图中的顶点数
 */
ALGraph::ALGraph(int vnum)
: VexNum(vnum), ArcNum(0){
	// 申请邻接表储存空间
	AdjList = new VexNode[VexNum + 1];
	// 申请距离表储存空间
	Table = new TableNode[VexNum + 1];

	// 判断是否申请成功
	if (AdjList == NULL || Table == NULL) {
		cout << "邻接表申请失败!" << endl;
		return;
	}

	// 初始化邻接表以及距离表
	for (int i = 0; i < VexNum + 1; i++) {
		AdjList[i].FirstArc = NULL;
		AdjList[i].Name = i;
		Table[i].Dist = INT_MAX;
		Table[i].Known = false;
		Table[i].Path = 0;
	}
}

/* 析构函数:对象消亡时回收储存空间
 * 返回值:无
 * 参数:无
 */
ALGraph::~ALGraph()
{
	// 重置所有的边
	MakeEmpty();

	// 删除邻接表
	delete AdjList;
	AdjList = NULL;
	
	// 删除距离表
	delete Table;
	Table = NULL;
}

/* 重置函数:重置所有的边
 * 返回值:无
 * 参数:无
 */
void ALGraph::MakeEmpty() {
	// 暂时储存中间节点
	Position P;

	// 遍历邻接表
	for (int i = 1; i < VexNum + 1; i++) {
		P = AdjList[i].FirstArc;

		// 遍历所有链接的边
		while (P != NULL) {
			AdjList[i].FirstArc = P->Next;
			delete P;
			P = AdjList[i].FirstArc;
		}
	}

	// 边数初始化
	ArcNum = 0;
}

/* 构建函数:在图中构建有向边
 * 返回值:无
 * 参数:无
 */
void ALGraph::Creat() {
	int tmp; // 储存边数
	cout << "请输入要创建的无向边数: ";
	cin >> tmp;
	ArcNum += tmp;

	// 创建所有的无向边
	for (int i = 0; i < tmp; i++) {
		// v:边的顶点
		// w:边的另一个顶点
		// weight:边的权重
		int v, w, weight;
		cout << "请输入要创建的无向边（v, w）: ";
		cin >> v >> w;
		cout << "请输入该无向边的权重: ";
		cin >> weight;

		// 构建一个单向边
		Position P1 = new ArcNode();
		P1->AdjName = w;
		P1->Weight = weight;
		P1->Next = AdjList[v].FirstArc;
		AdjList[v].FirstArc = P1;

		// 构建另一个单向边
		Position P2 = new ArcNode();
		P2->AdjName = v;
		P2->Weight = weight;
		P2->Next = AdjList[w].FirstArc;
		AdjList[w].FirstArc = P2;

		// 构建一个无向边（用于KrusKal算法）
		Edge E;
		E.Vex1 = v;
		E.Vex2 = w;
		E.Weight = weight;

		// 将该无向边压入优先队列
		H.push(E);
	}
}

/* 初始化函数:初始化距离表
 * 返回值:无
 * 参数:无
 */
void ALGraph::InitTable() {
	// 遍历所有的距离表
	for (int i = 0; i < VexNum + 1; i++) {
		// 初始化参数
		Table[i].Dist = INT_MAX;
		Table[i].Known = false;
		Table[i].Path = 0;
	}
}

/* 展示函数:展示距离表中的信息
 * 返回值:无
 * 参数:无
 */
void ALGraph::Display() {
	// 遍历所有的距离表
	for (int i = 1; i < VexNum + 1; i++) {
		cout << "节点: " << i << " ,   距离: " << Table[i].Dist << " ,   路径: " << Table[i].Path << endl;
	}
}

/* KrusKal算法:寻找最小生成树
 * 返回值:无
 * 参数:无
 */
void ALGraph::KrusKal() {
	// S:不相交集，用于判断两个顶点是否链接
	// v:一条无向边的顶点
	// w:一条无向边的另一个顶点
	// EdgeAccepted:已经生成的边数
	// V:顶点v所在的集合
	// W:顶点w所在的集合
	// E:无向边节点
	Disjoint_Set S(VexNum);
	int v, w, EdgeAccepted = 0;
	SetType V, W;
	Edge E;

	// 初始化距离表
	InitTable();

	// 一直寻找直到生成的边数为:VexNum - 1
	while (EdgeAccepted < VexNum - 1) {
		// 获取最小的无向边
		E = H.top();
		H.pop();

		// 获取无向边的顶点
		v = E.Vex1;
		w = E.Vex2;

		// 获取顶点所在的集合
		V = S.Find(v);
		W = S.Find(w);

		// 判断两个顶点是否在同一个集合
		if (V != W) {
			// 生成边数增加
			EdgeAccepted++;
			// 链接量顶点
			S.SetUnion(V, W);
			// 输出信息
			cout << "顶点1: " << E.Vex1 << " ,   顶点2: " << E.Vex2 << " ,   距离: " << E.Weight << endl;;
		}
	}
}

/* Prim算法:寻找最小生成树
 * 返回值:无
 * 参数:无
 */
void ALGraph::Prim() {
	// v:一条无向边的顶点
	// w:一条无向边的另一个顶点
	// counter:计数器，统计边数
	// P:储存边节点
	int v, w, counter;
	Position P;

	// 初始化距离表，并选取起始节点
	InitTable();
	v = 1;
	counter = 1;
	Table[v].Dist = 0;
	Table[v].Known = true;

	// 一直寻找，直到边数为:VexNum - 1
	while (counter != VexNum) {
		// 获取边节点
		P = AdjList[v].FirstArc;

		// 遍历完该节点所有无向边
		while (P != NULL) {
			w = P->AdjName;
			// 判断是否需要更新距离表信息
			if (Table[w].Known == false && Table[w].Dist > P->Weight) {
				Table[w].Dist = P->Weight;
				Table[w].Path = v;
			}
			// 指向下一个无向边
			P = P->Next;
		}

		// 寻找不构成圈的权重最小的无向边
		int Min = INT_MAX;
		for (int i = 1; i < VexNum + 1; i++) {
			if (Table[i].Known == false && Min > Table[i].Dist) {
				v = i;
				Min = Table[i].Dist;
			}
		}

		// 链接该无向边，计数器增加
		Table[v].Known = true;
		counter++;
	}
}