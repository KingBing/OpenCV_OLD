#include "detection.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;


int main1(int argc, char* argv[])
{
	IplImage *src=cvLoadImage("video_12.JPG");
	char*filename="video_15.JPG";
	//-------------------------------����Ե��⡿------------------------------
	//	����:
	//-------------------------------------------------------------------------
	//canny(filename);
	//log(filename);
	//sobel(filename);
	//prewitt(filename);
	//roberts(filename);
	//krisch(filename);
	//susan(filename);
	//laplace(filename);
	//laplace_mat(filename);
	//canny_trackbar(filename);
	//edge_trackbar(filename);

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

	
	//-------------------------------��������⡿------------------------------
	//	����:
	//-------------------------------------------------------------------------
	//contour1();
	//contour2(filename);

	//--------------------------------����ֵ����------------------------------
	//	����:
	//-------------------------------------------------------------------------
	//binaryzation(filename);
	//adaptiveThreshold(filename);
	
	return 0;
}
