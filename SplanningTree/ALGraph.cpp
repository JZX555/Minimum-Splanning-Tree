#include "stdafx.h"
#include "ALGraph.h"

/* ���캯��:��ʼ������
 * ����ֵ:��
 * ����:vnum:ͼ�еĶ�����
 */
ALGraph::ALGraph(int vnum)
: VexNum(vnum), ArcNum(0){
	// �����ڽӱ���ռ�
	AdjList = new VexNode[VexNum + 1];
	// ����������ռ�
	Table = new TableNode[VexNum + 1];

	// �ж��Ƿ�����ɹ�
	if (AdjList == NULL || Table == NULL) {
		cout << "�ڽӱ�����ʧ��!" << endl;
		return;
	}

	// ��ʼ���ڽӱ��Լ������
	for (int i = 0; i < VexNum + 1; i++) {
		AdjList[i].FirstArc = NULL;
		AdjList[i].Name = i;
		Table[i].Dist = INT_MAX;
		Table[i].Known = false;
		Table[i].Path = 0;
	}
}

/* ��������:��������ʱ���մ���ռ�
 * ����ֵ:��
 * ����:��
 */
ALGraph::~ALGraph()
{
	// �������еı�
	MakeEmpty();

	// ɾ���ڽӱ�
	delete AdjList;
	AdjList = NULL;
	
	// ɾ�������
	delete Table;
	Table = NULL;
}

/* ���ú���:�������еı�
 * ����ֵ:��
 * ����:��
 */
void ALGraph::MakeEmpty() {
	// ��ʱ�����м�ڵ�
	Position P;

	// �����ڽӱ�
	for (int i = 1; i < VexNum + 1; i++) {
		P = AdjList[i].FirstArc;

		// �����������ӵı�
		while (P != NULL) {
			AdjList[i].FirstArc = P->Next;
			delete P;
			P = AdjList[i].FirstArc;
		}
	}

	// ������ʼ��
	ArcNum = 0;
}

/* ��������:��ͼ�й��������
 * ����ֵ:��
 * ����:��
 */
void ALGraph::Creat() {
	int tmp; // �������
	cout << "������Ҫ�������������: ";
	cin >> tmp;
	ArcNum += tmp;

	// �������е������
	for (int i = 0; i < tmp; i++) {
		// v:�ߵĶ���
		// w:�ߵ���һ������
		// weight:�ߵ�Ȩ��
		int v, w, weight;
		cout << "������Ҫ����������ߣ�v, w��: ";
		cin >> v >> w;
		cout << "�����������ߵ�Ȩ��: ";
		cin >> weight;

		// ����һ�������
		Position P1 = new ArcNode();
		P1->AdjName = w;
		P1->Weight = weight;
		P1->Next = AdjList[v].FirstArc;
		AdjList[v].FirstArc = P1;

		// ������һ�������
		Position P2 = new ArcNode();
		P2->AdjName = v;
		P2->Weight = weight;
		P2->Next = AdjList[w].FirstArc;
		AdjList[w].FirstArc = P2;

		// ����һ������ߣ�����KrusKal�㷨��
		Edge E;
		E.Vex1 = v;
		E.Vex2 = w;
		E.Weight = weight;

		// ���������ѹ�����ȶ���
		H.push(E);
	}
}

/* ��ʼ������:��ʼ�������
 * ����ֵ:��
 * ����:��
 */
void ALGraph::InitTable() {
	// �������еľ����
	for (int i = 0; i < VexNum + 1; i++) {
		// ��ʼ������
		Table[i].Dist = INT_MAX;
		Table[i].Known = false;
		Table[i].Path = 0;
	}
}

/* չʾ����:չʾ������е���Ϣ
 * ����ֵ:��
 * ����:��
 */
void ALGraph::Display() {
	// �������еľ����
	for (int i = 1; i < VexNum + 1; i++) {
		cout << "�ڵ�: " << i << " ,   ����: " << Table[i].Dist << " ,   ·��: " << Table[i].Path << endl;
	}
}

/* KrusKal�㷨:Ѱ����С������
 * ����ֵ:��
 * ����:��
 */
void ALGraph::KrusKal() {
	// S:���ཻ���������ж����������Ƿ�����
	// v:һ������ߵĶ���
	// w:һ������ߵ���һ������
	// EdgeAccepted:�Ѿ����ɵı���
	// V:����v���ڵļ���
	// W:����w���ڵļ���
	// E:����߽ڵ�
	Disjoint_Set S(VexNum);
	int v, w, EdgeAccepted = 0;
	SetType V, W;
	Edge E;

	// ��ʼ�������
	InitTable();

	// һֱѰ��ֱ�����ɵı���Ϊ:VexNum - 1
	while (EdgeAccepted < VexNum - 1) {
		// ��ȡ��С�������
		E = H.top();
		H.pop();

		// ��ȡ����ߵĶ���
		v = E.Vex1;
		w = E.Vex2;

		// ��ȡ�������ڵļ���
		V = S.Find(v);
		W = S.Find(w);

		// �ж����������Ƿ���ͬһ������
		if (V != W) {
			// ���ɱ�������
			EdgeAccepted++;
			// ����������
			S.SetUnion(V, W);
			// �����Ϣ
			cout << "����1: " << E.Vex1 << " ,   ����2: " << E.Vex2 << " ,   ����: " << E.Weight << endl;;
		}
	}
}

/* Prim�㷨:Ѱ����С������
 * ����ֵ:��
 * ����:��
 */
void ALGraph::Prim() {
	// v:һ������ߵĶ���
	// w:һ������ߵ���һ������
	// counter:��������ͳ�Ʊ���
	// P:����߽ڵ�
	int v, w, counter;
	Position P;

	// ��ʼ���������ѡȡ��ʼ�ڵ�
	InitTable();
	v = 1;
	counter = 1;
	Table[v].Dist = 0;
	Table[v].Known = true;

	// һֱѰ�ң�ֱ������Ϊ:VexNum - 1
	while (counter != VexNum) {
		// ��ȡ�߽ڵ�
		P = AdjList[v].FirstArc;

		// ������ýڵ����������
		while (P != NULL) {
			w = P->AdjName;
			// �ж��Ƿ���Ҫ���¾������Ϣ
			if (Table[w].Known == false && Table[w].Dist > P->Weight) {
				Table[w].Dist = P->Weight;
				Table[w].Path = v;
			}
			// ָ����һ�������
			P = P->Next;
		}

		// Ѱ�Ҳ�����Ȧ��Ȩ����С�������
		int Min = INT_MAX;
		for (int i = 1; i < VexNum + 1; i++) {
			if (Table[i].Known == false && Min > Table[i].Dist) {
				v = i;
				Min = Table[i].Dist;
			}
		}

		// ���Ӹ�����ߣ�����������
		Table[v].Known = true;
		counter++;
	}
}