#include "detection.h"
#include<opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;


int main(int argc, char* argv[])
{
	IplImage *src=cvLoadImage("E:\\opencv2.3\\bone4.bmp");
	char*filename="frame2.bmp";
	//-------------------------------°æ±ﬂ‘µºÏ≤‚°ø------------------------------
	//	√Ë ˆ:
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
	//-------------------------------°æ÷±œﬂºÏ≤‚°ø------------------------------
	//	√Ë ˆ:
	//-------------------------------------------------------------------------
	//stdhoughlinedete(filename);
	line_dete_2(filename);



	//--------------------------------°æ∂˛÷µªØ°ø------------------------------
	//	√Ë ˆ:
	//-------------------------------------------------------------------------
	//binaryzation(filename);
	//adaptiveThreshold();

	//-------------------------------°æ¬÷¿™ºÏ≤‚°ø------------------------------
	//	√Ë ˆ:
	//-------------------------------------------------------------------------
	//contour1();
	//contour2();
	
	
	return 0;
}
