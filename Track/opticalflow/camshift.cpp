/*
 *���ܣ�camshift��ѡ����Ŀ�����
 *���ԣ�http://www.cnblogs.com/tornadomeet/archive/2012/03/15/2398769.html
 *Info:[11/10/2014 jmy]
 */

//���Բ��Ե�������Ƶ���в���

#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"


#include <iostream>
#include <ctype.h>

using namespace cv;
using namespace std;

Mat image;

bool backprojMode = false; //��ʾ�Ƿ�Ҫ���뷴��ͶӰģʽ��ture��ʾ׼�����뷴��ͶӰģʽ
bool selectObject = false;//�����Ƿ���ѡҪ���ٵĳ�ʼĿ�꣬true��ʾ���������ѡ��
int trackObject = 0; //�������Ŀ����Ŀ
bool showHist = true;//�Ƿ���ʾֱ��ͼ
Point origin;//���ڱ������ѡ���һ�ε���ʱ���λ��
Rect selection;//���ڱ������ѡ��ľ��ο�
int vmin = 10, vmax = 256, smin = 30;

void onMouse( int event, int x, int y, int, void* )
{
	if( selectObject )//ֻ�е�����������ȥʱ����Ч��Ȼ��ͨ��if�������Ϳ���ȷ����ѡ��ľ�������selection��
	{
		selection.x = MIN(x, origin.x);//�������ϽǶ�������
		selection.y = MIN(y, origin.y);
		selection.width = std::abs(x - origin.x);//���ο�
		selection.height = std::abs(y - origin.y);//���θ�

		selection &= Rect(0, 0, image.cols, image.rows);//����ȷ����ѡ�ľ���������ͼƬ��Χ��
	}

	switch( event )
	{
	case CV_EVENT_LBUTTONDOWN:
		origin = Point(x,y);
		selection = Rect(x,y,0,0);//���հ���ȥʱ��ʼ����һ����������
		selectObject = true;
		break;
	case CV_EVENT_LBUTTONUP:
		selectObject = false;
		if( selection.width > 0 && selection.height > 0 )
			trackObject = -1;
		break;
	}
}

void help()
{
	cout << "\nThis is a demo that shows mean-shift based tracking\n"
		"You select a color objects such as your face and it tracks it.\n"
		"This reads from video camera (0 by default, or the camera number the user enters\n"
		"Usage: \n"
		"    ./camshiftdemo [camera number]\n";

	cout << "\n\nHot keys: \n"
		"\tESC - quit the program\n"
		"\tc - stop the tracking\n"
		"\tb - switch to/from backprojection view\n"
		"\th - show/hide object histogram\n"
		"\tp - pause video\n"
		"To initialize tracking, select the object with mouse\n";
}

const char* keys = 
{
	"{1|  | 0 | camera number}"
};

int camshift_main( int argc, const char** argv )
{
	help();

	VideoCapture cap; //����һ������ͷ��׽�������
	Rect trackWindow;
	RotatedRect trackBox;//����һ����ת�ľ��������
	int hsize = 16;
	float hranges[] = {0,180};//hranges�ں���ļ���ֱ��ͼ������Ҫ�õ�
	const float* phranges = hranges;
	CommandLineParser parser(argc, argv, keys);//�������������
	int camNum = parser.get<int>("1");     

	cap.open(camNum);//ֱ�ӵ��ó�Ա����������ͷ

	if( !cap.isOpened() )
	{
		help();
		cout << "***Could not initialize capturing...***\n";
		cout << "Current parameter's value: \n";
		parser.printParams();
		return -1;
	}

	namedWindow( "Histogram", 0 );
	namedWindow( "CamShift Demo", 0 );
	setMouseCallback( "CamShift Demo", onMouse, 0 );//��Ϣ��Ӧ����
	createTrackbar( "Vmin", "CamShift Demo", &vmin, 256, 0 );//createTrackbar�����Ĺ������ڶ�Ӧ�Ĵ��ڴ�����������������Vmin,vmin��ʾ��������ֵ�����Ϊ256
	createTrackbar( "Vmax", "CamShift Demo", &vmax, 256, 0 );//���һ������Ϊ0����û�е��û����϶�����Ӧ����
	createTrackbar( "Smin", "CamShift Demo", &smin, 256, 0 );//vmin,vmax,smin��ʼֵ�ֱ�Ϊ10,256,30

	Mat frame, hsv, hue, mask, hist, histimg = Mat::zeros(200, 320, CV_8UC3), backproj;
	bool paused = false;

	for(;;)
	{
		if( !paused )//û����ͣ
		{
			cap >> frame;//������ͷץȡһ֡ͼ�������frame��
			if( frame.empty() )
				break;
		}

		frame.copyTo(image);

		if( !paused )//û�а���ͣ��
		{
			cvtColor(image, hsv, CV_BGR2HSV);//��rgb����ͷ֡ת����hsv�ռ��

			if( trackObject )//trackObject��ʼ��Ϊ0,���߰�����̵�'c'����ҲΪ0������굥���ɿ���Ϊ-1
			{
				int _vmin = vmin, _vmax = vmax;

				//inRange�����Ĺ����Ǽ����������ÿ��Ԫ�ش�С�Ƿ���2��������ֵ֮�䣬�����ж�ͨ��,mask����0ͨ������Сֵ��Ҳ����h����
				//����������hsv��3��ͨ�����Ƚ�h,0~180,s,smin~256,v,min(vmin,vmax),max(vmin,vmax)�����3��ͨ�����ڶ�Ӧ�ķ�Χ�ڣ���
				//mask��Ӧ���Ǹ����ֵȫΪ1(0xff)������Ϊ0(0x00).
				inRange(hsv, Scalar(0, smin, MIN(_vmin,_vmax)),
					Scalar(180, 256, MAX(_vmin, _vmax)), mask);
				int ch[] = {0, 0};
				hue.create(hsv.size(), hsv.depth());//hue��ʼ��Ϊ��hsv��С���һ���ľ���ɫ���Ķ������ýǶȱ�ʾ�ģ�������֮�����120�ȣ���ɫ���180��
				mixChannels(&hsv, 1, &hue, 1, ch, 1);//��hsv��һ��ͨ��(Ҳ����ɫ��)�������Ƶ�hue�У�0��������

				if( trackObject < 0 )//���ѡ�������ɿ��󣬸ú����ڲ��ֽ��丳ֵ1
				{
					//�˴��Ĺ��캯��roi�õ���Mat hue�ľ���ͷ����roi������ָ��ָ��hue����������ͬ�����ݣ�selectΪ�����Ȥ������
					Mat roi(hue, selection), maskroi(mask, selection);//mask�����hsv����Сֵ

					//calcHist()������һ������Ϊ����������У���2��������ʾ����ľ�����Ŀ����3��������ʾ��������ֱ��ͼά��ͨ�����б���4��������ʾ��ѡ�����뺯��
					//��5��������ʾ���ֱ��ͼ����6��������ʾֱ��ͼ��ά������7������Ϊÿһάֱ��ͼ����Ĵ�С����8������Ϊÿһάֱ��ͼbin�ı߽�
					calcHist(&roi, 1, 0, maskroi, hist, 1, &hsize, &phranges);//��roi��0ͨ������ֱ��ͼ��ͨ��mask����hist�У�hsizeΪÿһάֱ��ͼ�Ĵ�С
					normalize(hist, hist, 0, 255, CV_MINMAX);//��hist����������鷶Χ��һ��������һ����0~255

					trackWindow = selection;
					trackObject = 1;//ֻҪ���ѡ�������ɿ�����û�а�������0��'c'����trackObjectһֱ����Ϊ1����˸�if����ֻ��ִ��һ�Σ���������ѡ���������

					histimg = Scalar::all(0);//�밴��'c'����һ���ģ������all(0)��ʾ���Ǳ���ȫ����0
					int binW = histimg.cols / hsize;  //histing��һ��200*300�ľ���hsizeӦ����ÿһ��bin�Ŀ�ȣ�Ҳ����histing�����ֳܷ�����bin����
					Mat buf(1, hsize, CV_8UC3);//����һ�����嵥bin����
					for( int i = 0; i < hsize; i++ )//saturate_case����Ϊ��һ����ʼ����׼ȷ�任����һ����ʼ����
						buf.at<Vec3b>(i) = Vec3b(saturate_cast<uchar>(i*180./hsize), 255, 255);//Vec3bΪ3��charֵ������
					cvtColor(buf, buf, CV_HSV2BGR);//��hsv��ת����bgr

					for( int i = 0; i < hsize; i++ )
					{
						int val = saturate_cast<int>(hist.at<float>(i)*histimg.rows/255);//at����Ϊ����һ��ָ������Ԫ�صĲο�ֵ
						rectangle( histimg, Point(i*binW,histimg.rows),    //��һ������ͼ���ϻ�һ���򵥳�ľ��Σ�ָ�����ϽǺ����½ǣ���������ɫ����С�����͵�
							Point((i+1)*binW,histimg.rows - val),
							Scalar(buf.at<Vec3b>(i)), -1, 8 );
					}
				}

				calcBackProject(&hue, 1, 0, hist, backproj, &phranges);//����ֱ��ͼ�ķ���ͶӰ������hueͼ��0ͨ��ֱ��ͼhist�ķ���ͶӰ��������backproj��
				backproj &= mask;

				//opencv2.0�Ժ�İ汾��������ǰû��cv�����ˣ������������������2����˼�ĵ���Ƭ����ɵĻ�����ǰ���Ǹ�Ƭ�β����ɵ��ʣ����һ����ĸҪ
				//��д������Camshift�������һ����ĸ�Ǹ����ʣ���Сд������meanShift�����ǵڶ�����ĸһ��Ҫ��д
				RotatedRect trackBox = CamShift(backproj, trackWindow,               //trackWindowΪ���ѡ�������TermCriteriaΪȷ��������ֹ��׼��
					TermCriteria( CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 10, 1 ));//CV_TERMCRIT_EPS��ͨ��forest_accuracy,CV_TERMCRIT_ITER
				if( trackWindow.area() <= 1 )                                                  //��ͨ��max_num_of_trees_in_the_forest  
				{
					int cols = backproj.cols, rows = backproj.rows, r = (MIN(cols, rows) + 5)/6;
					trackWindow = Rect(trackWindow.x - r, trackWindow.y - r,
						trackWindow.x + r, trackWindow.y + r) &
						Rect(0, 0, cols, rows);//Rect����Ϊ�����ƫ�ƺʹ�С������һ��������Ϊ��������Ͻǵ����꣬�����ĸ�����Ϊ����Ŀ�͸�
				}

				if( backprojMode )
					cvtColor( backproj, image, CV_GRAY2BGR );//���ͶӰģʽ����ʾ��Ҳ��rgbͼ��
				ellipse( image, trackBox, Scalar(0,0,255), 3, CV_AA );//���ٵ�ʱ������ԲΪ����Ŀ��
			}
		}

		//����Ĵ����ǲ���pauseΪ�滹��Ϊ�ٶ�Ҫִ�е�
		else if( trackObject < 0 )//ͬʱҲ���ڰ�����ͣ��ĸ�Ժ�
			paused = false;

		if( selectObject && selection.width > 0 && selection.height > 0 )
		{
			Mat roi(image, selection);
			bitwise_not(roi, roi);//bitwise_notΪ��ÿһ��bitλȡ��
		}

		imshow( "CamShift Demo", image );
		imshow( "Histogram", histimg );

		char c = (char)waitKey(10);
		if( c == 27 )              //�˳���
			break;
		switch(c)
		{
		case 'b':             //����ͶӰģ�ͽ���
			backprojMode = !backprojMode;
			break;
		case 'c':            //�������Ŀ�����
			trackObject = 0;
			histimg = Scalar::all(0);
			break;
		case 'h':          //��ʾֱ��ͼ����
			showHist = !showHist;
			if( !showHist )
				destroyWindow( "Histogram" );
			else
				namedWindow( "Histogram", 1 );
			break;
		case 'p':       //��ͣ���ٽ���
			paused = !paused;
			break;
		default:
			;
		}
	}
	return 0;
}