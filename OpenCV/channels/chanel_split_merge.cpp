#include <cv.h>
#include <highgui.h>
using namespace std;

void channel_split_merge()
{
	IplImage*input=0;

	if ((input=cvLoadImage("PicVideo//channel.jpg",1))!=0)
	{

		IplImage* rImg=cvCreateImage(cvGetSize(input),IPL_DEPTH_8U,1);    
		IplImage* gImg=cvCreateImage(cvGetSize(input),IPL_DEPTH_8U,1);    
		IplImage* bImg=cvCreateImage(cvGetSize(input),IPL_DEPTH_8U,1);
		
		
		cvNamedWindow( "Input", 1 );
		cvShowImage( "Input", input );//��ʾԭͼ

		cvSplit(input,bImg,gImg,rImg,NULL);
		cvNamedWindow("bImg",1);
		cvNamedWindow("gImg",1);
		cvNamedWindow("rImg",1);

		cvShowImage( "bImg", bImg );//��ʾ����ͼ��
		cvShowImage( "gImg", gImg );
		cvShowImage( "rImg", rImg );

		cvWaitKey(0); 

		IplImage* rImg3=cvCreateImage(cvGetSize(input),IPL_DEPTH_8U,3);    
		IplImage* gImg3=cvCreateImage(cvGetSize(input),IPL_DEPTH_8U,3);    
		IplImage* bImg3=cvCreateImage(cvGetSize(input),IPL_DEPTH_8U,3);   
		
		//��һ�κϲ��ƻ��˽��
		//cvMerge(0,0,rImg,0,rImg3);  
		//cvMerge(0,gImg,0,0,gImg3);  
		//cvMerge(bImg,0,0,0,bImg3);

		//cvShowImage( "bImg", bImg3);//��ʾ�ϲ�ͼ��1
		//cvShowImage( "gImg", gImg3 );
		//cvShowImage( "rImg", rImg3);

		cvWaitKey(0); 

		/*cvCvtColor(bImg,bImg3,CV_GRAY2BGR);
		cvCvtColor(gImg,gImg3,CV_GRAY2BGR);
		cvCvtColor(rImg,rImg3,CV_GRAY2BGR);*/


		cvMerge(bImg,gImg,0,0,rImg3);  
		cvMerge(bImg,0,rImg,0,gImg3);  
		cvMerge(0,gImg,rImg,0,bImg3);  

		cvShowImage( "bImg", bImg3);//��ʾ�ϲ�ͼ��2
		cvShowImage( "gImg", gImg3 );
		cvShowImage( "rImg", rImg3);


		cvWaitKey(0); //�ȴ�����
		cvDestroyAllWindows();
		cvReleaseImage( &input ); 
		cvReleaseImage( &bImg );
		cvReleaseImage( &gImg );
		cvReleaseImage( &rImg );
		cvReleaseImage( &bImg3 );
		cvReleaseImage( &gImg3 );
		cvReleaseImage( &rImg3 );

		cvWaitKey(0); 
	}
	else
	{
		cout<<"����ʧ��"<<endl;
		cvWaitKey(0);
	}
}

