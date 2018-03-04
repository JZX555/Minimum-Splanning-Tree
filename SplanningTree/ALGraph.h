#ifndef ALGRAPH_H
#define ALGRAPH_H

#include <iostream>
#include <iomanip>
#include <queue>
#include "Disjoint_Set.h"
using namespace std;

// �ض���߽ڵ㣬���ڲ���
typedef struct ArcNode *Position;

/* �߽ڵ� 
 * ����Ԫ��:
 * AdjName:������ߵ�β���
 * Weight:������ߵ�Ȩ��
 * Next:������ߵ�ͷ�������������
 */
struct ArcNode {
	int AdjName;
	int Weight;
	Position Next;

};

/* �߽ڵ�:������KrusKal�㷨��
 * ����Ԫ��:
 * Vex1:������ߵĽڵ�
 * Vex2:������ߵ���һ���ڵ�
 * Weight:������ߵ�Ȩ��
 */
struct Edge {
	int Vex1;
	int Vex2;
	int Weight;

	// ���ء�<�����ţ�����KrusKal�㷨
	friend bool operator < (const Edge &a, const Edge &b) {
		return a.Weight > b.Weight;
	}
};

/* ����ڵ�
 * ����Ԫ��:
 * Name:�ö��������
 * FirstArc:�Ըö���Ϊͷ���ĵ�һ�������
 */
struct VexNode {
	int Name;
	Position FirstArc;
};

/* ��ڵ�
 * ����Ԫ��:
 * Known:�ýڵ��״̬
 * Dist:�ýڵ��ָ���ڵ�ľ���
 * Path:ָ��ýڵ�Ľڵ�
 */
struct TableNode {
	bool Known;
	int Dist;
	int Path;
};

/* ALGraph��
 * �ӿ�:
 * Display:չʾ���ܣ�չʾ������е���Ϣ
 * MakeEmpty:���ù��ܣ����ø�ͼ�е����б�
 * Creat:�������ܣ���ͼ�й�����
 * KrusKal:KrusKal�㷨����ͼ��Ѱ����С������
 * Prim:Prim�㷨����ͼ��Ѱ����С������
 */
class ALGraph
{
public:
	// ���캯��
	ALGraph(int = 10);
	// ��������
	~ALGraph();

//--------- �ӿں���------------

	// ��������
	void Display();
	void MakeEmpty();
	void Creat();

	// ��С����������
	void KrusKal();
	void Prim();

//-------------------------------

private:
	// ��������
	void InitTable();

	// ���ݳ�Ա
	int VexNum; // ���涥����
	int ArcNum; // �������
	VexNode *AdjList; // �����ڽӱ�
	TableNode *Table; // ��������
	priority_queue <Edge> H; // �������ȶ��У�����KrusKal�㷨��
};

#endif