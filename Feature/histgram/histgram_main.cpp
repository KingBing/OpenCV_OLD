//histgram���ܵ������

#include "histgram.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

int histgram()
{
	char*filename="zimu.jpg";

	//-----------------------------------��ֱ��ͼ���ơ�------------------------------
	//	����:
	//-------------------------------------------------------------------------
	//calcDrawHist(filename);
	//oneDim(filename);
	mutiDim(filename);

	//-----------------------------------��ֱ��ͼ���⻯��------------------------------
	//	����:
	//-------------------------------------------------------------------------
	//equalizeHist(filename);

	

	return 0;
}