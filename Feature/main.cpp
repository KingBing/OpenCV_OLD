//特征提取函数的主入口
#include <stdio.h>
#include "Feature.h"


int main()
{
	char*filename="samples/box.png";
	//garbor(filename);
	//-----------------------------------【角点检测和匹配】-----------------------------
	//surf_feature();
	//sift_feature();
	//surf_feature_opencv();
	//-----------------------------------【角点检测】-----------------------------
	//harris_corner_detect(filename);
	//susan_corner_detect(filename);
	fast_corner_detect(filename);

	getchar();
	return 0;
}