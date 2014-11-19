//Function��ͼ���Canny��Ե���
//Source:By MoreWindows (http://blog.csdn.net/morewindows/article/details/8239625)
//Status:
//Improve:
//Info:[11/18/2014 jmy]

#include <opencv2/opencv.hpp>

using namespace std;

//#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
IplImage *g1_pSrcImage, *g_pCannyImg;
const char *pstrWindowsCannyTitle = "��Ե���ͼ(canny_trackbar)";


//cvCreateTrackbar�Ļص�����
void on_trackbar(int threshold)
{
	//canny��Ե���
	printf("threshold:%d\n",threshold);
	cvCanny(g1_pSrcImage, g_pCannyImg, threshold, threshold * 3, 3);
	cvShowImage(pstrWindowsCannyTitle, g_pCannyImg);
}

int canny_trackbar(char*filename)
{
	//const char *pstrImageName = "lena.jpg";
	const char *pstrWindowsSrcTitle = "ԭͼ(canny_trackbar)";
	const char *pstrWindowsToolBar = "Threshold";

	//���ļ�������ͼ��ĻҶ�ͼCV_LOAD_IMAGE_GRAYSCALE - �Ҷ�ͼ
	g1_pSrcImage = cvLoadImage(filename, CV_LOAD_IMAGE_GRAYSCALE);
	g_pCannyImg = cvCreateImage(cvGetSize(g1_pSrcImage), IPL_DEPTH_8U, 1);

	//��������
	cvNamedWindow(pstrWindowsSrcTitle, CV_WINDOW_AUTOSIZE);
	cvNamedWindow(pstrWindowsCannyTitle, CV_WINDOW_AUTOSIZE);


	//����������
	int nThresholdEdge = 1;
	cvCreateTrackbar(pstrWindowsToolBar, pstrWindowsCannyTitle, &nThresholdEdge, 100, on_trackbar);

	//��ָ����������ʾͼ��
	cvShowImage(pstrWindowsSrcTitle, g1_pSrcImage);
	on_trackbar(1);

	//�ȴ������¼�
	cvWaitKey();

	cvDestroyWindow(pstrWindowsSrcTitle);
	cvDestroyWindow(pstrWindowsCannyTitle);
	cvReleaseImage(&g1_pSrcImage);
	cvReleaseImage(&g_pCannyImg);


	return 0;
}

