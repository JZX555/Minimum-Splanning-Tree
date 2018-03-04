#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#include <iostream>
#include <iomanip>
using namespace std;

// �ض�������������ڲ����������;
typedef int SetType;

/* Disjoint_Set�ࣨ���ཻ����
 * �ӿ�:
 * Find:���ҹ���:���Ҷ�ӦԪ������Ӧ�ļ���
 * SetUnion:���Ϲ���:����Ӧ����Ԫ�����ڵļ�������
 */
class Disjoint_Set
{
public:
	// ���캯��
	Disjoint_Set(int = 10);
	// ��������
	~Disjoint_Set();

	// �ӿں���
	SetType Find(int);
	void SetUnion(SetType, SetType);

private:
	int NumSets; // �����ܼ�����Ԫ�صĸ���
	int *DisjSet; // ����ȼ���ɭ��
};

#endif