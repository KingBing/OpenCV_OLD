#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int diff_mat_main()
{
	VideoCapture cap("bike.avi");
	Mat frame,gray;
	for (;;)
	{
		cap>>frame;
		cvtColor(frame,gray,CV_BGR2GRAY);
		Mat bg(gray),fr,bin; //������ǰ��
		absdiff(gray,bg,fr);//��ǰ֡�������õ�ǰ��
		accumulateWeighted(gray,bg,0.03);//���±���
		threshold(fr,bin,50,255,THRESH_BINARY);//ֵ��ǰ��������ͳ�ƣ����仯��������ʶ��
		imshow("Bin",bin);
	}
	

}

