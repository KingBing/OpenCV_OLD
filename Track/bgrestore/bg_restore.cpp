//Function����˹��ϱ�����ģ��ǰ�����
//Source:http://blog.csdn.net/xiaowei_cqu/article/details/23689189
//Status:
//Improve:
//Info:[11/18/2014 jmy]



#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;


int bg_restore_main()
{
	VideoCapture video("bike.avi");
	Mat frame,mask,thresholdImage, output;
	int frameNum=0;
	video>>frame;
	BackgroundSubtractorMOG2 bgSubtractor(20,16,true); //������ģ

	while(true)
	{
		video>>frame;
		if (frame.empty())
		{
			cout<<"��Ƶ����\n"<<endl;
			return -1;
		}
		++frameNum;
		bgSubtractor(frame,mask,0.001); //maskΪǰ��
		bgSubtractor.getBackgroundImage(output);
		cout<<frameNum<<endl;
		imshow("ǰ��",mask);
		imshow("����",output);
		waitKey(10);
	}
	return 0;
}