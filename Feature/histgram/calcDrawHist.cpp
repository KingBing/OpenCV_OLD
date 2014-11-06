#include <highgui.h>
#include <opencv2/core/core.hpp>
#include <opencv2/legacy/compat.hpp>
#include <opencv2/imgproc/imgproc_c.h>

using namespace cv;

IplImage *DrawHistogram(CvHistogram*hist, float scaleX = 1, float scaleY = 1)
{  // ��ֱ��ͼ   
	float histMax = 0;  
	cvGetMinMaxHistValue(hist, 0 , &histMax, 0, 0);  // ȡ��ֱ��ͼ�е���ֵ   
	IplImage *imgHist = cvCreateImage(cvSize(256 * scaleX, 64*scaleY), 8, 1);
	cvZero(imgHist); //// ������ֵ
	for(int i = 0; i < 255; i++)
	{
		float histValue = cvQueryHistValue_1D(hist, i); // ȡ��ֱ��ͼ�е�iֵ
		float nextValue = cvQueryHistValue_1D(hist, i+1);
		int numPt = 5;
		CvPoint pt[5];
		pt[0] = cvPoint(i*scaleX, 64*scaleY);
		pt[1] = cvPoint((i+1)*scaleX, 64*scaleY);
		pt[2] = cvPoint((i+1)*scaleX, (1 -(nextValue/histMax))* 64 * scaleY);
		pt[3] = cvPoint((i+1)*scaleX, (1 -(histValue/histMax))* 64 * scaleY);
		pt[4] = cvPoint(i*scaleX, 64*scaleY);
		cvFillConvexPoly(imgHist, pt, numPt, cvScalarAll(255));
	}
	return imgHist;
}  


void calcDrawHist(char* path)
{
	IplImage* img = cvLoadImage(path,1); //RGB����
	if(!img)
		return;
	//Ȼ�󣬴�������ʼ��һ��ֱ��ͼ��
	int numBins = 256;
	float range[] = {0, 255};
	float *ranges[] = { range };

	CvHistogram *hist = cvCreateHist(1, &numBins, CV_HIST_ARRAY, ranges, 1);
	cvClearHist(hist);
	//���������ʹ�õ���1ά��ֱ��ͼ�����Ҹ�ֱ��ͼ��256��ֱ��������Χ��0-255������cvCreateHist���Զ��������Χ�ֽ��256��ֱ������

	//Ȼ�󣬽����صĲ�ɫͼ���BGR����ͨ�����зֽ⣺����ͼ��ռ䣬�����ú���cvSplit����ͨ���ķֽ⣺
	IplImage* imgRed = cvCreateImage(cvGetSize(img), 8, 1);
	IplImage* imgGreen = cvCreateImage(cvGetSize(img), 8, 1);
	IplImage* imgBlue = cvCreateImage(cvGetSize(img), 8, 1);

	cvSplit(img, imgBlue, imgGreen, imgRed, NULL);
	//cvSplit�Ĳ����ǰ���B��G��R������һ��˳��ġ�ͼ�����ڴ��еĴ洢Ҳ�ǰ���B��G��R��˳����д洢��

	
	//��������ֱ��ͼ���Ҷ�ֱ��ͼ��
	IplImage*grayimg=cvCreateImage(cvGetSize(img),img->depth,1);
	cvCvtColor(img,grayimg,CV_BGR2GRAY);
	cvCalcHist(&grayimg, hist, 0, 0);
	IplImage* imgHistGray = DrawHistogram(hist);
	cvClearHist(hist);
	
	
	
	
	//��2������ֱ��ͼ����ʾֱ��ͼ
	//ʹ��Rͨ��ͼ�񣬼���Rͨ��ͼ���ֱ��ͼ��
	cvCalcHist(&imgRed, hist, 0, 0);
	IplImage* imgHistRed = DrawHistogram(hist);
	cvClearHist(hist);
	///����cvCalcHist����imgRed��ֱ��ͼ������ֱ��ͼ�洢��hist�С�imgHistRed��ֱ��ͼ��hist�Ӿ�Ч��������DrawHistogram��ֱ��ͼ�滭��ͼ��imgHistRed�ϣ��Ժ�������������

	//����������ͨ����Ҳ������ͬ�Ĳ�����
	cvCalcHist(&imgGreen, hist, 0, 0);
	IplImage* imgHistGreen = DrawHistogram(hist);
	cvClearHist(hist);

	cvCalcHist(&imgBlue, hist, 0, 0);
	IplImage* imgHistBlue = DrawHistogram(hist);
	cvClearHist(hist);
	
	//����ڴ�������ʾ��Щֱ��ͼ��
	cvNamedWindow("Gray");
	cvNamedWindow("Red");
	cvNamedWindow("Green");
	cvNamedWindow("Blue");

	cvShowImage("Gray",imgHistGray);
	cvShowImage("Red", imgHistRed);
	cvShowImage("Green", imgHistGreen);
	cvShowImage("Blue", imgHistBlue);

	cvWaitKey(0);
	cvReleaseImage(&img);
	cvReleaseImage(&grayimg);
	cvReleaseImage(&imgHistGray);
	cvReleaseImage(&imgHistRed);
	cvReleaseImage(&imgHistGreen);
	cvReleaseImage(&imgHistBlue);
	cvDestroyAllWindows(); 
}