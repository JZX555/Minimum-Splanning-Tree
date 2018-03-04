#include "stdafx.h"
#include "Disjoint_Set.h"


/* ���캯��:��ʼ������
 * ����ֵ:��
 * ����:nums:����������Ԫ�صĸ���
 */
Disjoint_Set::Disjoint_Set(int nums)
: NumSets(nums){
	DisjSet = new int[NumSets + 1]; // ���벻�ཻ��ɭ�ֵĴ洢�ռ�

	if (DisjSet == NULL)
		cout << "���ཻ������ʧ��!" << endl;

	// ��ʼ��ɭ���е�ÿ����
	else
		for (int i = NumSets; i > 0; i--)
			DisjSet[i] = 0;
}

/* ��������:��������ʱ���մ洢�ռ�
 * ����ֵ:��
 * ����:��
 */
Disjoint_Set::~Disjoint_Set()
{
	delete DisjSet;
	DisjSet = NULL;
}

/* ��������õķ�����
 * ���Ϻ���:��������������
 * ����ֵ:��
 * ����:Root1:��Ҫ�ϲ���һ�����ϣ�Root2:��Ҫ�ϲ�����һ������

void Disjoint_Set::SetUnion(SetType Root1, SetType Root2) {
	DisjSet[Root2] = Root1;
}
*/

/* ���Ϻ���:��������������
 * ����ֵ : ��
 * ���� : Root1 : ��Ҫ�ϲ���һ�����ϣ�Root2 : ��Ҫ�ϲ�����һ������
 */
void  Disjoint_Set::SetUnion(SetType Root1, SetType Root2) {
	// �ҵ���ӦԪ�����ڼ��ϵĸ���
	Root1 = Find(Root1);
	Root2 = Find(Root2);

	// case1:��Root2���ϸ߶ȴ���Root1ʱ
	if (DisjSet[Root2] < DisjSet[Root2])
		DisjSet[Root1] = Root2; // ��Root1�ϲ���Root2��

	else {
		// case2:��Root1���ϸ߶ȵ���Root2ʱ
		if (DisjSet[Root1] == DisjSet[Root2])
			DisjSet[Root1]--; // ����Root1�߶�
		
		// case3:��Root1���ϸ߶ȴ���Root2ʱ
		// ��Root2�ϲ���Root1��
		DisjSet[Root2] = Root1;
	}
}

/* ���Һ���:���Ҷ�ӦԪ�����ڵļ���
 * ����ֵ:SetTpye:��ӦԪ�����ڼ��ϵĸ�
 * ����:X:��Ҫ���ҵ�Ԫ��
 */
SetType Disjoint_Set::Find(int X) {
	// �ж��Ƿ��Ǹ���
	if (DisjSet[X] <= 0)
		return X;

	// ����Ѱ�Ҹ���
	// ͬʱ����·��ѹ��:
	// ����;��������ÿһ���ڵ�ĸ��ڵ㶼��Ϊ����
	// ע��:�˴��������¼���߶ȣ���Ȼ�߶Ȼ�ı䣬��������
	// ʹ�ù��Ƹ߶ȣ����Ϊ��--rank����
	else
		return DisjSet[X] = Find(DisjSet[X]);
}