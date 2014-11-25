/*
 *���ܣ��˶���⣬ǰ�����
 *���ԣ�http://blog.csdn.net/augusdi/article/details/9020009
 *Info:[11/12/2014 jmy]
 */

#define  Switch 1

#if Switch

#include <stdio.h>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

//#pragma comment(lib, "cv.lib")
//#pragma comment(lib, "cxcore.lib")
//#pragma comment(lib, "highgui.lib")

int diff2_main( int argc, char** argv )
{
	//����IplImageָ��
	IplImage* pFrame = NULL; 
	IplImage* pFrImg = NULL;
	IplImage* pBkImg = NULL;

	CvMat* pFrameMat = NULL;
	CvMat* pFrMat = NULL;
	CvMat* pBkMat = NULL;

	CvCapture* pCapture = NULL;

	int nFrmNum = 0;

	//��������
	cvNamedWindow("video", 1);
	cvNamedWindow("background",1);
	cvNamedWindow("foreground",1);
	//ʹ������������
	cvMoveWindow("video", 30, 0);
	cvMoveWindow("background", 360, 0);
	cvMoveWindow("foreground", 690, 0);


	if( !(pCapture = cvCaptureFromAVI("bike.avi")))
	{
		//pCapture = cvCaptureFromCAM(-1))
		fprintf(stderr, "Can not open camera.\n");
		return -2;
	}


	//��֡��ȡ��Ƶ
	while(pFrame = cvQueryFrame( pCapture ))
	{
		nFrmNum++;

		//����ǵ�һ֡����Ҫ�����ڴ棬����ʼ��
		if(nFrmNum == 1)
		{
			pBkImg = cvCreateImage(cvSize(pFrame->width, pFrame->height),  IPL_DEPTH_8U,1);
			pFrImg = cvCreateImage(cvSize(pFrame->width, pFrame->height),  IPL_DEPTH_8U,1);

			pBkMat = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);
			pFrMat = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);
			pFrameMat = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);

			//ת���ɵ�ͨ��ͼ���ٴ���
			cvCvtColor(pFrame, pBkImg, CV_BGR2GRAY);
			cvCvtColor(pFrame, pFrImg, CV_BGR2GRAY);

			cvConvert(pFrImg, pFrameMat);
			cvConvert(pFrImg, pFrMat);
			cvConvert(pFrImg, pBkMat);
		}
		else
		{
			cvCvtColor(pFrame, pFrImg, CV_BGR2GRAY);
			cvConvert(pFrImg, pFrameMat);
			//��˹�˲��ȣ���ƽ��ͼ��
			//cvSmooth(pFrameMat, pFrameMat, CV_GAUSSIAN, 3, 0, 0);

			//��ǰ֡������ͼ���
			cvAbsDiff(pFrameMat, pBkMat, pFrMat);

			//��ֵ��ǰ��ͼ
			cvThreshold(pFrMat, pFrImg, 60, 255.0, CV_THRESH_BINARY);

			//������̬ѧ�˲���ȥ������  
			//cvErode(pFrImg, pFrImg, 0, 1);
			//cvDilate(pFrImg, pFrImg, 0, 1);

			//���±���
			cvRunningAvg(pFrameMat, pBkMat, 0.003, 0);
			//������ת��Ϊͼ���ʽ��������ʾ
			cvConvert(pBkMat, pBkImg);

			//��ʾͼ��
			cvShowImage("video", pFrame);
			cvShowImage("background", pBkImg);
			cvShowImage("foreground", pFrImg);

			//����а����¼���������ѭ��
			//�˵ȴ�ҲΪcvShowImage�����ṩʱ�������ʾ
			//�ȴ�ʱ����Ը���CPU�ٶȵ���
			if( cvWaitKey(20) >= 0 )
			{
				break;
			}
		}
	}
	cvWaitKey();

	//���ٴ���
	cvDestroyWindow("video");
	cvDestroyWindow("background");
	cvDestroyWindow("foreground");

	//�ͷ�ͼ��;���
	cvReleaseImage(&pFrImg);
	cvReleaseImage(&pBkImg);

	cvReleaseMat(&pFrameMat);
	cvReleaseMat(&pFrMat);
	cvReleaseMat(&pBkMat);

	cvReleaseCapture(&pCapture);

	return 0;
}
#else

#include <cv.h>
#include <highgui.h>

//#pragma comment(lib, "cv.lib")
//#pragma comment(lib, "cxcore.lib")
//#pragma comment(lib, "highgui.lib")

int main( int argc, char** argv )
{
	CvCapture* capture = NULL;
	IplImage *frame = NULL;

	IplImage  *frame_last = NULL;//�洢��һ֡
	IplImage  *m_out_image = NULL;

	IplImage* frame_gray = NULL;
	IplImage* frame_gray_last = NULL;
	IplImage* m_out_image_copy = NULL;
	int nFrmNum = 0;

	//capture = cvCaptureFromCAM(-1); //������ͷ
	capture = cvCaptureFromAVI("diff_flash1s.wmv"); //����Ƶ

	//��������
	cvNamedWindow( "result", 1 );
	cvNamedWindow("���");

	//��֡��ȡ��Ƶ
	while(frame = cvQueryFrame( capture ))
	{
		nFrmNum++;

		//����ǵ�һ֡����Ҫ�����ڴ棬����ʼ��
		if(nFrmNum == 1)
		{
			frame_last = cvCreateImage(cvSize(frame->width,frame->height),IPL_DEPTH_8U, frame->nChannels);
			cvCopy(frame,frame_last);
		}
		else
		{
			frame_gray = cvCreateImage(cvSize(frame->width,frame->height),IPL_DEPTH_8U, 1);
			frame_gray_last = cvCreateImage(cvSize(frame->width,frame->height),IPL_DEPTH_8U, 1);

			m_out_image = cvCreateImage(cvSize(frame->width,frame->height),IPL_DEPTH_8U, 1);
			m_out_image_copy = cvCreateImage( cvSize(frame->width,frame->height),IPL_DEPTH_8U, 1 );

			cvCvtColor(frame,frame_gray,CV_RGB2GRAY);
			cvCvtColor(frame_last,frame_gray_last,CV_RGB2GRAY);
			cvAbsDiff(frame_gray,frame_gray_last,m_out_image);

			//cvThreshold(m_out_image,m_out_image,128, 255,CV_THRESH_BINARY);

			//��������ͼ��д�����ڶ���ͼ����
			if( m_out_image_copy->origin == IPL_ORIGIN_TL )
			{
				cvCopy( m_out_image, m_out_image_copy, 0 );
			}
			else
			{
				cvFlip( m_out_image, m_out_image_copy, 0 );
			}

			frame_last = cvCreateImage(cvSize(frame->width,frame->height),IPL_DEPTH_8U, frame->nChannels);
			cvCopy(frame,frame_last);

			cvShowImage("���",m_out_image_copy);
			cvShowImage("result",frame);

			cvReleaseImage( &m_out_image_copy );
			cvReleaseImage( &frame_gray_last );
			cvReleaseImage( &frame_gray );

			if( cvWaitKey( 20 ) >= 0 )
			{
				break;
			}
		}
	}
	cvWaitKey();

	cvReleaseImage( &m_out_image );
	cvReleaseImage( &frame_last );
	cvReleaseImage( &frame );

	cvReleaseCapture( &capture );

	cvDestroyWindow("result");
	cvDestroyWindow("���");

	return 0;
}
#endif