//-----------------------------------【四边形目标的自动透视矫正】------------------------------
//	描述:opencv自带的对四边形目标的自动透视矫正
//  参考：csdn博客介绍：http://blog.csdn.net/mysteryrat/article/details/8955229
//		   官方例子：http://opencv-code.com/tutorials/automatic-perspective-correction-for-quadrilateral-objects/
//-------------------------------------------------------------------------

#include "rectify.h"

using namespace std;
using namespace cv;

int rectAutoRectify()  
{  
	Mat src = imread("rectRectify.png");  
	if (src.empty()){  
		cout<<"加载图像失败"<<endl;
		return -1;  
	}  

	Mat bw;  
	cvtColor(src,bw,CV_BGR2GRAY);  
	imshow("gray_src",bw);  
	
	blur(bw,bw,Size(3,3));  
	imshow("blur",bw); 
	
	Canny(bw,bw,100,100,3);  
	imshow("cannyblur",bw); 

	vector<Vec4i> lines;  
	HoughLinesP(bw,lines,1,CV_PI/180,70,30,10);  
	//1像素分辨能力  1度的角度分辨能力>70可以检测成连线  30是最小线长,在直线L上的点（且点与点之间距离小于maxLineGap=10的）连成线段，然后这些点全部删除，并且记录该线段的参数，就是起始点和终止点  


	//直线标注
	for(int i = 0; i < lines.size(); i++ )
	{		
		line( src, Point(lines[i][0],lines[i][1]), Point(lines[i][2],lines[i][3]), CV_RGB(255,0,0), 1, CV_AA, 0 );
	}
	imshow("alllines",src); 


	//needed for visualization only
	//这里是将检测的线调整到延长至全屏，即射线的效果，其实可以不必这么做  
	for (unsigned int i = 0;i<lines.size();i++)  
	{  
		Vec4i v = lines[i];  
		lines[i][0] = 0;  
		lines[i][1] = ((float)v[1] - v[3])/(v[0] - v[2])* -v[0] + v[1];  //水平直线全屏
		
		lines[i][2] = src.cols;  
		lines[i][3] = ((float)v[1] - v[3])/(v[0] - v[2])*(src.cols - v[2]) + v[3];  

	} 


	vector<Point2f> corners;//线的交点存储  
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

	//直线交点相连
	if (corners.size()==0)
	{
		printf("no corner\n");
	}
	else
	{
		printf("corner size=%d",corners.size());

		for(int i = 0; i < corners.size(); i++ )
		{		
			line( bw, Point(0,0), Point(corners[i].x,corners[i].y), CV_RGB(0,255,0), 1, CV_AA, 0 );
		}
		imshow("corner_line",bw);

	}
	


	vector<Point2f> approx;  
	approxPolyDP(Mat(corners),approx,arcLength(Mat(corners),true)*0.02,true);  


	if (approx.size()!=4)  
	{  
		cout<<"The object is not quadrilateral（四边形）!"<<endl;  
		return -1;  
	}  

	//get mass center  
	for (unsigned int i = 0;i < corners.size();i++)  
	{  
		center += corners[i];  //重载
	}  

	center *=(1./corners.size());  
	sortCorners(corners,center);  
	Mat dst = src.clone();  

	//Draw Lines  
	for (unsigned int i = 0;i<lines.size();i++)  
	{  
		Vec4i v = lines[i];  
		line(dst,Point(v[0],v[1]),Point(v[2],v[3]),CV_RGB(0,255,0));  //目标版块画绿线   
	}  

	//draw corner points  
	circle(dst,corners[0],3,CV_RGB(255,0,0),2);  
	circle(dst,corners[1],3,CV_RGB(0,255,0),2);  
	circle(dst,corners[2],3,CV_RGB(0,0,255),2);  
	circle(dst,corners[3],3,CV_RGB(255,255,255),2);  

	//draw mass center  
	circle(dst,center,3,CV_RGB(255,255,0),2);  

	Mat quad = Mat::zeros(300,220,CV_8UC3);//设定校正过的图片从320*240变为300*220  

	//corners of the destination image  
	vector<Point2f> quad_pts;  
	quad_pts.push_back(Point2f(0,0));  
	quad_pts.push_back(Point2f(quad.cols,0));//(220,0)  
	quad_pts.push_back(Point2f(quad.cols,quad.rows));//(220,300)  
	quad_pts.push_back(Point2f(0,quad.rows));  

	// Get transformation matrix  
	Mat transmtx = getPerspectiveTransform(corners,quad_pts);   //求源坐标系（已畸变的）与目标坐标系的转换矩阵  

	// Apply perspective transformation透视转换  
	warpPerspective(src,quad,transmtx,quad.size());  
	
	//imshow("src",src);  
	imshow("image",dst);  
	imshow("quadrilateral",quad);  

	waitKey();  
	getchar();
	return 0;  
}  

