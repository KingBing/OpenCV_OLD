#include "cv.h"  
#include "highgui.h"  
#include <stdlib.h>  
#include <stdio.h>  

IplImage *src=0;  
IplImage *dst=0;  
IplConvKernel *element=0;//����һ���ṹԪ��  
int element_shape=CV_SHAPE_RECT;//��������״��Ԫ��  
int max_iters=10;  
int open_close_pos=0;  
int erode_dilate_pos=0; 

void OpenClose(int pos)  
{  
	int n=open_close_pos-max_iters;  
	int an=n>0?n:-n;  
	element = cvCreateStructuringElementEx(an*2+1,an*2+1,an,an,element_shape,0);//�����ṹԪ��  

	if (n<0)  
	{  
		cvErode(src,dst,element,1);//��ʴͼ��  
		cvDilate(dst,dst,element,1);//����ͼ��  
	}  
	else 
	{         
		cvDilate(dst,dst,element,1);//����ͼ��  
		cvErode(src,dst,element,1);//��ʴͼ��  
	}  
	cvReleaseStructuringElement(&element);  
	cvShowImage("Open/Close",dst);  
} 

void ErodeDilate(int pos)  
{  
	int n=erode_dilate_pos-max_iters;  
	int an=n>0?n:-n;  
	element = cvCreateStructuringElementEx(an*2+1,an*2+1,an,an,element_shape,0);  
	if (n<0)  
	{  
		cvErode(src,dst,element,1);  
	}  
	else 
	{  
		cvDilate(src,dst,element,1);  
	}  
	cvReleaseStructuringElement(&element);  
	cvShowImage("Erode/Dilate",dst);  
}  

int morphologyShow()  
{  
	//char *filename =argc ==2?argv[1]:(char *)"lena.jpg";      
	if( (src = cvLoadImage("lena.jpg",1)) == 0 )  
		return -1;  
	dst=cvCloneImage(src);  

	cvNamedWindow("Open/Close",1);  
	cvNamedWindow("Erode/Dilate",1);  
	open_close_pos = erode_dilate_pos = max_iters;  
	cvCreateTrackbar("iterations","Open/Close",&open_close_pos,max_iters*2+1,OpenClose);  
	cvCreateTrackbar("iterations","Erode/Dilate",&erode_dilate_pos,max_iters*2+1,ErodeDilate);  
	for (;;)  
	{  
		int c;  
		OpenClose(open_close_pos);  
		ErodeDilate(erode_dilate_pos);  
		c= cvWaitKey(0);  
		if (c==27)  
		{  
			break;  
		}  
		switch(c) {  
		case 'e':  
			element_shape=CV_SHAPE_ELLIPSE;  
			break;  
		case 'r':  
			element_shape=CV_SHAPE_RECT;  
			break;  
		case 't':  
			element_shape=(element_shape+1)%3;  
			break;
		case 'c':  
			element_shape=CV_SHAPE_CROSS;  
			break;
		default:  
			break;   
		}  
	}  
	cvReleaseImage(&src);  
	cvReleaseImage(&dst);  

	cvDestroyWindow("Open/Close");  
	cvDestroyWindow("Erode/Dilate");  
	return 0;  
}  