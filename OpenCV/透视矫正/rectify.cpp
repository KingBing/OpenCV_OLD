#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <iostream>

#include "rectify.h"
using namespace std;
using namespace cv;

int rectify()  
{  
	Mat src = imread("PicVideo//rectify1.jpg");  
	if (src.empty())  
	{  
		cout<<"����ͼ��ʧ��"<<endl;
		return -1;  
	}  

	Mat bw;  
	cvtColor(src,bw,CV_BGR2GRAY);  
	//imshow("gray_src",bw);  
	
	blur(bw,bw,Size(3,3));  
	//imshow("blur",bw);  
	
	Canny(bw,bw,100,100,3);  
	//imshow("cannyblur",bw); 

	vector<Vec4i> lines;  
	HoughLinesP(bw,lines,1,CV_PI/180,70,30,10);  
	//1���طֱ�����  1�ȵĽǶȷֱ�����>70���Լ�������  30����С�߳�  
	//��ֱ��L�ϵĵ㣨�ҵ����֮�����С��maxLineGap=10�ģ������߶Σ�Ȼ����Щ��ȫ��ɾ�������Ҽ�¼���߶εĲ�����������ʼ�����ֹ��  



	//needed for visualization only
	//�����ǽ������ߵ������ӳ���ȫ���������ߵ�Ч������ʵ���Բ�����ô��  
	for (unsigned int i = 0;i<lines.size();i++)  
	{  
		Vec4i v = lines[i];  
		lines[i][0] = 0;  
		lines[i][1] = ((float)v[1] - v[3])/(v[0] - v[2])* -v[0] + v[1];  
		lines[i][2] = src.cols;  
		lines[i][3] = ((float)v[1] - v[3])/(v[0] - v[2])*(src.cols - v[2]) + v[3];  

	}  

	vector<Point2f> corners;//�ߵĽ���洢  
	for (unsigned int i = 0;i<lines.size();i++)  
	{  
		for (unsigned int j=i+1;j<lines.size();j++)  
		{  
			Point2f pt = computeIntersect(lines[i],lines[j]);  
			if (pt.x >= 0 && pt.y >=0)  
			{  
				corners.push_back(pt);  
			}  
		}  
	}  

	vector<Point2f> approx;  
	approxPolyDP(Mat(corners),approx,arcLength(Mat(corners),true)*0.02,true);  

	if (approx.size()!=4)  
	{  
		cout<<"The object is not quadrilateral���ı��Σ�!"<<endl;  
		return -1;  
	}  

	//get mass center  
	for (unsigned int i = 0;i < corners.size();i++)  
	{  
		center += corners[i];  
	}  
	center *=(1./corners.size());  

	sortCorners(corners,center);  

	Mat dst = src.clone();  

	//Draw Lines  
	for (unsigned int i = 0;i<lines.size();i++)  
	{  
		Vec4i v = lines[i];  
		line(dst,Point(v[0],v[1]),Point(v[2],v[3]),CV_RGB(0,255,0));    //Ŀ���黭����   
	}  

	//draw corner points  
	circle(dst,corners[0],3,CV_RGB(255,0,0),2);  
	circle(dst,corners[1],3,CV_RGB(0,255,0),2);  
	circle(dst,corners[2],3,CV_RGB(0,0,255),2);  
	circle(dst,corners[3],3,CV_RGB(255,255,255),2);  

	//draw mass center  
	circle(dst,center,3,CV_RGB(255,255,0),2);  

	Mat quad = Mat::zeros(300,220,CV_8UC3);//�趨У������ͼƬ��320*240��Ϊ300*220  

	//corners of the destination image  
	vector<Point2f> quad_pts;  
	quad_pts.push_back(Point2f(0,0));  
	quad_pts.push_back(Point2f(quad.cols,0));//(220,0)  
	quad_pts.push_back(Point2f(quad.cols,quad.rows));//(220,300)  
	quad_pts.push_back(Point2f(0,quad.rows));  

	// Get transformation matrix  
	Mat transmtx = getPerspectiveTransform(corners,quad_pts);   //��Դ����ϵ���ѻ���ģ���Ŀ������ϵ��ת������  

	// Apply perspective transformation͸��ת��  
	warpPerspective(src,quad,transmtx,quad.size());  
	imshow("src",src);  
	imshow("image",dst);  
	imshow("quadrilateral",quad);  

	waitKey();  
	getchar();
	return 0;  
}  

