//���Ȱ���ͷ�ļ�
#include "cvgabor.h"

int garbor()
{
	//����һ��������PI/4���߶���3��gabor
	double Sigma = 2*PI;
	double F = sqrt(2.0);
	CvGabor *gabor1 = new CvGabor; gabor1->Init(PI/4, 3, Sigma, F);

	//���ʵ������ʾ��
	IplImage *kernel = cvCreateImage( cvSize(gabor1->get_mask_width(), gabor1->get_mask_width()), IPL_DEPTH_8U, 1);
	kernel = gabor1->get_image(CV_GABOR_REAL);
	cvNamedWindow("Gabor Kernel", 1);
	cvShowImage("Gabor Kernel", kernel);
	cvWaitKey(0);

	//����һ��ͼ����ʾ
	IplImage *img = cvLoadImage( "Crop1.bmp", CV_LOAD_IMAGE_GRAYSCALE );
	cvNamedWindow("Original Image", 1);
	cvShowImage("Original Image", img);
	cvWaitKey(0);  


	 
		   //��ȡ����ͼ���gabor�˲���Ӧ��ʵ��������ʾ

	IplImage *reimg = cvCreateImage(cvSize(img->width,img->height), IPL_DEPTH_8U, 1);
	gabor1->conv_img(img, reimg, CV_GABOR_REAL);
	cvNamedWindow("Real Response", 1);
	cvShowImage("Real Response",reimg);
	cvWaitKey(0);
	cvDestroyWindow("Real Response");


	//��ȡ����ͼ���gabor�˲���Ӧ���鲿������ʾ
	IplImage *reimg = cvCreateImage(cvSize(img->width,img->height), IPL_DEPTH_8U, 1);
	gabor1->conv_img(img, reimg, CV_GABOR_IMAG);
	cvNamedWindow("Imaginary Response", 1);
	cvShowImage("Imaginary Response",reimg);
	cvWaitKey(0);
	cvDestroyWindow("Imaginary Response");


														
	//��ȡ����ͼ���gabor�˲���Ӧ��ģ������ʾ
	IplImage *reimg = cvCreateImage(cvSize(img->width,img->height), IPL_DEPTH_8U, 1);
	gabor1->conv_img(img, reimg, CV_GABOR_MAG);
	cvNamedWindow("Magnitude Response", 1);
	cvShowImage("Magnitude Response",reimg);
	cvWaitKey(0);
	cvDestroyWindow("Magnitude Response");
}