#include "detection.h"
#include<opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;


int main(int argc, char* argv[])
{
	IplImage *src=cvLoadImage("E:\\opencv2.3\\bone4.bmp");
	char*filename="frame3.bmp";
	//-------------------------------����Ե��⡿------------------------------
	//	����:
	//-------------------------------------------------------------------------
	//canny(filename);
	//log(filename);
	//sobel(filename);
	//prewitt(filename);
	//roberts(filename);
	//histogram(filename);
	//krisch(filename);
	//susan(filename);
	//laplace(filename);
	//canny_detail();
	//canny_trackbar(filename);
	//-------------------------------��ֱ�߼�⡿------------------------------
	//	����:
	//-------------------------------------------------------------------------
	//stdhoughlinedete(filename);
	//line_dete_2(filename);

	//-------------------------------��Բ��⡿------------------------------
	//	����:
	//-------------------------------------------------------------------------
	//hough_circle(filename);
	//------------------------------�����μ�⡿------------------------------
	//	����:
	//-------------------------------------------------------------------------
    square_detection();

	//--------------------------------����ֵ����------------------------------
	//	����:
	//-------------------------------------------------------------------------
	//binaryzation(filename);
	//adaptiveThreshold();

	//-------------------------------��������⡿------------------------------
	//	����:
	//-------------------------------------------------------------------------
	//contour1();
	//contour2();
	
	
	return 0;
}
