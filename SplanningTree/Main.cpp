 // 最小生成树.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "ALGraph.h"


int main()
{
	ALGraph A(7);
	A.Creat();
	A.KrusKal();

	A.Prim();
	A.Display();

    return 0;
}

