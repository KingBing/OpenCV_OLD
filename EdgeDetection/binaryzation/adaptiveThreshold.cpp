//-----------------------------------��˵����------------------------------
//	����:�Ƚ�Treshold��AdaptiveThreshold��Ч������
//  ���ܣ�cvAdaptiveThreshold()��ʹ��Otsu�㷨����õ�һ��ȫ����ֵ��
//		  Ȼ����������ֵ���ж�ֵ��
//  �ο���http://blog.csdn.net/hitwengqi/article/details/6856768
//-------------------------------------------------------------------------

#include <highgui.h>
#include <math.h>
#include <cv.h>


int adaptiveThreshold()
{
	IplImage *Igray = 0, *It = 0, *Iat;

	/*if( argc != 7 )
	{
		return -1;
	}*/
	
	//����������
	//double threshold = (double)atof( argv[1] ); //convert string to double
	//int threshold_type = atoi( argv[2] ) ? CV_THRESH_BINARY : CV_THRESH_BINARY_INV;
	//int adaptive_method = atoi( argv[3] ) ? CV_ADAPTIVE_THRESH_MEAN_C : CV_ADAPTIVE_THRESH_GAUSSIAN_C;
	//int block_size = atoi( argv[4] );
	//double offset = (double)atof( argv[5] );

	//�����������Ƕ�cvThreshold()���õ�
	double threshold =  15;
	int threshold_type =CV_THRESH_BINARY_INV;

    //
	int adaptive_method = CV_ADAPTIVE_THRESH_GAUSSIAN_C;
	int block_size = 3;
	double offset = 15.0;
	
	//���ػҶ�ͼ
	if( ( Igray = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE ) ) == 0 )
	{
		return -1;
	}
	
	//����ͬ����С8λ�Ҷ�ͼ�������
	It = cvCreateImage( cvSize( Igray -> width, Igray -> height ), IPL_DEPTH_8U, 1 ); //��ͨ��8λ�Ҷ�ͼ
	Iat = cvCreateImage( cvSize( Igray -> width, Igray -> height ), IPL_DEPTH_8U, 1 );
	
	//��ֵ��
	cvThreshold( Igray, It, threshold, 255, threshold_type );
	cvAdaptiveThreshold( Igray, Iat, 255, adaptive_method, threshold_type, block_size, offset );
	
	//�����������
	cvNamedWindow( "Raw", 1 );
	cvNamedWindow( "Threshold", 1 );
	cvNamedWindow( "Adaptive Threshold", 1 );
	cvShowImage( "Raw", Igray );
	cvShowImage( "Threshold", It );
	cvShowImage( "Adaptive Threshold", Iat );
	cvWaitKey(0);
	
	//�����ڴ�
	cvReleaseImage( &Igray );
	cvReleaseImage( &It );
	cvReleaseImage( &Iat );
	cvDestroyWindow( "Raw" );
	cvDestroyWindow( "Threshold" );
	cvDestroyWindow( "Adaptive Threshold" );

	return 0;
}