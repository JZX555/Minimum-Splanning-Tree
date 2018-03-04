#include "stdafx.h"
#include "Disjoint_Set.h"


/* 构造函数:初始化对象
 * 返回值:无
 * 参数:nums:整个集合中元素的个数
 */
Disjoint_Set::Disjoint_Set(int nums)
: NumSets(nums){
	DisjSet = new int[NumSets + 1]; // 申请不相交集森林的存储空间

	if (DisjSet == NULL)
		cout << "不相交集申请失败!" << endl;

	// 初始化森林中的每棵树
	else
		for (int i = NumSets; i > 0; i--)
			DisjSet[i] = 0;
}

/* 析构函数:对象消亡时回收存储空间
 * 返回值:无
 * 参数:无
 */
Disjoint_Set::~Disjoint_Set()
{
	delete DisjSet;
	DisjSet = NULL;
}

/* （不是最好的方法）
 * 联合函数:将两个集合链接
 * 返回值:无
 * 参数:Root1:想要合并的一个集合；Root2:想要合并的另一个集合

void Disjoint_Set::SetUnion(SetType Root1, SetType Root2) {
	DisjSet[Root2] = Root1;
}
*/

/* 联合函数:将两个集合链接
 * 返回值 : 无
 * 参数 : Root1 : 想要合并的一个集合；Root2 : 想要合并的另一个集合
 */
void  Disjoint_Set::SetUnion(SetType Root1, SetType Root2) {
	// 找到对应元素所在集合的根部
	Root1 = Find(Root1);
	Root2 = Find(Root2);

	// case1:当Root2集合高度大于Root1时
	if (DisjSet[Root2] < DisjSet[Root2])
		DisjSet[Root1] = Root2; // 将Root1合并到Root2中

	else {
		// case2:当Root1集合高度等于Root2时
		if (DisjSet[Root1] == DisjSet[Root2])
			DisjSet[Root1]--; // 加深Root1高度
		
		// case3:当Root1集合高度大于Root2时
		// 将Root2合并到Root1上
		DisjSet[Root2] = Root1;
	}
}

/* 查找函数:查找对应元素所在的集合
 * 返回值:SetTpye:对应元素所在集合的根
 * 参数:X:想要查找的元素
 */
SetType Disjoint_Set::Find(int X) {
	// 判断是否是根部
	if (DisjSet[X] <= 0)
		return X;

	// 继续寻找根部
	// 同时进行路径压缩:
	// 将中途检索到的每一个节点的父节点都变为根；
	// 注意:此处不用重新计算高度！虽然高度会改变，但是我们
	// 使用估计高度（或称为秩--rank）；
	else
		return DisjSet[X] = Find(DisjSet[X]);
}