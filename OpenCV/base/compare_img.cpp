/************************************************************************
* Copyright(c) 2014 tuling56
*
* File:	compare_img.cpp
* Brief: ����opencv��ͼƬ�����ƶȱȽ�
* Source:http://blog.csdn.net/rcfalcon/article/details/7718436
* Status: 
* Date:	[11/26/2014 jmy]
************************************************************************/

#include <opencv2\opencv.hpp>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;

CvSeq* getImageContour(IplImage* srcIn) 
{
	IplImage* src;
	src = cvCreateImage(cvGetSize(srcIn),8,1);

	//����ͼ�� 
	cvCopy(srcIn,src);
	//�����ռ� 
	CvMemStorage* mem = cvCreateMemStorage(0);
	//�ṹ�� (mem��seq����ͬһ����ַ<���ͷŵ�ʱ��ֻҪ�ͷ�һ��������>)
	CvSeq* seq;

	if(!mem){
		printf("mem is null");
	}

	//��ֵ��ͼ��
	cvThreshold(src,src,100,255,0);
	//����ͼ������ ������������Ϣ�����ͷ� �ں�����Ҫ�õ�
	cvFindContours(src,mem,&seq,sizeof(CvContour),CV_RETR_CCOMP);
	//�ͷ�ͼ��ռ�
	cvReleaseImage(&src);
	//����������Ϣ
	return seq;
}


int main_comp(int argc, char* argv[]){

	//����ͼ��1
	IplImage* src1 = cvLoadImage("samples\\7.png",CV_LOAD_IMAGE_GRAYSCALE);
	//��ȡͼ��1������
	CvSeq* contour1;
	contour1 = getImageContour(src1);


	//����ͼ��2
	IplImage* src2 = cvLoadImage("samples\\2.png",CV_LOAD_IMAGE_GRAYSCALE);
	//��ȡͼ��2������
	CvSeq* contour2;
	contour2 = getImageContour(src2);


	//���бȶ�  -- �Ƚ���������������Ӧ��HU�صľ��� �ж�Զ
	double result;
	//cvMatchShapes��������������1������2��������
	//�����һ����������ͨ�غ����ľ� �� Ȼ�����������ε�HU�أ�HU���7����ֵ������ma�������
	//�ĸ������ͬ��(HU�ౣ����mb��) 
	//Ȼ��Ƚ�������HU��������� 
	//����������3�� �����ֱ���1,2,3 ���ּ��㷽��
	result = cvMatchShapes(contour1,contour2,1);

	//������ ���ԽС ���ƶ�Խ��
	printf("result is %f \n",result);

	//�ͷ������洢�ռ�
	cvReleaseMemStorage(&contour1->storage);
	cvReleaseMemStorage(&contour2->storage);

	//�ͷ�ͼ��ռ�
	cvReleaseImage(&src1);
	cvReleaseImage(&src2);

	getchar();

	return 0;

}


/*****************************************************/
/* ��Mat��д�ķ���                                     */
/*****************************************************/

Mat getImageContour(Mat srcIn)
{

	Mat src(srcIn),seq;
	//��ֵ��ͼ��
	threshold(src,src,100,255,0);
	//����ͼ������ ������������Ϣ�����ͷ� �ں�����Ҫ�õ�
	findContours(src,seq,sizeof(CvContour),CV_RETR_CCOMP);
	//����������Ϣ
	return seq;

}


int main_amt(int argc, char* argv[])
{

	//����ͼ��1
	Mat src1 = imread("samples\\7.png",CV_LOAD_IMAGE_GRAYSCALE);
	Mat contour1 = getImageContour(src1);

	//����ͼ��2
	Mat src2 = imread("samples\\7.png",CV_LOAD_IMAGE_GRAYSCALE);
	Mat contour2 = getImageContour(src1);


	//���бȶ�  -- �Ƚ���������������Ӧ��HU�صľ��� �ж�Զ
	double result;
	//cvMatchShapes��������������1������2��������
	//�����һ����������ͨ�غ����ľ� �� Ȼ�����������ε�HU�أ�HU���7����ֵ������ma�������
	//�ĸ������ͬ��(HU�ౣ����mb��) 
	//Ȼ��Ƚ�������HU��������� 
	//����������3�� �����ֱ���1,2,3 ���ּ��㷽��
 	result = matchShapes(contour1,contour2,1,0.0);

	//������ ���ԽС ���ƶ�Խ��
	printf("result is %f \n",result);

	getchar();

	return 0;

}
