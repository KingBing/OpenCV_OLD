//Function�� OpenCV_��������Ӧ�������µ��˶�Ŀ����
//Source:http://blog.csdn.net/icvpr/article/details/8487271
//Status: �˶�����Mat���Ͱ汾
//Improve:
//Info:[11/25/2014 jmy]

#include <iostream>
#include <string>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	string videoFileName = "bike.avi";

	int threshold = 10;    // ��ֵ����ֵ
	float alpha = 0.003;     // �����ٶ� [0, 1]

	VideoCapture capture;
	capture.open(videoFileName);
	if (!capture.isOpened())
	{
		cout<<"cannot open video"<<endl;
		return -1;
	}

	Mat foregroundImg;
	Mat foregroundMat;

	Mat backgroundImg;
	Mat backgroundMat;

	Mat frame;
	Mat grayImg;
	Mat grayMat;

	while (capture.read(frame))
	{
		cvtColor(frame, grayImg, CV_BGR2GRAY);
		grayImg.convertTo(grayMat, CV_32FC1);

		//�Ե�һ֡�Ĵ���
		if (backgroundMat.empty())
		{
			grayImg.copyTo(backgroundImg);
			grayImg.convertTo(backgroundMat, CV_32FC1);		
		}

		// ��������
		absdiff(grayMat, backgroundMat, foregroundMat);
		
		// ����Ӧ��������
		addWeighted(backgroundMat, alpha, foregroundMat, 1-alpha, 0, backgroundMat);

		// ��ֵ������ȡǰ�����ص�
		cv::threshold(foregroundMat, foregroundMat, threshold, 255, CV_THRESH_BINARY);


		// Ϊ����ʾ�ã���CV_32FC1ת��ΪCV_8U
		convertScaleAbs(foregroundMat, foregroundImg);
		convertScaleAbs(backgroundMat, backgroundImg);

		imshow("frame", frame);
		imshow("foreground", foregroundImg);
		imshow("background", backgroundImg);

		if (waitKey(2) > 0)
		{
			break;
		}
	}

	return 0;
}