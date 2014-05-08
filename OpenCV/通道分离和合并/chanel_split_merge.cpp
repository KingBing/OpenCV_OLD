#include <cv.h>
#include <highgui.h>
using namespace std;

void channel_split_merge(char*picname)
{
	IplImage*input=0;

	if ((input=cvLoadImage(picname,1))!=0)
	{

		IplImage* rImg=cvCreateImage(cvGetSize(input),IPL_DEPTH_8U,1);    
		IplImage* gImg=cvCreateImage(cvGetSize(input),IPL_DEPTH_8U,1);    
		IplImage* bImg=cvCreateImage(cvGetSize(input),IPL_DEPTH_8U,1);
		
		
		cvNamedWindow( "Input", 1 );//��������
		cvShowImage( "Input", input );//��ʾͼ��

		cvSplit(input,bImg,rImg,gImg,NULL);
		cvNamedWindow("bImg",1);
		cvNamedWindow("gImg",1);
		cvNamedWindow("rImg",1);
		cvShowImage( "bImg", bImg );//��ʾͼ��
		cvShowImage( "gImg", gImg );
		cvShowImage( "rImg", rImg );

		cvWaitKey(0); //�ȴ�����

		IplImage* rImg3=cvCreateImage(cvGetSize(input),IPL_DEPTH_8U,3);    
		IplImage* gImg3=cvCreateImage(cvGetSize(input),IPL_DEPTH_8U,3);    
		IplImage* bImg3=cvCreateImage(cvGetSize(input),IPL_DEPTH_8U,3);   
		
		cvMerge(0,0,rImg,0,rImg3);  
		cvMerge(0,gImg,0,0,gImg3);  
		cvMerge(bImg,0,0,0,bImg3);

		cvShowImage( "bImg", bImg3);//��ʾ����ͼ��
		cvShowImage( "gImg", gImg3 );
		cvShowImage( "rImg", rImg3);

		cvWaitKey(0); //�ȴ�����

		cvMerge(bImg,gImg,0,0,rImg3);  
		cvMerge(bImg,0,rImg,0,gImg3);  
		cvMerge(0,gImg,rImg,0,bImg3);  

		cvShowImage( "bImg", bImg3);//��ʾ�ϲ�ͼ��
		cvShowImage( "gImg", gImg3 );
		cvShowImage( "rImg", rImg3);


		cvWaitKey(0); //�ȴ�����
		cvDestroyAllWindows();//���ٴ���
		cvReleaseImage( &input ); //�ͷ�ͼ��
		cvReleaseImage( &bImg );
		cvReleaseImage( &gImg );
		cvReleaseImage( &rImg );
		cvReleaseImage( &bImg3 );
		cvReleaseImage( &gImg3 );
		cvReleaseImage( &rImg3 );

		cvWaitKey(0); //�ȴ���
	}
	else
	{
		cout<<"����ʧ��"<<endl;
		cvWaitKey(0);
	}
}

