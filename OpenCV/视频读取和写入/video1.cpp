//Function��������Ϊ����Ƶ֡�б��֡�����ڵ�һ֡���ȡ��Ĺ����Բ��Գ���
//Source:http://www.cnblogs.com/wsc36305/archive/2012/10/08/2715854.html
//Status:
//Improve:
//Info:[11/16/2014 jmy]


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace cv;
using namespace std;

Rect box; 
bool drawing_box = false;
bool gotBB = false;    

void draw_framecount(Mat Frame,int framecount); 
//void mouseHandler(int event, int x, int y, int flags, void *param);

int main()
{
	void mouseHandler(int event, int x, int y, int flags, void *param);
	namedWindow("text",CV_WINDOW_AUTOSIZE);
	
	//ע�ᴰ������¼�
	cvSetMouseCallback("text",mouseHandler,NULL);
	
	Mat img;
	VideoCapture cap("PicVideo/video/test_o2.mp4");

	long count=0;
	for(;;)
	{   
		Mat frame;
		cap>>frame;
		
		rectangle(frame,box,Scalar(0,0,255));//����һ֡���Ի�����֡��ѡ��
		draw_framecount(frame,count);  //����֡��
		
		//����Ƶ�г��־��ο��ʱ�򣬻��ƾ��ο�
		if(gotBB)
		{
			rectangle(frame,box,Scalar(0,0,255));  //���ƾ��ο�ѡ
			//imshow("text",frame);
			//waitKey(100);
			//������Ӧ����ͣһ�£������¿ո����ʱ���ٴο�ʼ
// 			char c=cvWaitKey();
// 			if (c==' ')
// 			{
// 				//������һ֡
// 			}
		}

		imshow("text",frame);
		count++;
		//waitKey(100);

	}
	
	//�ͷ�����¼�
	setMouseCallback("text", NULL, NULL);

}

//��ǵ�ǰ֡��֡��
void draw_framecount(Mat Frame,int framecount)//FrameΪ�������ĵ�ǰ֡��framecountΪ��ǰ֡��
{
	char strFrame[10];
	sprintf(strFrame, "#%0d ",framecount);
	putText(Frame,strFrame,cvPoint(0,20),1,1,CV_RGB(25,200,25));
}

//����¼��Ļص��������壬��������Ƶ֡�н�ȡһ�����Σ������ڸ���,�ص�������һ���ɵ��÷��Լ�ʵ�֣��������÷�ʹ�õ����⺯��
//����event �� CV_EVENT_* ����֮һ�� x ��y �����ָ����ͼ������ϵ�����꣨���Ǵ�������ϵ���� 
//flags ��CV_EVENT_FLAG ����ϣ� param ���û�����Ĵ��ݵ�cvSetMouseCallback �������õĲ�����
void mouseHandler(int event, int x, int y, int flags, void *param)	
{
	switch (event)
	{
	case CV_EVENT_MOUSEMOVE:
		if (drawing_box)
		{
			box.width = x - box.x;
			box.height = y - box.y;
		}
		break;
	case CV_EVENT_LBUTTONDOWN:
		drawing_box = true;
		box = Rect(x, y, 0, 0);
		break;
	case CV_EVENT_LBUTTONUP:
		drawing_box = false;
		if (box.width < 0)
		{
			box.x += box.width;
			box.width *= -1;
		}
		if( box.height < 0 )
		{
			box.y += box.height;
			box.height *= -1;
		}
		gotBB = true;
		break;
	default:
		break;
	}
}