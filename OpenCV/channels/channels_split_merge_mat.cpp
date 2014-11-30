#include <cv.h>
#include <highgui.h> 
#include <iostream>
#include <windows.h>  

using namespace cv; 
using namespace std;   

int main( int argc, char** argv )
{   
	FreeConsole();     //Hide the CMD window  
	if( argc != 2)   
	{    
		 std::cout <<"��������Ҫ���ص��ļ�!" << std::endl;   
	     return -1;  
	}  
	//��ȡͼ�� 
	Mat image;   
	char * imageName = argv[1];   
	image = imread(imageName, CV_LOAD_IMAGE_COLOR);// Read the file  
	if(! image.data )   
	{ 
	    std::cout <<  "�ļ�����ʧ��,����!" << std::endl;    
		return -1;   
    }   
	//�Ҷ�ͼ  
	Mat grayImage;   
	cvtColor(image,grayImage,CV_RGB2GRAY);//Coonvert the image from RGB to Grayscale format  
	//��ʾ��  
	Mat display;  
	int w = image.cols;  
	int h = image.rows;   
	display.create (h*2,w*2,CV_8UC3);  
	//��ɫ 
	Mat bk;  
	bk.create(h,w,CV_8UC1); 
	bk = Scalar(0);  
	//��ʾ��   
	Mat m(display,Rect(0,0,w,h));  
	Mat m1(display,Rect(0,h,w,h));  
	Mat m2(display,Rect(w,0,w,h)); 
	Mat m3(display,Rect(w,h,w,h)); 
	Mat m4(display,Rect(w/2,h/2,w,h)); 
	//ͨ��������  
	std::vector<cv::Mat> sbgr(image.channels());  
	//ͨ���ϳ���   
	std::vector<cv::Mat> mbgr(image.channels()); 
	//����   
	split(image,sbgr); //split to sbgr[0] ,sbgr[1] ,sbgr[2]  
	//�ϳɵ���ʾ-�Ҷ� 
	mbgr[0] = grayImage; 
	mbgr[1] = grayImage; 
	mbgr[2] = grayImage; 
	merge(mbgr,m);  
	//�ϳɵ���ʾ-B  
	mbgr[0] = sbgr[0]; 
	mbgr[1] = bk;  
	mbgr[2] = bk;  
	merge(mbgr,m1);  
	//�ϳɵ���ʾ-G 
	mbgr[0] = bk; 
	mbgr[1] = sbgr[1]; 
	mbgr[2] = bk;  
	merge(mbgr,m2); 
	//�ϳɵ���ʾ-R   
	mbgr[0] = bk; 
	mbgr[1] = bk; 
	mbgr[2] = sbgr[2]; 
	merge(mbgr,m3);  
	//���Ƶ���ʾ-ԭͼ  
	image.copyTo (m4); 
	//��ʾ   
	namedWindow( imageName,CV_WINDOW_NORMAL);// Create a window for display. 
	resizeWindow(imageName,w*2,h*2);  
	imshow(imageName, display);    // Show our image inside it.  
	waitKey(0);           // Wait for a keystroke in the window   
	return 0; 
} 