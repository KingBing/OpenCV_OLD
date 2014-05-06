#include <opencv2\core\core.hpp>  
#include <opencv2\highgui\highgui.hpp>  
#include <opencv2\imgproc\imgproc.hpp>  
#include <iostream>  

using namespace std;  
using namespace cv;  


int roi_mat()  
{  
	Mat image = imread("PicVideo\\test2.png", 1);  
	if(!image.data){  
		cout << "fail to load image" << endl;  
		return 0;  
	}  
	Mat tongtong = imread("PicVideo\\resize.JPG", 1);  
	//����ROI�����ַ�ʽ
	//Mat imageROI = image(Rect(140,20,tongtong.cols, tongtong.rows));  //��һ�ַ�ʽ
	//Mat imageROI(image, Rect(140,20,tongtong.cols, tongtong.rows));//�ڶ��ַ�ʽ  
	Mat imageROI = image(Range(20, 20 + tongtong.rows),Range(140, 140+tongtong.cols));  // �����ַ�ʽ  
	tongtong.copyTo(imageROI);  
	namedWindow("imageROI");  
	imshow("imageROI", imageROI);  
	namedWindow("image");  
	imshow("image",image);  
	
	waitKey(0);  
	return 0;  
}  