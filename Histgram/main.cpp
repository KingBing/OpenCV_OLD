#include "histgram.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

int main()
{
	char*filename="fruits.png";
	
	//EqualizeHist(filename);
	calcDrawHist(filename);


	return 0;
}