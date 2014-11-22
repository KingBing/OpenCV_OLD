//ͼ������������
//By MoreWindows (http://blog.csdn.net/MoreWindows)
#include <opencv2/opencv.hpp>
using namespace std;


IplImage *greyimg = NULL;
const char *binWndName = "��ֵͼ(http://blog.csdn.net/MoreWindows)";
const char *contourWndName = "����ͼ(http://blog.csdn.net/MoreWindows)";
CvSeq *g_pcvSeq = NULL;

void contour2_trackbar(int pos)
{
	// תΪ��ֵͼ
	IplImage *pBinaryImage = cvCreateImage(cvGetSize(greyimg), IPL_DEPTH_8U, 1);
	cvThreshold(greyimg, pBinaryImage, pos, 255, CV_THRESH_BINARY);
	// ��ʾ��ֵͼ
	cvShowImage(binWndName, pBinaryImage);

	CvMemStorage* cvMStorage = cvCreateMemStorage();
	// �������������ؼ�⵽�������ĸ���
	cvFindContours(pBinaryImage,cvMStorage, &g_pcvSeq);

	IplImage *pOutlineImage = cvCreateImage(cvGetSize(greyimg), IPL_DEPTH_8U, 3);
	int _levels = 5;
	cvZero(pOutlineImage);
	cvDrawContours(pOutlineImage, g_pcvSeq, CV_RGB(255,0,0), CV_RGB(0,255,0), _levels);
	cvShowImage(contourWndName, pOutlineImage);

	cvReleaseMemStorage(&cvMStorage);
	cvReleaseImage(&pBinaryImage);
	cvReleaseImage(&pOutlineImage);
}

int contour2(char*path)
{	
	const char *pstrWindowsSrcTitle = "ԭͼ(http://blog.csdn.net/MoreWindows)";
	const char *pstrWindowsToolBarName = "��ֵ��";

	// ���ļ��м���ԭͼ
	IplImage *pSrcImage = cvLoadImage(path, CV_LOAD_IMAGE_UNCHANGED);
	if (!pSrcImage)
	{
		printf("����ʧ��\n");
		exit(0);
	}
	// ��ʾԭͼ
	cvNamedWindow(pstrWindowsSrcTitle, CV_WINDOW_AUTOSIZE);
	cvShowImage(pstrWindowsSrcTitle, pSrcImage);

	// תΪ�Ҷ�ͼ
	greyimg =  cvCreateImage(cvGetSize(pSrcImage), IPL_DEPTH_8U, 1);
	cvCvtColor(pSrcImage, greyimg, CV_BGR2GRAY);

	// ������ֵͼ������ͼ����
	cvNamedWindow(binWndName, CV_WINDOW_AUTOSIZE);
	cvNamedWindow(contourWndName, CV_WINDOW_AUTOSIZE);


	// ������	
	int nThreshold = 0;
	cvCreateTrackbar(pstrWindowsToolBarName, binWndName, &nThreshold, 254, contour2_trackbar);

	contour2_trackbar(1);

	cvWaitKey(0);

	cvDestroyWindow(pstrWindowsSrcTitle);
	cvDestroyWindow(binWndName);
	cvDestroyWindow(contourWndName);
	cvReleaseImage(&pSrcImage);
	cvReleaseImage(&greyimg);
	return 0;
}