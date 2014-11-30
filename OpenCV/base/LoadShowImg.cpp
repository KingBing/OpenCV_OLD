#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std; 

//OpenCV1.0�ӿڵ�
void Load_Show_Img(char* filepath);

int Read_Show_main( int argc, char** argv )
{ 

	Mat image;
	image = imread("samples/1.png", CV_LOAD_IMAGE_COLOR);	// Read the file

	if(! image.data )                              // Check for invalid input
	{
		cout <<  "Could not open or find the image" << endl ;
		return -1;
	}

	//��������  
	//����Ϊ�����ص�ͼƬ����������֣����ֵ�λ�ã��ı������½ǣ������壬��С����ɫ  
	string words= "good luck";  
	putText( image, words, Point( image.rows/2,image.cols/4),CV_FONT_HERSHEY_COMPLEX, 1, Scalar(255, 0, 0) );  


	namedWindow( "Display window", CV_WINDOW_AUTOSIZE );// Create a window for display.
	imshow( "Display window", image );                   // Show our image inside it.

	waitKey(0);											 // Wait for a keystroke in the window
	return 0;
}


void Load_Show_Img(char* filepath)
{

	/* cvLoadImage( filename, -1 ); Ĭ�϶�ȡͼ���ԭͨ���� 
		cvLoadImage( filename, 0 );ǿ��ת����ȡͼ��Ϊ�Ҷ�ͼ 
		cvLoadImage( filename, 1 );��ȡ��ɫͼ 
		*/

    IplImage *pImg;
	if(	(pImg = cvLoadImage( filepath, 1)) != 0 )
	{
		cvNamedWindow( "Image", 1 );//��������
		cvShowImage( "Image", pImg );//��ʾͼ��
		cvWaitKey(0); //�ȴ�����
		cvDestroyWindow( "Image" );//���ٴ���
		cvReleaseImage( &pImg ); //�ͷ�ͼ��
		cvWaitKey(0); //�ȴ�����

	}

	else{
		cout<<"����ʧ��"<<endl;
		cvWaitKey(0); //�ȴ�����

	}

}


