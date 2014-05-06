#include "harris_corner_detect.h"

using namespace cv;


int harris_corner_dete(char*filename)
{
	cv::Mat  image, image1 = cv::imread (filename);
	//�Ҷȱ任
	cv::cvtColor (image1,image,CV_BGR2GRAY);

	// �����harris�ǵ㷽��
	harris Harris;
	// ����ǵ�
	Harris.detect(image);
	//��ýǵ�
	std::vector<cv::Point> pts;
	Harris.getCorners(pts,0.01);
	// ��ǽǵ�
	Harris.drawOnImage(image1,pts);

	cv::namedWindow ("harris");
	cv::imshow ("harris",image1);
	cv::waitKey (0);
	return 0;

}

//��ʵ����opencv��ʹ�õ�harris�ǵ���
int harris_corner_dete_improve(char*filename)
{
	cv::Mat  grayimage, srcimage = cv::imread (filename);  
	//�Ҷȱ任  
	cv::cvtColor (srcimage,grayimage,CV_BGR2GRAY);  
	// �Ľ���harris�ǵ��ⷽ��  
	std::vector<cv::Point> corners;  
	cv::goodFeaturesToTrack(grayimage,corners,  
		200,  //�ǵ������Ŀ  
		0.01,  // �����ȼ���������0.01*max��min��e1��e2������e1��e2��harris���������ֵ  
		1  // �����ǵ�֮��ľ������̶�
		);  
	  
	harris().drawOnImage(srcimage,corners);//��ǽǵ� 

	imwrite("harris_improve.jpg",srcimage);

	/*namedWindow("FastCornerImprove",1);
	imshow("FastCornerImprove",srcimage);*/

	return 0;
}


