//������ȡ�����������
#include <stdio.h>
#include "Feature.h"


int main()
{
	char*filename="samples/box.png";
	//garbor(filename);
	//-----------------------------------���ǵ����ƥ�䡿-----------------------------
	//surf_feature();
	//sift_feature();
	//surf_feature_opencv();
	//-----------------------------------���ǵ��⡿-----------------------------
	//harris_corner_detect(filename);
	//susan_corner_detect(filename);
	fast_corner_detect(filename);

	getchar();
	return 0;
}