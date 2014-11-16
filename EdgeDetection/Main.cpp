#include "detection.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;


int main1(int argc, char* argv[])
{
	IplImage *src=cvLoadImage("video_12.JPG");
	char*filename="video_15.JPG";
	//-------------------------------°æ±ﬂ‘µºÏ≤‚°ø------------------------------
	//	√Ë ˆ:
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

	//-------------------------------°æ÷±œﬂºÏ≤‚°ø------------------------------
	//	√Ë ˆ:
	//-------------------------------------------------------------------------
	//stdhoughlinedete(filename);
	//line_dete_2(filename);

	//-------------------------------°æ‘≤ºÏ≤‚°ø------------------------------
	//	√Ë ˆ:
	//-------------------------------------------------------------------------
	//hough_circle(filename);
	
	//------------------------------°ææÿ–ŒºÏ≤‚°ø------------------------------
	//	√Ë ˆ:
	//-------------------------------------------------------------------------
    square_detection();

	
	//-------------------------------°æ¬÷¿™ºÏ≤‚°ø------------------------------
	//	√Ë ˆ:
	//-------------------------------------------------------------------------
	//contour1();
	//contour2(filename);

	//--------------------------------°æ∂˛÷µªØ°ø------------------------------
	//	√Ë ˆ:
	//-------------------------------------------------------------------------
	//binaryzation(filename);
	//adaptiveThreshold(filename);
	
	return 0;
}
